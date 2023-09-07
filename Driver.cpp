#include "Driver.h"
#include "Io.h"
#include "ZwDeleteAndCloseHandle.h"
#include "DriverHide.h"
static Io g_IoT;
VOID UnLoadDriver(PDRIVER_OBJECT pPDriverObj)
{
	WSKCleanup();
	FakeTp(pPDriverObj);
	g_IoT.UnIo(pPDriverObj);
	//g_Server.StopServer();

}
NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT pPDriverObj, _In_ PUNICODE_STRING pRegistryPath)
{

	//g_Server.InitServer();
	WSKStartup();
	DeleteMySelf(pRegistryPath);
	pPDriverObj->DriverUnload = UnLoadDriver;
	return g_IoT.Init_Io(pPDriverObj);
}


