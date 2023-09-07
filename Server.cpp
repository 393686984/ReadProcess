#include "Server.h"



VOID Server::InitServer()
{
	NTSTATUS status = WSKStartup();
	if (!NT_SUCCESS(status)) {
		DbgPrintEx(77, 0, "初始化Socket失败\n");
		return;
	}
	this->m_InitFlage = TRUE;
}

NTSTATUS Server::StartServer()
{
	HANDLE	hThread = NULL;
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	if (this->m_InitFlage == TRUE)
	{
	
		status = PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, TcpListenWorker, NULL);
		if (!NT_SUCCESS(status)) {
			DbgPrintEx(77, 0, "创建系统线程失败。错误代码:%X\n", status);
			return status;
		}
		status = ObReferenceObjectByHandle(hThread, THREAD_ALL_ACCESS, NULL, KernelMode, (PVOID*)&m_EThread, NULL);
		if (NT_SUCCESS(status) == FALSE) {
			DbgPrintEx(77, 0, "获取线程EP结构失败。0x%08X\n", status);
			return status;
		}

		ZwClose(hThread);
	}
	return status;
}

VOID Server::StopServer()
{
	g_StopServer = TRUE;
	KeWaitForSingleObject(m_EThread,
		Executive,
		KernelMode,
		FALSE,
		NULL);
	if (m_EThread != NULL) {
		ObDereferenceObject(m_EThread);
	}
	if (this->m_InitFlage == TRUE) {
           WSKCleanup();
	}


}
VOID Read(PVOID pRxBuf, WSK_SOCKET* paccept_socket)
{

	PSocketRecv Data = reinterpret_cast<PSocketRecv>(pRxBuf);
	PVOID Tmp = ExAllocatePool(NonPagedPool, Data->Size);
	if (NT_SUCCESS(g_ReadProcess.ReadProcessMemory_APC(Data->Addr, Data->Size, Tmp,0)))
	{
		Send(paccept_socket, Tmp, Data->Size, 0);
	}
	else
	{
		int Error = -1;
		Send(paccept_socket, &Error, 4, 0);
	}
	if (Tmp) {
		ExFreePool(Tmp);
		Tmp = NULL;
	}
	memset(pRxBuf, 0, 2048);
}

VOID SetPid(PVOID pRxBuf, WSK_SOCKET* paccept_socket)
{
	ULONG Pid = *(ULONG *)pRxBuf;
	memcpy(&Pid, pRxBuf, 4);
	if (NT_SUCCESS(g_ReadProcess.SetProcess((HANDLE)Pid)))
	{
		Send(paccept_socket, "1", 1, 0);
	}
	else
	{
		Send(paccept_socket, "0", 1, 0);
	}
	memset(pRxBuf, 0, 2048);

}
VOID GetDll(PVOID pRxBuf, WSK_SOCKET* paccept_socket)
{
	char *DllName = (char *)pRxBuf;
	ULONGLONG DllAddr = g_ReadProcess.GetModuleBaseAddr(DllName);
    Send(paccept_socket,(PVOID)&DllAddr, 8, 0);
	memset(pRxBuf, 0, 2048);
}
VOID Server::TcpListenWorker(PVOID Context)
{
	
	WSK_SOCKET* paccept_socket = NULL;
	SOCKADDR_IN 	LocalAddress = {0};	
	SOCKADDR_IN RemoteAddress = { 0 };
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	CHAR* pRxBuf = (CHAR*)ExAllocatePoolWithTag(NonPagedPool, 2048, 'dddd');
	PWSK_SOCKET TcpSocket = CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, WSK_FLAG_LISTEN_SOCKET);

	if (TcpSocket == NULL) {
		DbgPrintEx(77, 0, "创建Socket失败\n");
		goto $EXIT;
	}

	LocalAddress.sin_family = AF_INET;
	LocalAddress.sin_addr.s_addr = INADDR_ANY;
	LocalAddress.sin_port = HTON_SHORT(40000); //40000

	status = Bind(TcpSocket, (PSOCKADDR)&LocalAddress);
	if (!NT_SUCCESS(status)) {
		DbgPrintEx(77, 0, "绑定失败错误代码:%X\n", status);
		goto $EXIT;
	}
	while (1)
	{
		paccept_socket = Accept(TcpSocket, (PSOCKADDR)&LocalAddress, (PSOCKADDR)&RemoteAddress);
		if (paccept_socket == NULL) {
			DbgPrintEx(77, 0, "一次链接失败\n");
			continue;
		}
		break;
	}
	while (!g_StopServer)
	{
		int Len = Receive(paccept_socket, pRxBuf, 2048, 0);
		switch (Len)
		{
		case 8:
		{
			Read(pRxBuf, paccept_socket);
			break;
		}

		case 4:
		{
			SetPid(pRxBuf, paccept_socket);
			break;
		}

		case 1024:
		{

			GetDll(pRxBuf, paccept_socket);
			break;
		}

		default:
			break;
		}



		if (g_StopServer) {
			goto $EXIT;
		}
	}

$EXIT:

	if (TcpSocket) {
		CloseSocket(TcpSocket);
		TcpSocket = NULL;
	}
	if (paccept_socket) {
		CloseSocket(paccept_socket);
		paccept_socket = NULL;
	}

	if (pRxBuf != NULL) {
		ExFreePool(pRxBuf);
	}

	g_ReadProcess.UnReadProcess();

	PsTerminateSystemThread(STATUS_SUCCESS);

	return;
}
