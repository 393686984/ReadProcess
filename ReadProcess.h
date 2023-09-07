#pragma once
#include "NtApi.h"
#include "Thread.h"
static KEVENT g_kEvent;
typedef struct SocketRecv
{
	ULONG Addr;
	ULONG Size;
}CSocketRecv, *PSocketRecv;


typedef struct _RWPM_INFO
{
	void* Address;
	void* Buffer;
	SIZE_T Length;
	SIZE_T Type;//0=read;1=write
	KEVENT Event;
}RWPM_INFO, *PRWPM_INFO;

class ReadProcess;
struct ThreadGetDll
{
	char *DllName;
	ULONGLONG BaseAddr;
	ReadProcess *Ob;
};
class ReadProcess
{
public:

	NTSTATUS SetProcess(HANDLE Pid);
	NTSTATUS ReadProcessMemory(IN ULONGLONG Addr, IN ULONG Size,OUT PVOID Buffer);
	NTSTATUS ReadProcessMemory_APC(IN ULONGLONG Addr, IN ULONG Size, OUT PVOID Buffer,int Type);
	BOOLEAN WIN10_ReadProcessMemory(ULONG Addr, UINT_PTR bytestoread, PVOID output);
	VOID WIN10_WriteProcessMemory(ULONG Addr, UINT_PTR bytestoread, PVOID Buffer);
	ULONGLONG GetModuleBaseAddr(_In_ char* pModuleName);
	ULONGLONG IoGetModeuleBaseAddr(_In_ char* pModuleName);
	VOID TpPr(HANDLE Pid);
private:
	NTSTATUS MMCopyProcessMemory(PEPROCESS tagetProcess, PVOID addr, SIZE_T size, PVOID data);
	ULONGLONG  GetModuleBaseWow64(_In_ PEPROCESS pEProcess, _In_ UNICODE_STRING usModuleName);
	BOOLEAN WIN10_ReadProcess(ULONG Addr, UINT_PTR bytestoread, PVOID output);
	VOID WIN10_WritedProcess(ULONG Addr, UINT_PTR bytestoread, PVOID Buffer);
	static VOID GetDllBase(PVOID Ob);
public:
	VOID UnReadProcess();

private:
	PEPROCESS m_Peprocess;

	
};
