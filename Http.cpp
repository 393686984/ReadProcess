#include "Http.h"
#include<stdio.h>
char *join(const char *a, const char *b) {
	char *c = (char *)ExAllocatePool(NonPagedPool, strlen(a) + strlen(b) + 1);
	if (c == NULL)
	{
		DbgPrintEx(77, 0, "分配空间失败");
		return NULL;
	}
	char *tempc = c;
	while (*a != '\0') {
		*c++ = *a++;
	}
	while ((*c++ = *b++) != '\0') {
		;

	}
	return tempc;
}
long change_uint(long a, long b, long c, long d) {
	long address = 0;
	address |= d << 24;
	address |= c << 16;
	address |= b << 8;
	address |= a;
	return address;
}

VOID Post(IN ULONG IP1, IN ULONG IP2, IN ULONG IP3, IN ULONG IP4, IN const char * url, IN const char * path, IN ULONG Port, IN const char * PostData, IN const char * Other, OUT PVOID RecvBuffer, IN ULONG RecvSize)
{
	if (MmIsAddressValid((PVOID)PostData) == FALSE)
		return;
	char DataBuffer[100] = "";
	char * HttpBuffer = join("POST /", path);
	HttpBuffer = join(HttpBuffer, " HTTP/1.1\n");
	HttpBuffer = join(HttpBuffer, "Host: ");
	HttpBuffer = join(HttpBuffer, url);
	HttpBuffer = join(HttpBuffer, "\n");
	HttpBuffer = join(HttpBuffer, "Proxy-Connection: keep-alive\n");
	HttpBuffer = join(HttpBuffer, "User-Agent: Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.153 Safari/537.36 SE 2.X MetaSr 1.0\n");
	sprintf(DataBuffer, "Content-Length: %d\n", (int)strlen(PostData));
	HttpBuffer = join(HttpBuffer, DataBuffer);
	HttpBuffer = join(HttpBuffer, Other);
	HttpBuffer = join(HttpBuffer, "Content-Type: application/x-www-form-urlencoded\n\n");

	HttpBuffer = join(HttpBuffer, PostData);



	NTSTATUS 		status = STATUS_SUCCESS;
	SOCKADDR_IN 	LocalAddress = { 0, };
	SOCKADDR_IN 	RemoteAddress = { 0, };

	PWSK_SOCKET TcpSocket = CreateSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, WSK_FLAG_CONNECTION_SOCKET);
	if (TcpSocket == NULL) {
		DbgPrintEx(77, 0, "创建SOCKET失败\n");
		return;
	}

	LocalAddress.sin_family = AF_INET;
	LocalAddress.sin_addr.s_addr = INADDR_ANY;
	status = Bind(TcpSocket, (PSOCKADDR)&LocalAddress);
	if (!NT_SUCCESS(status)) {
		DbgPrintEx(77, 0, "绑定失败 0x%08X\n", status);
		CloseSocket(TcpSocket);
		return;
	}

	RemoteAddress.sin_family = AF_INET;
	RemoteAddress.sin_addr.s_addr = change_uint(IP1, IP2, IP3, IP4);
	RemoteAddress.sin_port = HTON_SHORT(Port);

	status = Connect(TcpSocket, (PSOCKADDR)&RemoteAddress);
	if (!NT_SUCCESS(status)) {
		DbgPrint("链接目标服务器失败 0x%08X\n", status);
		CloseSocket(TcpSocket);
		return;
	}

	Send(TcpSocket, HttpBuffer, strlen(HttpBuffer), 0);
	if (MmIsAddressValid((PVOID)RecvBuffer))
	{
		Receive(TcpSocket, RecvBuffer, RecvSize, 0);

	}
	CloseSocket(TcpSocket);
}
