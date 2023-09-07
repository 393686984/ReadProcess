#include "DriverHide.h"
PVOID UtilKernelBase(OUT PULONG pSize)
{
	NTSTATUS status = STATUS_SUCCESS;
	ULONG bytes = 0;
	PRTL_PROCESS_MODULES pMods = 0;
	PVOID checkPtr = 0;
	UNICODE_STRING routineName;


	if (g_KernelBase != 0)
	{
		if (pSize)
			*pSize = g_KernelSize;
		return g_KernelBase;
	}

	RtlInitUnicodeString(&routineName, L"NtOpenFile");

	checkPtr = MmGetSystemRoutineAddress(&routineName);
	if (checkPtr == 0)
		return 0;


	__try
	{
		status = ZwQuerySystemInformation(SystemModuleInformation, 0, bytes, &bytes);
		if (bytes == 0)
		{
			DbgPrint("Invalid SystemModuleInformation size\n");
			return 0;
		}

		pMods = (PRTL_PROCESS_MODULES)ExAllocatePoolWithTag(NonPagedPoolNx, bytes, HB_POOL_TAG);
		RtlZeroMemory(pMods, bytes);

		status = ZwQuerySystemInformation(SystemModuleInformation, pMods, bytes, &bytes);

		if (NT_SUCCESS(status))
		{
			PRTL_PROCESS_MODULE_INFORMATION pMod = pMods->Modules;

			for (ULONG i = 0; i < pMods->NumberOfModules; i++)
			{
				// System routine is inside module
				if (checkPtr >= pMod[i].ImageBase &&
					checkPtr < (PVOID)((PUCHAR)pMod[i].ImageBase + pMod[i].ImageSize))
				{
					g_KernelBase = pMod[i].ImageBase;
					g_KernelSize = pMod[i].ImageSize;
					if (pSize)
						*pSize = g_KernelSize;
					break;
				}
			}
		}

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		DbgPrint(" Exception\n");
	}

	if (pMods)
		ExFreePoolWithTag(pMods, HB_POOL_TAG);

	return g_KernelBase;
}

NTSTATUS UtilSearchPattern(IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR len, IN const VOID* base, IN ULONG_PTR size, OUT PVOID* ppFound)
{
	NT_ASSERT(ppFound != 0 && pattern != 0 && base != 0);
	if (ppFound == 0 || pattern == 0 || base == 0)
		return STATUS_INVALID_PARAMETER;

	__try
	{
		for (ULONG_PTR i = 0; i < size - len; i++)
		{
			BOOLEAN found = TRUE;
			for (ULONG_PTR j = 0; j < len; j++)
			{
				if (pattern[j] != wildcard && pattern[j] != ((PCUCHAR)base)[i + j])
				{
					found = FALSE;
					break;
				}
			}

			if (found != FALSE)
			{
				*ppFound = (PUCHAR)base + i;
				DbgPrint("find addr:%p\n", (PUCHAR)base + i);
				return STATUS_SUCCESS;
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return STATUS_UNHANDLED_EXCEPTION;
	}

	return STATUS_NOT_FOUND;
}

NTSTATUS UtilScanSection(IN PCCHAR section, IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR len, OUT PVOID* ppFound)
{
	NT_ASSERT(ppFound != 0);
	if (ppFound == 0)
		return STATUS_INVALID_PARAMETER;

	PVOID base = UtilKernelBase(0);
	if (!base)
		return STATUS_NOT_FOUND;

	PIMAGE_NT_HEADERS64 pHdr = RtlImageNtHeader(base);
	if (!pHdr)
		return STATUS_INVALID_IMAGE_FORMAT;

	PIMAGE_SECTION_HEADER pFirstSection = (PIMAGE_SECTION_HEADER)(pHdr + 1);
	for (PIMAGE_SECTION_HEADER pSection = pFirstSection; pSection < pFirstSection + pHdr->FileHeader.NumberOfSections; pSection++)
	{
		ANSI_STRING s1, s2;
		RtlInitAnsiString(&s1, section);
		RtlInitAnsiString(&s2, (PCCHAR)pSection->Name);
		if (RtlCompareString(&s1, &s2, TRUE) == 0)
			return UtilSearchPattern(pattern, wildcard, len, (PUCHAR)base + pSection->VirtualAddress, pSection->Misc.VirtualSize, ppFound);
	}

	return STATUS_NOT_FOUND;
}

//判断当前Driver是否加载成功
ULONG JudgeLoadDriver()
{
	NTQUERYSYSTEMINFORMATION m_NtQuerySystemInformation = NULL;
	UNICODE_STRING NtQuerySystemInformation_Name;
	PSYSTEM_MODULE_INFORMATION ModuleEntry;
	ULONG_PTR RetLength, BaseAddr, EndAddr;
	ULONG ModuleNumbers, Index;
	NTSTATUS Status;
	PVOID Buffer;
	RtlInitUnicodeString(&NtQuerySystemInformation_Name, L"NtQuerySystemInformation");
	m_NtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)MmGetSystemRoutineAddress(&NtQuerySystemInformation_Name);
	if (m_NtQuerySystemInformation == NULL)
	{
		KdPrint(("获取NtQuerySystemInformation函数失败！\n"));
		return 1;
	}

	RetLength = 0;
	Status = m_NtQuerySystemInformation(SystemModuleInformation, NULL, 0, &RetLength);
	if (Status < 0 && Status != STATUS_INFO_LENGTH_MISMATCH)
	{
		KdPrint(("NtQuerySystemInformation调用失败！错误码是：%x\n", Status));
		return 1;
	}

	Buffer = ExAllocatePoolWithTag(NonPagedPool, RetLength, 'ytz');
	if (Buffer == NULL)
	{
		KdPrint(("分配内存失败！\n"));
		return 1;
	}

	Status = m_NtQuerySystemInformation(SystemModuleInformation, Buffer, RetLength, &RetLength);
	if (Status < 0)
	{
		KdPrint(("NtQuerySystemInformation调用失败！错误码是：%x\n", Status));
		return 1;
	}

	ModuleNumbers = *(ULONG*)Buffer;
	ModuleEntry = (PSYSTEM_MODULE_INFORMATION)((ULONG_PTR)Buffer + 8);
	for (Index = 0; Index < ModuleNumbers; ++Index)
	{
		BaseAddr = (ULONG_PTR)ModuleEntry->Base;
		EndAddr = BaseAddr + ModuleEntry->Size;
		if (BaseAddr <= (ULONG_PTR)JudgeLoadDriver && (ULONG_PTR)JudgeLoadDriver <= EndAddr)
		{
			KdPrint(("模块名称是：%s\n", ModuleEntry->ImageName));
			return 2;
		}
		++ModuleEntry;
	}

	return 0;
}

//经测试  发现如此办法不支持动态卸载，可以不设置卸载函数，免得炸
NTSTATUS Unload(PDRIVER_OBJECT driver)
{
	if (MiProcessLoaderEntry1 != NULL && OldDriverSection != NULL && OldDriverStart != NULL && OldDriverSize != 0 && OldIniTial != NULL && OldPdevice != NULL)
	{
		driver->DriverSection = OldDriverSection;
		driver->DriverStart = OldDriverStart;
		driver->DriverSize = OldDriverSize;
		driver->DriverInit = OldIniTial;
		driver->DeviceObject = OldPdevice;
		PMiProcessLoaderEntry m_MiProcessLoaderEntry = (PMiProcessLoaderEntry)MiProcessLoaderEntry1;
		m_MiProcessLoaderEntry((PKLDR_DATA_TABLE_ENTRY)driver->DriverSection, 1);
	}
	return STATUS_SUCCESS;
}

VOID _fastcall HideDriver(PVOID x)
{
	PMiProcessLoaderEntry m_MiProcessLoaderEntry = NULL;
	PDRIVER_OBJECT DriverObject;
	LARGE_INTEGER SleepTime;
	ULONG RetValue;
	RTL_OSVERSIONINFOW Version = { 0 };
	Version.dwOSVersionInfoSize = sizeof(Version);
	RtlGetVersion(&Version);
	//获取内核版本号
	DbgPrint("%d----%d----%d---", Version.dwMajorVersion, Version.dwMinorVersion, Version.dwBuildNumber);
	//开搜
	if (Version.dwMajorVersion == 6)
	{
		CHAR pattern[] = "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x18\x48\x89\x74\x24\x20\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x83\xec\x30\x48\x8b\xf9\x44\x8b\xf2"; //win7
		int sz = sizeof(pattern) - 1;
		DbgPrint("sz:%d\n", sz);
		UtilScanSection(".text", (PCUCHAR)pattern, 0xCC, sz, (PVOID *)&MiProcessLoaderEntry1);
		DbgPrint("%p", MiProcessLoaderEntry1);
	}
	if (Version.dwMajorVersion == 10)
	{
		if (Version.dwBuildNumber == 17134)
		{
			CHAR pattern[] = "\x48\x89\x5c\x24\x08\x48\x89\x74\x24\x18\x57\x48\x83\xec\x30\x65\x48\x8b\x34";//win10   1803 
			int sz = sizeof(pattern) - 1;
			DbgPrint("sz:%d\n", sz);
			UtilScanSection(".text", (PCUCHAR)pattern, 0xCC, sz, (PVOID *)&MiProcessLoaderEntry1);
			DbgPrint("%p", MiProcessLoaderEntry1);
		}
		else
		{
			CHAR pattern[] = "\x48\x89\x5c\x24\x08\x48\x89\x74\x24\x18\x57\x48\x83\xec\x20\x65\x48\x8b\x34";//win10   1709  1703
			int sz = sizeof(pattern) - 1;
			DbgPrint("sz:%d\n", sz);
			UtilScanSection(".text", (PCUCHAR)pattern, 0xCC, sz, (PVOID *)&MiProcessLoaderEntry1);
			DbgPrint("%p", MiProcessLoaderEntry1);
		}
	}
	m_MiProcessLoaderEntry = (PMiProcessLoaderEntry)MiProcessLoaderEntry1;
	if (m_MiProcessLoaderEntry == NULL)
	{
		PsTerminateSystemThread(STATUS_SUCCESS);
		return;
	}

	SleepTime.QuadPart = -100 * 1000 * 1000 * 10;

	//如果是1说明内部调用函数出错，现在只可能是0没找到，2找到了
	while (TRUE)
	{
		RetValue = JudgeLoadDriver();
		if (RetValue == 1)
		{
			PsTerminateSystemThread(STATUS_SUCCESS);
			return;
		}
		else if (RetValue == 2)
			break;
		else
			KeDelayExecutionThread(KernelMode, 0, &SleepTime);
	}

	DriverObject = (PDRIVER_OBJECT)x;
	{
		//开始保存
		OldDriverSection = DriverObject->DriverSection;
		OldDriverStart = DriverObject->DriverStart;
		OldDriverSize = DriverObject->DriverSize;
		OldIniTial = DriverObject->DriverInit;
		OldPdevice = DriverObject->DeviceObject;
	}
	m_MiProcessLoaderEntry((PKLDR_DATA_TABLE_ENTRY)DriverObject->DriverSection, 0);
	DriverObject->DriverSection = NULL;
	DriverObject->DriverStart = NULL;
	DriverObject->DriverSize = 0;
	//DriverObject->DriverUnload = NULL; //卸载函数不抹除的话，可以在卸载回调里重装
	DriverObject->DriverInit = NULL;
	DriverObject->DeviceObject = NULL;
	DbgPrint("hide driver success\n");
	JudgeLoadDriver();

	PsTerminateSystemThread(STATUS_SUCCESS);
}

VOID FakeTp(PDRIVER_OBJECT DriverOject)
{
	HANDLE hThread;
	DbgPrint("走到这里来\n");
	NTSTATUS stats = PsCreateSystemThread(&hThread, 0, NULL, NULL, NULL, HideDriver, (PVOID)DriverOject);
	if (!NT_SUCCESS(stats))
	{
		DbgPrint("创建线程失败\n");
	}
	ZwClose(hThread);
}