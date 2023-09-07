#include "ComProt.h"

NTSTATUS ComProt::StartComServer()
{

	HANDLE	hThread = NULL;
	NTSTATUS status = PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, ComServerWokerThread, this);
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

	return status;

}

VOID ComProt::StopComServer()
{		
	g_StopComServer = TRUE;
	KeWaitForSingleObject(m_EThread,
		Executive,
		KernelMode,
		FALSE,
		NULL);

	if (g_ComPortHandle != NULL) {
		ZwClose(g_ComPortHandle);
		g_ComPortHandle = NULL;
	}




}

NTSTATUS ComProt::OpenComProt(OUT PHANDLE Handle, WCHAR * ComName)
{
	OBJECT_ATTRIBUTES object_attributes;
	UNICODE_STRING ufile_name;
	IO_STATUS_BLOCK IoStatus;
	RtlInitUnicodeString(&ufile_name, ComName);
	InitializeObjectAttributes(
		&object_attributes,
		&ufile_name,
		OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
		NULL,
		NULL);

	return NtCreateFile(Handle,
		GENERIC_READ | GENERIC_WRITE,
		&object_attributes,
		&IoStatus,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		FILE_OPEN,
		FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0);

}

NTSTATUS ComProt::SendComData(HANDLE hDevice, PVOID lpInBuffer, DWORD nInBufferSize)
{
	IO_STATUS_BLOCK Io;
	ULONG Len;
	PurgeComm(hDevice, PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT);
    return NtWriteFile(g_ComPortHandle, 
		NULL, 
		NULL, 
		NULL, 
		&Io,
		lpInBuffer,
		nInBufferSize,
		0,
		NULL);

}

NTSTATUS ComProt::RecvComData(HANDLE hDevice, PVOID lpInBuffer, DWORD nInBufferSize)
{
	IO_STATUS_BLOCK Io;
	ULONG Len;
	NTSTATUS Status = NtReadFile(hDevice,
		NULL,
		NULL,
		NULL,
		&Io,
		lpInBuffer,
		nInBufferSize,
		NULL,
		0);
	PurgeComm(g_ComPortHandle, PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT);
	return Status;

}






BOOLEAN ComProt::DeviceIoControl(
	_In_ HANDLE hDevice,
	_In_ DWORD dwIoControlCode,
	_In_reads_bytes_opt_(nInBufferSize) PVOID lpInBuffer,
	_In_ DWORD nInBufferSize,
	_Out_writes_bytes_to_opt_(nOutBufferSize, *lpBytesReturned) PVOID lpOutBuffer,
	_In_ DWORD nOutBufferSize,
	_Out_opt_ LPDWORD lpBytesReturned,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
) {
	NTSTATUS RC;
	BOOLEAN DevIoCtl = TRUE;
	IO_STATUS_BLOCK Iosb;

	if (dwIoControlCode >> 16 == FILE_DEVICE_FILE_SYSTEM) {
		DevIoCtl = FALSE;
	}
	else {
		DevIoCtl = TRUE;
	}

	if (DevIoCtl){
		RC = NtDeviceIoControlFile(hDevice,
			NULL,
			NULL,
			NULL,
			&Iosb,
			dwIoControlCode,
			lpInBuffer,
			nInBufferSize,
			lpOutBuffer,
			nOutBufferSize);
	}
	else {
		RC = NtFsControlFile(
			hDevice,
			NULL,
			NULL,        
			NULL,           
			&Iosb,
			dwIoControlCode, 
			lpInBuffer,    
			nInBufferSize,
			lpOutBuffer,    
			nOutBufferSize   
		);
	}

	if (RC == STATUS_PENDING) {
		RC = ZwWaitForSingleObject(hDevice, FALSE, NULL);
		if (NT_SUCCESS(RC)) {
			RC = Iosb.Status;
		}
	}

	if (MmIsAddressValid(lpBytesReturned))
	{
		if (NT_SUCCESS(RC)) {
			*lpBytesReturned = (DWORD)Iosb.Information;
			return TRUE;
		}
		else {
		
			if (!NT_ERROR(RC)) {
				*lpBytesReturned = (DWORD)Iosb.Information;
			}
			return FALSE;
		}
	}

	if (NT_SUCCESS(RC)) {

		if (NT_SUCCESS(RC)) {
			return TRUE;
		}
		else {
			if (!NT_ERROR(RC))
			{
				return FALSE;
			}
		}

	}
	return FALSE;

}

NTSTATUS ComProt::SetupComm(IN HANDLE handle, IN ULONG insize, IN ULONG outsize)
{

	SERIAL_QUEUE_SIZE   sqs;
	DWORD dwBytesReturned;
	sqs.InSize = insize;
	sqs.OutSize = outsize;
	return DeviceIoControl(handle,
		IOCTL_SERIAL_SET_QUEUE_SIZE,
		&sqs, 
		sizeof(sqs),
		NULL, 
		0,
		&dwBytesReturned,
		NULL);



}

BOOLEAN ComProt::GetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts)
{
	SERIAL_TIMEOUTS     st;
	DWORD dwBytesReturned;

	if (!lpCommTimeouts){
		return FALSE;
	}

	if (!DeviceIoControl(hFile, IOCTL_SERIAL_GET_TIMEOUTS,
		NULL, 0, &st, sizeof(st), &dwBytesReturned, NULL)) {
		return FALSE;
	}
	lpCommTimeouts->ReadIntervalTimeout = st.ReadIntervalTimeout;
	lpCommTimeouts->ReadTotalTimeoutMultiplier = st.ReadTotalTimeoutMultiplier;
	lpCommTimeouts->ReadTotalTimeoutConstant = st.ReadTotalTimeoutConstant;
	lpCommTimeouts->WriteTotalTimeoutMultiplier = st.WriteTotalTimeoutMultiplier;
	lpCommTimeouts->WriteTotalTimeoutConstant = st.WriteTotalTimeoutConstant;
	return TRUE;
}

BOOLEAN ComProt::SetCommTimeouts(HANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts)
{

	SERIAL_TIMEOUTS     st;
	DWORD dwBytesReturned;

	if (lpCommTimeouts == NULL)
	{
		return FALSE;
	}
	st.ReadIntervalTimeout = lpCommTimeouts->ReadIntervalTimeout;
	st.ReadTotalTimeoutMultiplier = lpCommTimeouts->ReadTotalTimeoutMultiplier;
	st.ReadTotalTimeoutConstant = lpCommTimeouts->ReadTotalTimeoutConstant;
	st.WriteTotalTimeoutMultiplier = lpCommTimeouts->WriteTotalTimeoutMultiplier;
	st.WriteTotalTimeoutConstant = lpCommTimeouts->WriteTotalTimeoutConstant;

	return DeviceIoControl(hFile, IOCTL_SERIAL_SET_TIMEOUTS,
		&st, sizeof(st), NULL, 0, &dwBytesReturned, NULL);
}

BOOLEAN ComProt::GetCommState(HANDLE hFile, LPDCB lpDCB)
{
	SERIAL_BAUD_RATE    sbr;
	SERIAL_LINE_CONTROL slc;
	SERIAL_HANDFLOW     shf;
	SERIAL_CHARS        sc;
	DWORD dwBytesReturned;



	if (!lpDCB)
	{
	
		return FALSE;
	}

	if (!DeviceIoControl(hFile, IOCTL_SERIAL_GET_BAUD_RATE,
		NULL, 0, &sbr, sizeof(sbr), &dwBytesReturned, NULL) ||
		!DeviceIoControl(hFile, IOCTL_SERIAL_GET_LINE_CONTROL,
			NULL, 0, &slc, sizeof(slc), &dwBytesReturned, NULL) ||
		!DeviceIoControl(hFile, IOCTL_SERIAL_GET_HANDFLOW,
			NULL, 0, &shf, sizeof(shf), &dwBytesReturned, NULL) ||
		!DeviceIoControl(hFile, IOCTL_SERIAL_GET_CHARS,
			NULL, 0, &sc, sizeof(sc), &dwBytesReturned, NULL))
		return FALSE;

	memset(lpDCB, 0, sizeof(*lpDCB));
	lpDCB->DCBlength = sizeof(*lpDCB);

	lpDCB->fBinary = 1;
	lpDCB->fParity = 0;

	lpDCB->BaudRate = sbr.BaudRate;

	lpDCB->StopBits = slc.StopBits;
	lpDCB->Parity = slc.Parity;
	lpDCB->ByteSize = slc.WordLength;

	if (shf.ControlHandShake & SERIAL_CTS_HANDSHAKE)    lpDCB->fOutxCtsFlow = 1;
	if (shf.ControlHandShake & SERIAL_DSR_HANDSHAKE)    lpDCB->fOutxDsrFlow = 1;
	switch (shf.ControlHandShake & (SERIAL_DTR_CONTROL | SERIAL_DTR_HANDSHAKE))
	{
	case 0:                     lpDCB->fDtrControl = DTR_CONTROL_DISABLE; break;
	case SERIAL_DTR_CONTROL:    lpDCB->fDtrControl = DTR_CONTROL_ENABLE; break;
	case SERIAL_DTR_HANDSHAKE:  lpDCB->fDtrControl = DTR_CONTROL_HANDSHAKE; break;
	}
	switch (shf.FlowReplace & (SERIAL_RTS_CONTROL | SERIAL_RTS_HANDSHAKE))
	{
	case 0:                     lpDCB->fRtsControl = RTS_CONTROL_DISABLE; break;
	case SERIAL_RTS_CONTROL:    lpDCB->fRtsControl = RTS_CONTROL_ENABLE; break;
	case SERIAL_RTS_HANDSHAKE:  lpDCB->fRtsControl = RTS_CONTROL_HANDSHAKE; break;
	case SERIAL_RTS_CONTROL | SERIAL_RTS_HANDSHAKE:
		lpDCB->fRtsControl = RTS_CONTROL_TOGGLE; break;
	}
	if (shf.ControlHandShake & SERIAL_DSR_SENSITIVITY)  lpDCB->fDsrSensitivity = 1;
	if (shf.ControlHandShake & SERIAL_ERROR_ABORT)      lpDCB->fAbortOnError = 1;
	if (shf.FlowReplace & SERIAL_ERROR_CHAR)            lpDCB->fErrorChar = 1;
	if (shf.FlowReplace & SERIAL_NULL_STRIPPING)        lpDCB->fNull = 1;
	if (shf.FlowReplace & SERIAL_XOFF_CONTINUE)         lpDCB->fTXContinueOnXoff = 1;
	lpDCB->XonLim = (WORD)shf.XonLimit;
	lpDCB->XoffLim = (WORD)shf.XoffLimit;

	if (shf.FlowReplace & SERIAL_AUTO_TRANSMIT) lpDCB->fOutX = 1;
	if (shf.FlowReplace & SERIAL_AUTO_RECEIVE)  lpDCB->fInX = 1;

	lpDCB->EofChar = sc.EofChar;
	lpDCB->ErrorChar = sc.ErrorChar;
	lpDCB->EvtChar = sc.EventChar;
	lpDCB->XonChar = sc.XonChar;
	lpDCB->XoffChar = sc.XoffChar;



	return TRUE;
}

BOOLEAN ComProt::SetCommState(HANDLE hFile, LPDCB lpDCB)
{
	SERIAL_BAUD_RATE           sbr;
	SERIAL_LINE_CONTROL        slc;
	SERIAL_HANDFLOW            shf;
	SERIAL_CHARS               sc;
	DWORD dwBytesReturned;

	if (lpDCB == NULL)
	{
	
		return FALSE;
	}

	sbr.BaudRate = lpDCB->BaudRate;

	slc.StopBits = lpDCB->StopBits;
	slc.Parity = lpDCB->Parity;
	slc.WordLength = lpDCB->ByteSize;

	shf.ControlHandShake = 0;
	shf.FlowReplace = 0;
	if (lpDCB->fOutxCtsFlow)      shf.ControlHandShake |= SERIAL_CTS_HANDSHAKE;
	if (lpDCB->fOutxDsrFlow)      shf.ControlHandShake |= SERIAL_DSR_HANDSHAKE;
	switch (lpDCB->fDtrControl)
	{
	case DTR_CONTROL_DISABLE:                                                  break;
	case DTR_CONTROL_ENABLE:      shf.ControlHandShake |= SERIAL_DTR_CONTROL;  break;
	case DTR_CONTROL_HANDSHAKE:   shf.ControlHandShake |= SERIAL_DTR_HANDSHAKE; break;
	default:
		return FALSE;
	}
	switch (lpDCB->fRtsControl)
	{
	case RTS_CONTROL_DISABLE:                                                  break;
	case RTS_CONTROL_ENABLE:      shf.FlowReplace |= SERIAL_RTS_CONTROL;       break;
	case RTS_CONTROL_HANDSHAKE:   shf.FlowReplace |= SERIAL_RTS_HANDSHAKE;     break;
	case RTS_CONTROL_TOGGLE:      shf.FlowReplace |= SERIAL_RTS_CONTROL |
		SERIAL_RTS_HANDSHAKE;     break;
	default:
		return FALSE;
	}
	if (lpDCB->fDsrSensitivity)   shf.ControlHandShake |= SERIAL_DSR_SENSITIVITY;
	if (lpDCB->fAbortOnError)     shf.ControlHandShake |= SERIAL_ERROR_ABORT;

	if (lpDCB->fErrorChar)        shf.FlowReplace |= SERIAL_ERROR_CHAR;
	if (lpDCB->fNull)             shf.FlowReplace |= SERIAL_NULL_STRIPPING;
	if (lpDCB->fTXContinueOnXoff) shf.FlowReplace |= SERIAL_XOFF_CONTINUE;
	if (lpDCB->fOutX)             shf.FlowReplace |= SERIAL_AUTO_TRANSMIT;
	if (lpDCB->fInX)              shf.FlowReplace |= SERIAL_AUTO_RECEIVE;

	shf.XonLimit = lpDCB->XonLim;
	shf.XoffLimit = lpDCB->XoffLim;

	sc.EofChar = lpDCB->EofChar;
	sc.ErrorChar = lpDCB->ErrorChar;
	sc.BreakChar = 0;
	sc.EventChar = lpDCB->EvtChar;
	sc.XonChar = lpDCB->XonChar;
	sc.XoffChar = lpDCB->XoffChar;


	return (DeviceIoControl(hFile, IOCTL_SERIAL_SET_BAUD_RATE,
		&sbr, sizeof(sbr), NULL, 0, &dwBytesReturned, NULL) &&
		DeviceIoControl(hFile, IOCTL_SERIAL_SET_LINE_CONTROL,
			&slc, sizeof(slc), NULL, 0, &dwBytesReturned, NULL) &&
		DeviceIoControl(hFile, IOCTL_SERIAL_SET_HANDFLOW,
			&shf, sizeof(shf), NULL, 0, &dwBytesReturned, NULL) &&
		DeviceIoControl(hFile, IOCTL_SERIAL_SET_CHARS,
			&sc, sizeof(sc), NULL, 0, &dwBytesReturned, NULL));
}

BOOLEAN ComProt::PurgeComm(HANDLE hFile, DWORD dwFlags)
{
	DWORD dwBytesReturned;
	return DeviceIoControl(hFile, IOCTL_SERIAL_PURGE, &dwFlags, sizeof(dwFlags),
		NULL, 0, &dwBytesReturned, NULL);
}

BOOLEAN ComProt::ClearCommError(HANDLE hFile, LPDWORD lpErrors, LPCOMSTAT lpStat)
{
	SERIAL_STATUS       ss;
	DWORD dwBytesReturned;

	if (!DeviceIoControl(hFile, IOCTL_SERIAL_GET_COMMSTATUS, NULL, 0,
		&ss, sizeof(ss), &dwBytesReturned, NULL))
		return FALSE;

	if (lpErrors)
	{
		*lpErrors = 0;
		if (ss.Errors & SERIAL_ERROR_BREAK)             *lpErrors |= CE_BREAK;
		if (ss.Errors & SERIAL_ERROR_FRAMING)           *lpErrors |= CE_FRAME;
		if (ss.Errors & SERIAL_ERROR_OVERRUN)           *lpErrors |= CE_OVERRUN;
		if (ss.Errors & SERIAL_ERROR_QUEUEOVERRUN)      *lpErrors |= CE_RXOVER;
		if (ss.Errors & SERIAL_ERROR_PARITY)            *lpErrors |= CE_RXPARITY;
	}

	if (lpStat)
	{
		memset(lpStat, 0, sizeof(*lpStat));

		if (ss.HoldReasons & SERIAL_TX_WAITING_FOR_CTS)         lpStat->fCtsHold = TRUE;
		if (ss.HoldReasons & SERIAL_TX_WAITING_FOR_DSR)         lpStat->fDsrHold = TRUE;
		if (ss.HoldReasons & SERIAL_TX_WAITING_FOR_DCD)         lpStat->fRlsdHold = TRUE;
		if (ss.HoldReasons & SERIAL_TX_WAITING_FOR_XON)         lpStat->fXoffHold = TRUE;
		if (ss.HoldReasons & SERIAL_TX_WAITING_XOFF_SENT)       lpStat->fXoffSent = TRUE;
		if (ss.EofReceived)                                     lpStat->fEof = TRUE;
		if (ss.WaitForImmediate)                                lpStat->fTxim = TRUE;
		lpStat->cbInQue = ss.AmountInInQueue;
		lpStat->cbOutQue = ss.AmountInOutQueue;
	}
	return TRUE;
}

BOOLEAN ComProt::SetCommMask(HANDLE handle, DWORD evtmask)
{
	DWORD dwBytesReturned;
	return DeviceIoControl(handle, IOCTL_SERIAL_SET_WAIT_MASK,&evtmask, sizeof(evtmask), NULL, 0, &dwBytesReturned, NULL);
}

BOOLEAN  ComProt:: WaitCommEvent(
	HANDLE hFile,              /* [in] handle of comm port to wait for */
	LPDWORD lpdwEvents,        /* [out] event(s) that were detected */
	LPOVERLAPPED lpOverlapped) /* [in/out] for Asynchronous waiting */
{
	return DeviceIoControl(hFile, IOCTL_SERIAL_WAIT_ON_MASK, NULL, 0,
		lpdwEvents, sizeof(DWORD), NULL, lpOverlapped);
}




VOID ComProt::ComServerWokerThread(PVOID Context)
{

	ComProt *This = NULL;
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	BOOLEAN nRet = FALSE;
	COMMTIMEOUTS TimeOuts;
	DCB dcb;
	COMSTAT cs = { 0 };
	DWORD Error;
	OBJECT_ATTRIBUTES object_attributes;
	

	if (!MmIsAddressValid(Context)) {
		goto $EXIT;
	}
	This = (ComProt *)Context;

	Status = This->OpenComProt(&g_ComPortHandle);
	if (!NT_SUCCESS(Status)) {
		DbgPrintEx(77, 0, "打开串口失败 %X\n", Status);
		goto $EXIT;
	}

	Status = This->SetupComm(g_ComPortHandle, 0x1024, 0x1024);
	if (!NT_SUCCESS(Status)) {
		DbgPrintEx(77, 0, "设置缓冲区失败\n");
		goto $EXIT;
	}

	nRet = This->GetCommState(g_ComPortHandle, &dcb);
	if (!nRet) {
		DbgPrintEx(77, 0, "获取串口配置失败\n");
		goto $EXIT;
	}
	dcb.BaudRate = 9600;
	dcb.StopBits = ONESTOPBIT;
	nRet = This->SetCommState(g_ComPortHandle, &dcb);

	if (!nRet) {
		DbgPrintEx(77, 0, "设置串口配置失败\n");
		goto $EXIT;
	}

	TimeOuts.ReadIntervalTimeout = MAXDWORD32;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0; 
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;

	nRet = This->SetCommTimeouts(g_ComPortHandle, &TimeOuts);
	if (!nRet) {
		DbgPrintEx(77, 0, "设置超时时间失败\n");
		goto $EXIT;
	}

	nRet = This->PurgeComm(g_ComPortHandle, PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT);

	if (!nRet) {
		DbgPrintEx(77, 0, "初始化串口失败\n");
		goto $EXIT;
	}

	while (!g_StopComServer)
	{
		

		This->ClearCommError(g_ComPortHandle, &Error, &cs);
		if (cs.cbInQue > 0) {
			ULONG Len = cs.cbInQue;
			CHAR *Buffer = (CHAR *)ExAllocatePool(NonPagedPool, Len);
			memset(Buffer,0, Len);
			This->RecvComData(g_ComPortHandle,Buffer, cs.cbInQue);
		
			if (cs.cbInQue == 8)
			{	
	
			/*	PSocketRecv Data = (PSocketRecv)Buffer;
				DbgPrintEx(77, 0, "%X %d\n\n", Data->Addr, Data->Size);
				PVOID SendBuffer = ExAllocatePool(NonPagedPool, Data->Size);
				memset(SendBuffer, 0, Data->Size);

				This->m_ReadProcess.ReadProcessMemory(Data->Addr, Data->Size, SendBuffer);
				This->SendComData(g_ComPortHandle, SendBuffer, Data->Size);
		
				ExFreePool(SendBuffer);*/

			}

			if (cs.cbInQue == 4)
			{
		
				int Pid = *(int *)Buffer;
				Status = This->m_ReadProcess.SetProcess((HANDLE)Pid);
				This->SendComData(g_ComPortHandle, &Status, 4);
			
	
			}
		
			if (Buffer != NULL) {
				ExFreePool(Buffer);
				Buffer = NULL;
			}
	
			
		}
		
	
	}

	goto $EXIT;

$EXIT:

	PsTerminateSystemThread(STATUS_SUCCESS);
	return;
}


