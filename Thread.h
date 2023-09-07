#pragma once
#include "NtApi.h"
static PSYSTEM_PROCESS_INFO SystemProcessInfo = NULL;
static PETHREAD pEThread = NULL;
namespace Thread
{
	BOOLEAN ICanbeInsertedAPC_W7(My_PETHREADW7 THOBJECT);
	NTSTATUS InsertApc(PEPROCESS PEOBJCT,PVOID SystemArgument2,PVOID Parameter);

}