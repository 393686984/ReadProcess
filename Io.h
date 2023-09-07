#pragma once
#include "NtHread.h"
#include "ReadProcess.h"
#include "Http.h"
#define DRIVER_LINK_NAME    L"\\??\\FeiZou"
#define DEVICE_OBJECT_NAME  L"\\Device\\Be"
#define SETPROCESS 1
#define READPROCESS 2
#define WRITEROCESS 3
#define GETDLLBASSE 4
#define YIYOU 6
#define TP 5
#define CODE_BASE 0x800
#define SET_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN, CODE_BASE, METHOD_BUFFERED, FILE_ANY_ACCESS)
static ReadProcess g_ReadProcess;
static BOOLEAN g_YiYou_Flage = FALSE;
typedef struct Hread {
	ULONG Flage;
	ULONG Addr;
	ULONG WriteBufferAddr;
	ULONG Size;
	ULONG Pid;
	ULONG IsWin10;
}_Hread, *PtrHread;

class Io
{
public:
	NTSTATUS Init_Io(PDRIVER_OBJECT DriverObject);
	VOID UnIo(PDRIVER_OBJECT DriverObject);
private:
	static NTSTATUS PassThroughDispatch(PDEVICE_OBJECT DriverOject, PIRP Irp);
	NTSTATUS CreateIoObject(PDRIVER_OBJECT DriverObject);
	static NTSTATUS ControlThroughDispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp);
};

