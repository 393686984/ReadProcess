#pragma once
#include "ComStruct.h"
#include "ReadProcess.h"
#define COM_PROT L"\\??\\COM2"
static HANDLE g_ComPortHandle = NULL;
static BOOLEAN g_StopComServer = FALSE;
class ComProt
{
public:
	NTSTATUS StartComServer();
	VOID StopComServer();
private:
	NTSTATUS OpenComProt(OUT PHANDLE Handle, WCHAR * ComName = COM_PROT);
	NTSTATUS SendComData(_In_ HANDLE hDevice,
		_In_reads_bytes_opt_(nInBufferSize) PVOID lpInBuffer,
		_In_ DWORD nInBufferSize);

	NTSTATUS RecvComData(_In_ HANDLE hDevice,
		_In_reads_bytes_opt_(nInBufferSize) PVOID lpInBuffer,
		_In_ DWORD nInBufferSize);

private:
	BOOLEAN DeviceIoControl(
		_In_ HANDLE hDevice,
		_In_ DWORD dwIoControlCode,
		_In_reads_bytes_opt_(nInBufferSize) PVOID lpInBuffer,
		_In_ DWORD nInBufferSize,
		_Out_writes_bytes_to_opt_(nOutBufferSize, *lpBytesReturned) PVOID lpOutBuffer,
		_In_ DWORD nOutBufferSize,
		_Out_opt_ LPDWORD lpBytesReturned,
		_Inout_opt_ LPOVERLAPPED lpOverlapped
	);
private:
	NTSTATUS SetupComm(IN HANDLE handle,
		IN ULONG insize,
		IN ULONG outsize);

	    BOOLEAN GetCommTimeouts(
			_In_  HANDLE hFile,
			_Out_ LPCOMMTIMEOUTS lpCommTimeouts
		);

		BOOLEAN SetCommTimeouts(
			_In_ HANDLE hFile,
			_In_ LPCOMMTIMEOUTS lpCommTimeouts
		);

		BOOLEAN GetCommState(
				_In_  HANDLE hFile,
				_Out_ LPDCB lpDCB
			);


		BOOLEAN SetCommState(
				_In_ HANDLE hFile,
				_In_ LPDCB lpDCB
			);

		BOOLEAN  PurgeComm(
				_In_ HANDLE hFile,
				_In_ DWORD dwFlags
			);


		BOOLEAN ClearCommError(
				_In_      HANDLE hFile,
				_Out_opt_ LPDWORD lpErrors,
				_Out_opt_ LPCOMSTAT lpStat
			);

		BOOLEAN  SetCommMask(HANDLE handle,
			DWORD evtmask);

		BOOLEAN WaitCommEvent(
			HANDLE hFile,              /* [in] handle of comm port to wait for */
			LPDWORD lpdwEvents,        /* [out] event(s) that were detected */
			LPOVERLAPPED lpOverlapped); /* [in/out] for Asynchronous waiting */




private:
	static VOID ComServerWokerThread(__in PVOID Context);

private:
	PETHREAD m_EThread = NULL;
	ReadProcess m_ReadProcess;
};

