#pragma once
#include "ReadProcess.h"
#include "WSKSocket.h"

static BOOLEAN g_StopServer = FALSE;
static ReadProcess g_ReadProcess;

class Server
{
public:
	VOID InitServer();
	NTSTATUS StartServer();
	VOID StopServer();
private:
	static VOID TcpListenWorker(__in PVOID Context);
private:
	BOOLEAN m_InitFlage = FALSE;
    PETHREAD m_EThread = NULL;
};