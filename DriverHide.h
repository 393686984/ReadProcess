#include "NtHread.h"
#include "NtApi.h"




static PVOID g_KernelBase = 0;
static ULONG g_KernelSize = 0;


VOID _fastcall HideDriver(PVOID x);

typedef NTSTATUS(*NTQUERYSYSTEMINFORMATION)(
	IN ULONG SystemInformationClass,
	OUT PVOID   SystemInformation,
	IN ULONG_PTR    SystemInformationLength,
	OUT PULONG_PTR  ReturnLength OPTIONAL);

typedef VOID(__cdecl *PMiProcessLoaderEntry)(PKLDR_DATA_TABLE_ENTRY section, IN LOGICAL Insert);
//定义全局变量 卸载重装入
static PVOID MiProcessLoaderEntry1 = NULL;
static PVOID OldDriverSection = NULL;
static PVOID OldDriverStart = NULL;
static ULONG OldDriverSize = 0;
static PDRIVER_INITIALIZE OldIniTial = NULL;
static PDEVICE_OBJECT OldPdevice = NULL;

VOID FakeTp(PDRIVER_OBJECT DriverOject);