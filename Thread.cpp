#include "Thread.h"

NTSTATUS ApcpQuerySystemProcessInformation(PSYSTEM_PROCESS_INFO * SystemInfo)
{
	PSYSTEM_PROCESS_INFO pBuffer = NULL;
	ULONG BufferSize = 0;
	ULONG RequiredSize = 0;

	NTSTATUS status = STATUS_SUCCESS;
	while ((status = ZwQuerySystemInformation(
		SystemProcessInformation,
		pBuffer,
		BufferSize,
		&RequiredSize//retn Length
	)) == STATUS_INFO_LENGTH_MISMATCH)
	{
		BufferSize = RequiredSize;
		pBuffer = (PSYSTEM_PROCESS_INFO)ExAllocatePool(PagedPool, BufferSize);
	}

	if (!NT_SUCCESS(status))
	{
		if (pBuffer != NULL)
		{
			ExFreePool(pBuffer);
		}

		return status;
	}
	//retn pSystemProcessInfo
	*SystemInfo = pBuffer;
	return status;
}
BOOLEAN Thread::ICanbeInsertedAPC_W7(My_PETHREADW7 THOBJECT)
{
	BOOLEAN nRet = FALSE;
	if (MmIsAddressValid(THOBJECT) == FALSE) {
		return nRet;
	}
	if (THOBJECT->Tcb.Alertable == 1) {
		nRet = TRUE;
		return nRet;
	}
	return nRet;
}

NTSTATUS Thread::InsertApc(PEPROCESS PEOBJCT, PVOID SystemArgument2, PVOID Parameter)
{
	NTSTATUS Status;	
	PKAPC ExitApc = NULL;
	
	if (!SystemProcessInfo) {
		PSYSTEM_PROCESS_INFO OriginalSystemProcessInfo = NULL;

	
		Status = ApcpQuerySystemProcessInformation(&OriginalSystemProcessInfo);
		if (!NT_SUCCESS(Status)) {
			return Status;
		}

		SystemProcessInfo = OriginalSystemProcessInfo;
		Status = STATUS_NOT_FOUND;
		do
		{
			if (SystemProcessInfo->UniqueProcessId == PsGetProcessId(PEOBJCT))
			{
				Status = STATUS_SUCCESS;
				break;
			}

			SystemProcessInfo = (PSYSTEM_PROCESS_INFO)((PUCHAR)SystemProcessInfo + SystemProcessInfo->NextEntryOffset);
		} while (SystemProcessInfo->NextEntryOffset != 0);

		if (!NT_SUCCESS(Status))
		{
			ExFreePool(OriginalSystemProcessInfo);
			return Status;
		}
	}
STATRT:
	if (MmIsAddressValid(SystemProcessInfo)) {
		if (pEThread == NULL || MmIsAddressValid(pEThread) == FALSE) {
			for (ULONG Index = 0; Index < SystemProcessInfo->NumberOfThreads; ++Index)
			{

				HANDLE UniqueThreadId = SystemProcessInfo->Threads[Index].ClientId.UniqueThread;
				Status = PsLookupThreadByThreadId(UniqueThreadId, &pEThread);
				if (NT_SUCCESS(Status) && pEThread != NULL) {
					ExitApc = (PKAPC)ExAllocatePool(NonPagedPool, sizeof(KAPC));
					KeInitializeApc(ExitApc,
						(PKTHREAD)pEThread,
						OriginalApcEnvironment,
						(PKKERNEL_ROUTINE)SystemArgument2,
						NULL,
						NULL,
						KernelMode,
						NULL);
					ExitApc->NormalContext = Parameter;
					if (KeInsertQueueApc(ExitApc, ExitApc, NULL, 2)) {
						//ObDereferenceObject(pEThread);
						break;
					}
					ObDereferenceObject(pEThread);
					Status = STATUS_UNSUCCESSFUL;
				}
			}
		}
		else {
			ExitApc = (PKAPC)ExAllocatePool(NonPagedPool, sizeof(KAPC));
			KeInitializeApc(ExitApc,
				(PKTHREAD)pEThread,
				OriginalApcEnvironment,
				(PKKERNEL_ROUTINE)SystemArgument2,
				NULL,
				NULL,
				KernelMode,
				NULL);
			ExitApc->NormalContext = Parameter;
			if (KeInsertQueueApc(ExitApc, ExitApc, NULL, 2)) {
				Status = STATUS_SUCCESS;
				return Status;
			}
			goto STATRT;
		}
	}
	return Status;
}
