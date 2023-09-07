#pragma once
#include "NtHread.h"

#define IOCTL_SERIAL_CLEAR_STATS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 36, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_CLR_DTR \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 10, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_CLR_RTS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 13, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_CONFIG_SIZE \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 32, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_BAUD_RATE \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 20, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_CHARS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 22, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_COMMSTATUS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 27, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_DTRRTS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 30, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_HANDFLOW \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 24, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_LINE_CONTROL \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 21, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_MODEM_CONTROL \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 37, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_MODEMSTATUS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 26, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_PROPERTIES \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 29, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_STATS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 35, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_TIMEOUTS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 8, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_GET_WAIT_MASK \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 16, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_IMMEDIATE_CHAR \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 6, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_LSRMST_INSERT \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 31, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_PURGE \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 19, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_RESET_DEVICE \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 11, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_BAUD_RATE \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_BREAK_ON \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 4, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_BREAK_OFF \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 5, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_CHARS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 23, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_DTR \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 9, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_FIFO_CONTROL \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 39, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_HANDFLOW \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 25, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_LINE_CONTROL \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 3, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_MODEM_CONTROL \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 38, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_QUEUE_SIZE \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_RTS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 12, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_TIMEOUTS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 7, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_WAIT_MASK \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 17, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_XOFF \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 14, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_SET_XON \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 15, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_WAIT_ON_MASK \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 18, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_XOFF_COUNTER \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 28, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_SERIAL_INTERNAL_BASIC_SETTINGS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 3, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_INTERNAL_CANCEL_WAIT_WAKE \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_INTERNAL_DO_WAIT_WAKE \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERIAL_INTERNAL_RESTORE_SETTINGS \
  CTL_CODE (FILE_DEVICE_SERIAL_PORT, 4, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_SERENUM_PORT_DESC \
  CTL_CODE (FILE_DEVICE_SERENUM, 130, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SERENUM_GET_PORT_NAME \
  CTL_CODE (FILE_DEVICE_SERENUM, 131, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_SERENUM_REMOVE_SELF \
  CTL_CODE (FILE_DEVICE_SERENUM, 129, METHOD_NEITHER, FILE_ANY_ACCESS)

#define SERIAL_DTR_CONTROL	0x01
#define SERIAL_CTS_HANDSHAKE	0x08
#define SERIAL_ERROR_ABORT	0x80000000
#define SERIAL_DTR_MASK                   0x00000003
#define SERIAL_DTR_HANDSHAKE              0x00000002
#define SERIAL_DSR_HANDSHAKE              0x00000010
#define SERIAL_DCD_HANDSHAKE              0x00000020
#define SERIAL_OUT_HANDSHAKEMASK          0x00000038
#define SERIAL_DSR_SENSITIVITY            0x00000040
#define SERIAL_ERROR_ABORT                0x80000000
#define SERIAL_CONTROL_INVALID            0x7fffff84
#define SERIAL_AUTO_TRANSMIT              0x00000001
#define SERIAL_AUTO_RECEIVE               0x00000002
#define SERIAL_ERROR_CHAR                 0x00000004
#define SERIAL_NULL_STRIPPING             0x00000008
#define SERIAL_BREAK_CHAR                 0x00000010
#define SERIAL_RTS_MASK                   0x000000c0
#define SERIAL_RTS_CONTROL                0x00000040
#define SERIAL_RTS_HANDSHAKE              0x00000080
#define SERIAL_TRANSMIT_TOGGLE            0x000000c0
#define SERIAL_XOFF_CONTINUE              0x80000000
#define SERIAL_FLOW_INVALID               0x7fffff20

#define DTR_CONTROL_DISABLE    0x00
#define DTR_CONTROL_ENABLE     0x01
#define DTR_CONTROL_HANDSHAKE  0x02

//
// RTS Control Flow Values
//
#define RTS_CONTROL_DISABLE    0x00
#define RTS_CONTROL_ENABLE     0x01
#define RTS_CONTROL_HANDSHAKE  0x02
#define RTS_CONTROL_TOGGLE     0x03


#define FILE_TYPE_UNKNOWN   0x0000
#define FILE_TYPE_DISK      0x0001
#define FILE_TYPE_CHAR      0x0002
#define FILE_TYPE_PIPE      0x0003
#define FILE_TYPE_REMOTE    0x8000


#define STD_INPUT_HANDLE    ((DWORD)-10)
#define STD_OUTPUT_HANDLE   ((DWORD)-11)
#define STD_ERROR_HANDLE    ((DWORD)-12)

#define NOPARITY            0
#define ODDPARITY           1
#define EVENPARITY          2
#define MARKPARITY          3
#define SPACEPARITY         4

#define ONESTOPBIT          0
#define ONE5STOPBITS        1
#define TWOSTOPBITS         2

#define IGNORE              0       // Ignore signal
#define INFINITE            0xFFFFFFFF  // Infinite timeout


//
// PURGE function flags.
//
#define PURGE_TXABORT       0x0001  // Kill the pending/current writes to the comm port.
#define PURGE_RXABORT       0x0002  // Kill the pending/current reads to the comm port.
#define PURGE_TXCLEAR       0x0004  // Kill the transmit queue if there.
#define PURGE_RXCLEAR       0x0008  // Kill the typeahead buffer if there.
#define COMMPROP_INITIALIZED ((DWORD)0xE73CF52E)


#define SERIAL_ERROR_BREAK                0x00000001
#define SERIAL_ERROR_FRAMING              0x00000002
#define SERIAL_ERROR_OVERRUN              0x00000004
#define SERIAL_ERROR_QUEUEOVERRUN         0x00000008
#define SERIAL_ERROR_PARITY               0x00000010

#define SERIAL_SP_UNSPECIFIED             0x00000000
#define SERIAL_SP_RS232                   0x00000001
#define SERIAL_SP_PARALLEL                0x00000002
#define SERIAL_SP_RS422                   0x00000003
#define SERIAL_SP_RS423                   0x00000004
#define SERIAL_SP_RS449                   0x00000005
#define SERIAL_SP_MODEM                   0X00000006
#define SERIAL_SP_FAX                     0x00000021
#define SERIAL_SP_SCANNER                 0x00000022
#define SERIAL_SP_BRIDGE                  0x00000100
#define SERIAL_SP_LAT                     0x00000101
#define SERIAL_SP_TELNET                  0x00000102
#define SERIAL_SP_X25                     0x00000103
#define SERIAL_SP_SERIALCOMM              0x00000001

#define SERIAL_TX_WAITING_FOR_CTS         0x00000001
#define SERIAL_TX_WAITING_FOR_DSR         0x00000002
#define SERIAL_TX_WAITING_FOR_DCD         0x00000004
#define SERIAL_TX_WAITING_FOR_XON         0x00000008
#define SERIAL_TX_WAITING_XOFF_SENT       0x00000010
#define SERIAL_TX_WAITING_ON_BREAK        0x00000020
#define SERIAL_RX_WAITING_FOR_DSR         0x00000040

#define SERIAL_DTR_STATE                  0x00000001
#define SERIAL_RTS_STATE                  0x00000002
#define SERIAL_CTS_STATE                  0x00000010
#define SERIAL_DSR_STATE                  0x00000020
#define SERIAL_RI_STATE                   0x00000040
#define SERIAL_DCD_STATE                  0x00000080

#define CE_RXOVER           0x0001  // Receive Queue overflow
#define CE_OVERRUN          0x0002  // Receive Overrun Error
#define CE_RXPARITY         0x0004  // Receive Parity Error
#define CE_FRAME            0x0008  // Receive Framing error
#define CE_BREAK            0x0010  // Break Detected
#define CE_TXFULL           0x0100  // TX Queue is full
#define CE_PTO              0x0200  // LPTx Timeout
#define CE_IOE              0x0400  // LPTx I/O Error
#define CE_DNS              0x0800  // LPTx Device not selected
#define CE_OOP              0x1000  // LPTx Out-Of-Paper
#define CE_MODE             0x8000  // Requested mode unsupported

#define IE_BADID            (-1)    // Invalid or unsupported id
#define IE_OPEN             (-2)    // Device Already Open
#define IE_NOPEN            (-3)    // Device Not Open
#define IE_MEMORY           (-4)    // Unable to allocate queues
#define IE_DEFAULT          (-5)    // Error in default parameters
#define IE_HARDWARE         (-10)   // Hardware Not Present
#define IE_BYTESIZE         (-11)   // Illegal Byte Size
#define IE_BAUDRATE         (-12)   // Unsupported BaudRate

#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

#define INVALID_FILE_SIZE ((DWORD)0xFFFFFFFF)
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#define EV_RXCHAR           0x0001  // Any Character received
#define EV_RXFLAG           0x0002  // Received certain character
#define EV_TXEMPTY          0x0004  // Transmitt Queue Empty
#define EV_CTS              0x0008  // CTS changed state
#define EV_DSR              0x0010  // DSR changed state
#define EV_RLSD             0x0020  // RLSD changed state
#define EV_BREAK            0x0040  // BREAK received
#define EV_ERR              0x0080  // Line status error occurred
#define EV_RING             0x0100  // Ring signal detected
#define EV_PERR             0x0200  // Printer error occured
#define EV_RX80FULL         0x0400  // Receive buffer is 80 percent full
#define EV_EVENT1           0x0800  // Provider specific event 1
#define EV_EVENT2           0x1000  // Provider specific event 2



typedef struct _COMSTAT {
	DWORD fCtsHold : 1;
	DWORD fDsrHold : 1;
	DWORD fRlsdHold : 1;
	DWORD fXoffHold : 1;
	DWORD fXoffSent : 1;
	DWORD fEof : 1;
	DWORD fTxim : 1;
	DWORD fReserved : 25;
	DWORD cbInQue;
	DWORD cbOutQue;
} COMSTAT, *LPCOMSTAT;

typedef struct _SERIAL_QUEUE_SIZE {
	ULONG  InSize;
	ULONG  OutSize;
} SERIAL_QUEUE_SIZE, *PSERIAL_QUEUE_SIZE;

typedef struct _COMMTIMEOUTS {
	DWORD ReadIntervalTimeout;          /* Maximum time between read chars. */
	DWORD ReadTotalTimeoutMultiplier;   /* Multiplier of characters.        */
	DWORD ReadTotalTimeoutConstant;     /* Constant in milliseconds.        */
	DWORD WriteTotalTimeoutMultiplier;  /* Multiplier of characters.        */
	DWORD WriteTotalTimeoutConstant;    /* Constant in milliseconds.        */
} COMMTIMEOUTS, *LPCOMMTIMEOUTS;

typedef struct _SERIAL_TIMEOUTS {
	ULONG  ReadIntervalTimeout;
	ULONG  ReadTotalTimeoutMultiplier;
	ULONG  ReadTotalTimeoutConstant;
	ULONG  WriteTotalTimeoutMultiplier;
	ULONG  WriteTotalTimeoutConstant;
} SERIAL_TIMEOUTS, *PSERIAL_TIMEOUTS;

typedef struct _DCB {
	DWORD DCBlength;      /* sizeof(DCB)                     */
	DWORD BaudRate;       /* Baudrate at which running       */
	DWORD fBinary : 1;     /* Binary Mode (skip EOF check)    */
	DWORD fParity : 1;     /* Enable parity checking          */
	DWORD fOutxCtsFlow : 1; /* CTS handshaking on output       */
	DWORD fOutxDsrFlow : 1; /* DSR handshaking on output       */
	DWORD fDtrControl : 2;  /* DTR Flow control                */
	DWORD fDsrSensitivity : 1; /* DSR Sensitivity              */
	DWORD fTXContinueOnXoff : 1; /* Continue TX when Xoff sent */
	DWORD fOutX : 1;       /* Enable output X-ON/X-OFF        */
	DWORD fInX : 1;        /* Enable input X-ON/X-OFF         */
	DWORD fErrorChar : 1;  /* Enable Err Replacement          */
	DWORD fNull : 1;       /* Enable Null stripping           */
	DWORD fRtsControl : 2;  /* Rts Flow control                */
	DWORD fAbortOnError : 1; /* Abort all reads and writes on Error */
	DWORD fDummy2 : 17;     /* Reserved                        */
	WORD wReserved;       /* Not currently used              */
	WORD XonLim;          /* Transmit X-ON threshold         */
	WORD XoffLim;         /* Transmit X-OFF threshold        */
	BYTE ByteSize;        /* Number of bits/byte, 4-8        */
	BYTE Parity;          /* 0-4=None,Odd,Even,Mark,Space    */
	BYTE StopBits;        /* 0,1,2 = 1, 1.5, 2               */
	char XonChar;         /* Tx and Rx X-ON character        */
	char XoffChar;        /* Tx and Rx X-OFF character       */
	char ErrorChar;       /* Error replacement char          */
	char EofChar;         /* End of Input character          */
	char EvtChar;         /* Received Event character        */
	WORD wReserved1;      /* Fill for now.                   */
} DCB, *LPDCB;

typedef struct _SERIAL_BAUD_RATE {
	ULONG  BaudRate;
} SERIAL_BAUD_RATE, *PSERIAL_BAUD_RATE;

typedef struct _SERIAL_LINE_CONTROL {
	UCHAR  StopBits;
	UCHAR  Parity;
	UCHAR  WordLength;
} SERIAL_LINE_CONTROL, *PSERIAL_LINE_CONTROL;

typedef struct _SERIAL_HANDFLOW {
	ULONG  ControlHandShake;
	ULONG  FlowReplace;
	LONG  XonLimit;
	LONG  XoffLimit;
} SERIAL_HANDFLOW, *PSERIAL_HANDFLOW;

typedef struct _SERIAL_CHARS {
	UCHAR  EofChar;
	UCHAR  ErrorChar;
	UCHAR  BreakChar;
	UCHAR  EventChar;
	UCHAR  XonChar;
	UCHAR  XoffChar;
} SERIAL_CHARS, *PSERIAL_CHARS;

typedef struct _SERIAL_STATUS {
	ULONG  Errors;
	ULONG  HoldReasons;
	ULONG  AmountInInQueue;
	ULONG  AmountInOutQueue;
	BOOLEAN  EofReceived;
	BOOLEAN  WaitForImmediate;
} SERIAL_STATUS, *PSERIAL_STATUS;

typedef struct _SECURITY_ATTRIBUTES {
	DWORD nLength;
	PVOID lpSecurityDescriptor;
	BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;