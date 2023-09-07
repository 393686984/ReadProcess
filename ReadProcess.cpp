#include "ReadProcess.h"

VOID SelfTerminateProcess(IN struct _KAPC *Apc, IN OUT PKNORMAL_ROUTINE *NormalRoutine, IN OUT PVOID *NormalContext, IN OUT PVOID *SystemArgument1, IN OUT PVOID *SystemArgument2)
{
	PRWPM_INFO pInfo = (PRWPM_INFO)(Apc->NormalContext);
	if (!MmIsAddressValid(pInfo->Address)) {
		goto $EXIT;
	}
	if (pInfo->Type == 0)
	{
		_try
		{
				RtlCopyMemory(pInfo->Buffer,pInfo->Address,pInfo->Length);
		}
			_except(1)
		{
			goto $EXIT;
		}
	}
	else
	{
		_try
		{
				_disable();
				__writecr0(__readcr0() & 0xfffffffffffeffff);
				RtlCopyMemory(pInfo->Address,pInfo->Buffer,pInfo->Length);
				__writecr0(__readcr0() | 0x10000);
				_enable();

		}
			_except(1)
		{
			goto $EXIT;
		}
	}
	pInfo->Type = 2;
	goto $EXIT;

$EXIT:
	KeSetEvent(&(pInfo->Event), IO_NO_INCREMENT, FALSE);
	
}

ULONGLONG ReadProcess::GetModuleBaseWow64(_In_ PEPROCESS pEProcess, _In_ UNICODE_STRING usModuleName)
{

	ULONGLONG BaseAddr = 0;
	KAPC_STATE KAPC = { 0 };
	KeStackAttachProcess(pEProcess, &KAPC);
	PPEB32 pPeb = (PPEB32)PsGetProcessWow64Process(pEProcess);
	if (pPeb == NULL || pPeb->Ldr == 0)
	{
		KeUnstackDetachProcess(&KAPC);
		return 0;
	}
	// init module name

	// Ergodic ModuleList
	for (PLIST_ENTRY32 pListEntry = (PLIST_ENTRY32)((PPEB_LDR_DATA32)pPeb->Ldr)->InLoadOrderModuleList.Flink;
		pListEntry != &((PPEB_LDR_DATA32)pPeb->Ldr)->InLoadOrderModuleList;
		pListEntry = (PLIST_ENTRY32)pListEntry->Flink)
	{
		PLDR_DATA_TABLE_ENTRY32 LdrEntry = CONTAINING_RECORD(pListEntry, LDR_DATA_TABLE_ENTRY32, InLoadOrderLinks);

		if (LdrEntry->BaseDllName.Buffer == NULL)
		{
			continue;
		}
		// Current Module Name in ListFlink
		UNICODE_STRING usCurrentName = { 0 };
		RtlInitUnicodeString(&usCurrentName, (PWCHAR)LdrEntry->BaseDllName.Buffer);
		// cmp module name
		if (RtlEqualUnicodeString(&usModuleName, &usCurrentName, TRUE))
		{	
	
			BaseAddr = (ULONGLONG)LdrEntry->DllBase;
			KeUnstackDetachProcess(&KAPC);
		
			return BaseAddr;
		}
	}

	KeUnstackDetachProcess(&KAPC);
	return 0;
}

BOOLEAN ReadProcess::WIN10_ReadProcess(ULONG Addr, UINT_PTR bytestoread, PVOID output)
{
	NTSTATUS nStatus;
	BOOLEAN Flage = TRUE;
	KAPC_STATE KAPC = { 0 };
	PHYSICAL_ADDRESS PhyAddr;
	BOOLEAN bIsAttached = FALSE;
	KeStackAttachProcess(this->m_Peprocess, &KAPC);
	bIsAttached = TRUE;
	PhyAddr = MmGetPhysicalAddress((PVOID)Addr);
	if (PhyAddr.QuadPart == 0)
	{
		Flage = FALSE;
		goto TABLE1;
	}
	PVOID Temp = MmMapIoSpace(PhyAddr, bytestoread, (MEMORY_CACHING_TYPE)0);
	if (Temp == NULL)
	{
		Flage = FALSE;
		goto TABLE1;
	}
	RtlCopyMemory(output, Temp, bytestoread);
	MmUnmapIoSpace(Temp, bytestoread);

TABLE1:
	if (bIsAttached != FALSE)
	{
		KeUnstackDetachProcess(&KAPC);
	}
	return Flage;
}
KIRQL Open()  // ¹Ø
{
	KIRQL irql = KeRaiseIrqlToDpcLevel();
	UINT64 cr0 = __readcr0();
	cr0 &= 0xfffffffffffeffff;
	__writecr0(cr0);
	_disable();
	return irql;
}
void Close(KIRQL irql) //¿ª
{
	UINT64 cr0 = __readcr0();
	cr0 |= 0x10000;
	_enable();
	__writecr0(cr0);
	KeLowerIrql(irql);
}
VOID ReadProcess::WIN10_WritedProcess(ULONG Addr, UINT_PTR bytestoread, PVOID Buffer)
{
	NTSTATUS nStatus;
	KAPC_STATE KAPC = { 0 };
	PHYSICAL_ADDRESS PhyAddr;
	BOOLEAN bIsAttached = FALSE;
	KeStackAttachProcess(this->m_Peprocess, &KAPC);
	bIsAttached = TRUE;
	PhyAddr = MmGetPhysicalAddress((PVOID)Addr);
	PVOID Temp = MmMapIoSpace(PhyAddr, bytestoread, (MEMORY_CACHING_TYPE)TRUE);
	if (Temp == NULL)
		goto TABLE1;
	KIRQL Irq = Open();
	RtlCopyMemory(Temp, Buffer, bytestoread);
	Close(Irq);
	MmUnmapIoSpace(Temp, bytestoread);

TABLE1:
	if (bIsAttached != FALSE)
	{
		KeUnstackDetachProcess(&KAPC);
	}

}

VOID CHAR_TO_UNICODE_STRING(PCHAR ch, PUNICODE_STRING unicodeBuffer)
{
	ANSI_STRING ansiBuffer;
	UNICODE_STRING buffer_proc;
	ULONG len = strlen(ch);

	ansiBuffer.Buffer = ch;
	ansiBuffer.Length = ansiBuffer.MaximumLength = (USHORT)len;
	RtlAnsiStringToUnicodeString(unicodeBuffer, &ansiBuffer, TRUE);
}
NTSTATUS ReadProcess::SetProcess(HANDLE Pid)
{

	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	if (this->m_Peprocess != NULL)
	{
		ObDereferenceObject(this->m_Peprocess);
		this->m_Peprocess = NULL;
	}
	Status = PsLookupProcessByProcessId(Pid, &this->m_Peprocess);
	return Status;

}

NTSTATUS ReadProcess::MMCopyProcessMemory(PEPROCESS tagetProcess, PVOID addr, SIZE_T size, PVOID data)
{
	SIZE_T BytesRead = 0;
	NTSTATUS Status = MmCopyVirtualMemory(tagetProcess,
		addr,
		this->m_Peprocess,
		data,
		size,
		KernelMode,
		&BytesRead);
	return Status;
}


NTSTATUS ReadProcess::ReadProcessMemory(IN ULONGLONG Addr, IN ULONG Size, OUT PVOID Buffer)
{
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	if (this->m_Peprocess != NULL) {
		Status = MMCopyProcessMemory(this->m_Peprocess, (PVOID)Addr, Size, Buffer);
	}
	return Status;
	
}

NTSTATUS ReadProcess::ReadProcessMemory_APC(IN ULONGLONG Addr, IN ULONG Size, OUT PVOID Buffer,int Type)
{
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	if (MmIsAddressValid(this->m_Peprocess))
	{
		if (this->m_Peprocess != NULL) {
			PRWPM_INFO pInfo = (PRWPM_INFO)ExAllocatePool(NonPagedPool, sizeof(RWPM_INFO));
			pInfo->Address = (PVOID)Addr;
			pInfo->Buffer = Buffer;
			pInfo->Length = Size;
			pInfo->Type = Type;
			KeInitializeEvent(&(pInfo->Event), NotificationEvent, TRUE);
			KeClearEvent(&(pInfo->Event));
			Status = Thread::InsertApc(m_Peprocess, SelfTerminateProcess, pInfo);
			if (NT_SUCCESS(Status)) {
				LARGE_INTEGER interval = { 0 };
				interval.QuadPart = -10000;
				interval.QuadPart *= 1000;
				Status = KeWaitForSingleObject(&(pInfo->Event), Executive, KernelMode, 0, &interval);
				if (pInfo->Type != 2) {
					Status = STATUS_UNSUCCESSFUL;
				}
			}

			if (pInfo) {

				ExFreePool(pInfo);
				pInfo = NULL;
			}
		}
	}

	return Status;
	
}

BOOLEAN ReadProcess::WIN10_ReadProcessMemory(ULONG Addr, UINT_PTR bytestoread, PVOID output)
{
	if (!this->m_Peprocess) {
		return FALSE;
	}
	if (!MmIsAddressValid(output)) {
		return FALSE;
	}

	return this->WIN10_ReadProcess(Addr, bytestoread, output);
}

VOID ReadProcess::WIN10_WriteProcessMemory(ULONG Addr, UINT_PTR bytestoread, PVOID Buffer)
{
	if (!this->m_Peprocess) {
		return;
	}
	if (!MmIsAddressValid(Buffer)) {
		return;
	}
	PVOID t_Buffer = ExAllocatePool(NonPagedPool, bytestoread);
	RtlCopyMemory(t_Buffer, Buffer, bytestoread);
	this->WIN10_WritedProcess(Addr, bytestoread, t_Buffer);
	ExFreePool(t_Buffer);
}



ULONGLONG ReadProcess::GetModuleBaseAddr(char  *pModuleName)
{
	UNICODE_STRING ModuleName = { 0 };
	if (!this->m_Peprocess) {
		return 0;
	}
	CHAR_TO_UNICODE_STRING(pModuleName, &ModuleName);

	return this->GetModuleBaseWow64(m_Peprocess, ModuleName);
}
VOID ReadProcess::GetDllBase(PVOID Ob)
{
	struct ThreadGetDll *Thread = (struct ThreadGetDll *)Ob;
	Thread->BaseAddr = Thread->Ob->GetModuleBaseAddr(Thread->DllName);
	KeSetEvent(&g_kEvent, 0, TRUE);
	PsTerminateSystemThread(STATUS_SUCCESS);
}
ULONGLONG ReadProcess::IoGetModeuleBaseAddr(char * pModuleName)
{
	if (!MmIsAddressValid((PVOID)pModuleName)) {
		return 0;
	}
	struct ThreadGetDll Thread;
	HANDLE     hThread;
	NTSTATUS status;
	char* t_Buffer = (char*)ExAllocatePool(NonPagedPool, strlen(pModuleName));
	RtlCopyMemory(t_Buffer, pModuleName, strlen(pModuleName));
	Thread.DllName = t_Buffer;
	Thread.Ob = this;
	KeInitializeEvent(&g_kEvent, SynchronizationEvent, FALSE);
	status = PsCreateSystemThread(&hThread, 0, NULL, NULL, NULL, GetDllBase, &Thread);
	if (NT_SUCCESS(status))
	{
		ZwClose(hThread);
		KeWaitForSingleObject(&g_kEvent, Executive, KernelMode, FALSE, NULL);
	}
	ExFreePool(t_Buffer);
	return Thread.BaseAddr;
}

VOID ReadProcess::TpPr(HANDLE Pid)
{
	if (!this->m_Peprocess) {
		return;
	}
	My_PEPROCESSW7 Pe;
	My_PEPROCESSW7 Game = (My_PEPROCESSW7)this->m_Peprocess;
	if (!NT_SUCCESS(PsLookupProcessByProcessId(Pid, (PEPROCESS *)&Pe))) {
		return;
	}
	Pe->UniqueProcessId = Game->UniqueProcessId;
	ObDereferenceObject(Pe);
}

VOID ReadProcess::UnReadProcess()
{
	if (this->m_Peprocess != NULL)
	{
		ObDereferenceObject(this->m_Peprocess);
		this->m_Peprocess = NULL;
	}

}

