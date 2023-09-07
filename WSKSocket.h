#pragma once
#pragma warning(push)
#pragma warning(disable:4201) // nameless struct/union
#pragma warning(disable:4214) // bit field types other than int
#include "NtHread.h"

#pragma warning(pop)

#define SOCKET_ERROR -1

#define WPP_CONTROL_GUIDS \
    WPP_DEFINE_CONTROL_GUID(WsktcpCtlGuid, \
        (998bdf51, 0349, 4fbc, 870c, d6130a955a5f), \
        WPP_DEFINE_BIT(TRCERROR) \
        WPP_DEFINE_BIT(TRCINFO) )
#define WSKTCP_SOCKET_POOL_TAG ((ULONG)'sksw')
#define WSKTCP_BUFFER_POOL_TAG ((ULONG)'bksw')
#define WSKTCP_GENERIC_POOL_TAG ((ULONG)'xksw')
#define HTON_SHORT(n) (((((unsigned short)(n) & 0xFFu  )) << 8) | \
					(((unsigned short)(n) & 0xFF00u) >> 8))
#define HTON_LONG(x)	(((((x)& 0xff)<<24) | ((x)>>24) & 0xff) | \
					(((x) & 0xff0000)>>8) | (((x) & 0xff00)<<8))

#ifdef __cplusplus
extern "C"
{
#endif
NTSTATUS NTAPI WSKStartup();

VOID NTAPI WSKCleanup();

PWSK_SOCKET
NTAPI
CreateSocket(
	__in ADDRESS_FAMILY AddressFamily,
	__in USHORT                 SocketType,
	__in ULONG                  Protocol,
	__in ULONG                  Flags

);

NTSTATUS
NTAPI
CloseSocket(
	__in PWSK_SOCKET WskSocket
);

NTSTATUS
NTAPI
Connect(
	__in PWSK_SOCKET        WskSocket,
	__in PSOCKADDR          RemoteAddress
);

PWSK_SOCKET
NTAPI
SocketConnect(
	__in USHORT             SocketType,
	__in ULONG              Protocol,
	__in PSOCKADDR  RemoteAddress,
	__in PSOCKADDR  LocalAddress
);

LONG
NTAPI
Send(
	__in PWSK_SOCKET        WskSocket,
	__in PVOID                      Buffer,
	__in ULONG                      BufferSize,
	__in ULONG                      Flags
);

LONG
NTAPI
SendTo(
	__in PWSK_SOCKET        WskSocket,
	__in PVOID                      Buffer,
	__in ULONG                      BufferSize,
	__in_opt PSOCKADDR      RemoteAddress
);

LONG
NTAPI
Receive(
	__in  PWSK_SOCKET       WskSocket,
	__out PVOID                     Buffer,
	__in  ULONG                     BufferSize,
	__in  ULONG                     Flags
);

LONG
NTAPI
ReceiveFrom(
	__in  PWSK_SOCKET       WskSocket,
	__out PVOID                     Buffer,
	__in  ULONG                     BufferSize,
	__out_opt PSOCKADDR     RemoteAddress,
	__out_opt PULONG        ControlFlags
);

NTSTATUS
NTAPI
Bind(
	__in PWSK_SOCKET        WskSocket,
	__in PSOCKADDR          LocalAddress
);

PWSK_SOCKET
NTAPI
Accept(
	__in PWSK_SOCKET        WskSocket,
	__out_opt PSOCKADDR     LocalAddress,
	__out_opt PSOCKADDR     RemoteAddress
);
#ifdef __cplusplus
}
#endif
