#pragma once
#include "NtHread.h"


typedef struct _KAFFINITY_EX
{
	/* 0x0000 */ unsigned short Count;
	/* 0x0002 */ unsigned short Size;
	/* 0x0004 */ unsigned long Reserved;
	/* 0x0008 */ unsigned __int64 Bitmap[4];
} KAFFINITY_EX, *PKAFFINITY_EX; /* size: 0x0028 */


typedef union _KEXECUTE_OPTIONS
{
	union
	{
		struct /* bitfield */
		{
			/* 0x0000 */ unsigned char ExecuteDisable : 1; /* bit position: 0 */
			/* 0x0000 */ unsigned char ExecuteEnable : 1; /* bit position: 1 */
			/* 0x0000 */ unsigned char DisableThunkEmulation : 1; /* bit position: 2 */
			/* 0x0000 */ unsigned char Permanent : 1; /* bit position: 3 */
			/* 0x0000 */ unsigned char ExecuteDispatchEnable : 1; /* bit position: 4 */
			/* 0x0000 */ unsigned char ImageDispatchEnable : 1; /* bit position: 5 */
			/* 0x0000 */ unsigned char DisableExceptionChainValidation : 1; /* bit position: 6 */
			/* 0x0000 */ unsigned char Spare : 1; /* bit position: 7 */
		}; /* bitfield */
		/* 0x0000 */ volatile unsigned char ExecuteOptions;
	}; /* size: 0x0001 */
} KEXECUTE_OPTIONS, *PKEXECUTE_OPTIONS; /* size: 0x0001 */

typedef union _KSTACK_COUNT
{
	union
	{
		/* 0x0000 */ volatile long Value;
		struct /* bitfield */
		{
			/* 0x0000 */ volatile unsigned long State : 3; /* bit position: 0 */
			/* 0x0000 */ unsigned long StackCount : 29; /* bit position: 3 */
		}; /* bitfield */
	}; /* size: 0x0004 */
} KSTACK_COUNT, *PKSTACK_COUNT; /* size: 0x0004 */

typedef union _KGDTENTRY64
{
	union
	{
		struct
		{
			/* 0x0000 */ unsigned short LimitLow;
			/* 0x0002 */ unsigned short BaseLow;
			union
			{
				struct // _TAG_UNNAMED_32
				{
					/* 0x0004 */ unsigned char BaseMiddle;
					/* 0x0005 */ unsigned char Flags1;
					/* 0x0006 */ unsigned char Flags2;
					/* 0x0007 */ unsigned char BaseHigh;
				} /* size: 0x0004 */ Bytes;
				struct
				{
					struct // _TAG_UNNAMED_33
					{
						struct /* bitfield */
						{
							/* 0x0004 */ unsigned long BaseMiddle : 8; /* bit position: 0 */
							/* 0x0004 */ unsigned long Type : 5; /* bit position: 8 */
							/* 0x0004 */ unsigned long Dpl : 2; /* bit position: 13 */
							/* 0x0004 */ unsigned long Present : 1; /* bit position: 15 */
							/* 0x0004 */ unsigned long LimitHigh : 4; /* bit position: 16 */
							/* 0x0004 */ unsigned long System : 1; /* bit position: 20 */
							/* 0x0004 */ unsigned long LongMode : 1; /* bit position: 21 */
							/* 0x0004 */ unsigned long DefaultBig : 1; /* bit position: 22 */
							/* 0x0004 */ unsigned long Granularity : 1; /* bit position: 23 */
							/* 0x0004 */ unsigned long BaseHigh : 8; /* bit position: 24 */
						}; /* bitfield */
					} /* size: 0x0004 */ Bits;
					/* 0x0008 */ unsigned long BaseUpper;
					/* 0x000c */ unsigned long MustBeZero;
				}; /* size: 0x000c */
			}; /* size: 0x000c */
		}; /* size: 0x0010 */
		/* 0x0000 */ unsigned __int64 Alignment;
	}; /* size: 0x0010 */
} KGDTENTRY64, *PKGDTENTRY64; /* size: 0x0010 */



typedef struct _KGUARDED_MUTEX
{
	/* 0x0000 */ volatile long Count;
	/* 0x0008 */ struct _KTHREAD* Owner;
	/* 0x0010 */ unsigned long Contention;
	/* 0x0018 */ struct _KGATE Gate;
	union
	{
		struct
		{
			/* 0x0030 */ short KernelApcDisable;
			/* 0x0032 */ short SpecialApcDisable;
		}; /* size: 0x0004 */
		/* 0x0030 */ unsigned long CombinedApcDisable;
	}; /* size: 0x0004 */
	/* 0x0034 */ long __PADDING__[1];
} KGUARDED_MUTEX1, *PKGUARDED_MUTEX1; /* size: 0x0038 */

typedef struct _KPROCESS
{
	/* 0x0000 */ struct _DISPATCHER_HEADER Header;
	/* 0x0018 */ struct _LIST_ENTRY ProfileListHead;
	/* 0x0028 */ unsigned __int64 DirectoryTableBase;
	/* 0x0030 */ struct _LIST_ENTRY ThreadListHead;
	/* 0x0040 */ unsigned __int64 ProcessLock;
	/* 0x0048 */ struct _KAFFINITY_EX Affinity;
	/* 0x0070 */ struct _LIST_ENTRY ReadyListHead;
	/* 0x0080 */ struct _SINGLE_LIST_ENTRY SwapListEntry;
	/* 0x0088 */ volatile struct _KAFFINITY_EX ActiveProcessors;
	union
	{
		struct /* bitfield */
		{
			/* 0x00b0 */ volatile long AutoAlignment : 1; /* bit position: 0 */
			/* 0x00b0 */ volatile long DisableBoost : 1; /* bit position: 1 */
			/* 0x00b0 */ volatile long DisableQuantum : 1; /* bit position: 2 */
			/* 0x00b0 */ volatile unsigned long ActiveGroupsMask : 4; /* bit position: 3 */
			/* 0x00b0 */ volatile long ReservedFlags : 25; /* bit position: 7 */
		}; /* bitfield */
		/* 0x00b0 */ volatile long ProcessFlags;
	}; /* size: 0x0004 */
	/* 0x00b4 */ char BasePriority;
	/* 0x00b5 */ char QuantumReset;
	/* 0x00b6 */ unsigned char Visited;
	/* 0x00b7 */ unsigned char Unused3;
	/* 0x00b8 */ unsigned long ThreadSeed[4];
	/* 0x00c8 */ unsigned short IdealNode[4];
	/* 0x00d0 */ unsigned short IdealGlobalNode;
	/* 0x00d2 */ union _KEXECUTE_OPTIONS Flags;
	/* 0x00d3 */ unsigned char Unused1;
	/* 0x00d4 */ unsigned long Unused2;
	/* 0x00d8 */ unsigned long Unused4;
	/* 0x00dc */ union _KSTACK_COUNT StackCount;
	/* 0x00e0 */ struct _LIST_ENTRY ProcessListEntry;
	/* 0x00f0 */ volatile unsigned __int64 CycleTime;
	/* 0x00f8 */ unsigned long KernelTime;
	/* 0x00fc */ unsigned long UserTime;
	/* 0x0100 */ void* InstrumentationCallback;
	/* 0x0108 */ union _KGDTENTRY64 LdtSystemDescriptor;
	/* 0x0118 */ void* LdtBaseAddress;
	/* 0x0120 */ struct _KGUARDED_MUTEX LdtProcessLock;
	/* 0x0158 */ unsigned short LdtFreeSelectorHint;
	/* 0x015a */ unsigned short LdtTableLength;
	/* 0x015c */ long __PADDING__[1];
} KPROCESS, *PKPROCESS; /* size: 0x0160 */

typedef struct _EX_PUSH_LOCK
{
	union
	{
		struct /* bitfield */
		{
			/* 0x0000 */ unsigned __int64 Locked : 1; /* bit position: 0 */
			/* 0x0000 */ unsigned __int64 Waiting : 1; /* bit position: 1 */
			/* 0x0000 */ unsigned __int64 Waking : 1; /* bit position: 2 */
			/* 0x0000 */ unsigned __int64 MultipleShared : 1; /* bit position: 3 */
			/* 0x0000 */ unsigned __int64 Shared : 60; /* bit position: 4 */
		}; /* bitfield */
		/* 0x0000 */ unsigned __int64 Value;
		/* 0x0000 */ void* Ptr;
	}; /* size: 0x0008 */
} EX_PUSH_LOCK1, *PEX_PUSH_LOCK1; /* size: 0x0008 */





typedef struct _EX_FAST_REF
{
	union
	{
		/* 0x0000 */ void* Object;
		/* 0x0000 */ unsigned __int64 RefCnt : 4; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 Value;
	}; /* size: 0x0008 */
} EX_FAST_REF, *PEX_FAST_REF; /* size: 0x0008 */

typedef struct _HARDWARE_PTE
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 Write : 1; /* bit position: 1 */
		/* 0x0000 */ unsigned __int64 Owner : 1; /* bit position: 2 */
		/* 0x0000 */ unsigned __int64 WriteThrough : 1; /* bit position: 3 */
		/* 0x0000 */ unsigned __int64 CacheDisable : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned __int64 Accessed : 1; /* bit position: 5 */
		/* 0x0000 */ unsigned __int64 Dirty : 1; /* bit position: 6 */
		/* 0x0000 */ unsigned __int64 LargePage : 1; /* bit position: 7 */
		/* 0x0000 */ unsigned __int64 Global : 1; /* bit position: 8 */
		/* 0x0000 */ unsigned __int64 CopyOnWrite : 1; /* bit position: 9 */
		/* 0x0000 */ unsigned __int64 Prototype : 1; /* bit position: 10 */
		/* 0x0000 */ unsigned __int64 reserved0 : 1; /* bit position: 11 */
		/* 0x0000 */ unsigned __int64 PageFrameNumber : 28; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 reserved1 : 12; /* bit position: 40 */
		/* 0x0000 */ unsigned __int64 SoftwareWsIndex : 11; /* bit position: 52 */
		/* 0x0000 */ unsigned __int64 NoExecute : 1; /* bit position: 63 */
	}; /* bitfield */
} HARDWARE_PTE, *PHARDWARE_PTE; /* size: 0x0008 */

typedef struct _SE_AUDIT_PROCESS_CREATION_INFO
{
	/* 0x0000 */ struct _OBJECT_NAME_INFORMATION* ImageFileName;
} SE_AUDIT_PROCESS_CREATION_INFO, *PSE_AUDIT_PROCESS_CREATION_INFO; /* size: 0x0008 */

typedef struct _MMSUPPORT_FLAGS
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned char WorkingSetType : 3; /* bit position: 0 */
		/* 0x0000 */ unsigned char ModwriterAttached : 1; /* bit position: 3 */
		/* 0x0000 */ unsigned char TrimHard : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned char MaximumWorkingSetHard : 1; /* bit position: 5 */
		/* 0x0000 */ unsigned char ForceTrim : 1; /* bit position: 6 */
		/* 0x0000 */ unsigned char MinimumWorkingSetHard : 1; /* bit position: 7 */
	}; /* bitfield */
	struct /* bitfield */
	{
		/* 0x0001 */ unsigned char SessionMaster : 1; /* bit position: 0 */
		/* 0x0001 */ unsigned char TrimmerState : 2; /* bit position: 1 */
		/* 0x0001 */ unsigned char Reserved : 1; /* bit position: 3 */
		/* 0x0001 */ unsigned char PageStealers : 4; /* bit position: 4 */
	}; /* bitfield */
	/* 0x0002 */ unsigned char MemoryPriority : 8; /* bit position: 0 */
	struct /* bitfield */
	{
		/* 0x0003 */ unsigned char WsleDeleted : 1; /* bit position: 0 */
		/* 0x0003 */ unsigned char VmExiting : 1; /* bit position: 1 */
		/* 0x0003 */ unsigned char ExpansionFailed : 1; /* bit position: 2 */
		/* 0x0003 */ unsigned char Available : 5; /* bit position: 3 */
	}; /* bitfield */
} MMSUPPORT_FLAGS, *PMMSUPPORT_FLAGS; /* size: 0x0004 */

typedef struct _MMSUPPORT
{
	/* 0x0000 */ struct _EX_PUSH_LOCK WorkingSetMutex;
	/* 0x0008 */ struct _KGATE* ExitGate;
	/* 0x0010 */ void* AccessLog;
	/* 0x0018 */ struct _LIST_ENTRY WorkingSetExpansionLinks;
	/* 0x0028 */ unsigned long AgeDistribution[7];
	/* 0x0044 */ unsigned long MinimumWorkingSetSize;
	/* 0x0048 */ unsigned long WorkingSetSize;
	/* 0x004c */ unsigned long WorkingSetPrivateSize;
	/* 0x0050 */ unsigned long MaximumWorkingSetSize;
	/* 0x0054 */ unsigned long ChargedWslePages;
	/* 0x0058 */ unsigned long ActualWslePages;
	/* 0x005c */ unsigned long WorkingSetSizeOverhead;
	/* 0x0060 */ unsigned long PeakWorkingSetSize;
	/* 0x0064 */ unsigned long HardFaultCount;
	/* 0x0068 */ struct _MMWSL* VmWorkingSetList;
	/* 0x0070 */ unsigned short NextPageColor;
	/* 0x0072 */ unsigned short LastTrimStamp;
	/* 0x0074 */ unsigned long PageFaultCount;
	/* 0x0078 */ unsigned long RepurposeCount;
	/* 0x007c */ unsigned long Spare[2];
	/* 0x0084 */ struct _MMSUPPORT_FLAGS Flags;
} MMSUPPORT, *PMMSUPPORT; /* size: 0x0088 */

typedef struct _MMADDRESS_NODE
{
	union // _TAG_UNNAMED_65
	{
		union
		{
			/* 0x0000 */ __int64 Balance : 2; /* bit position: 0 */
			/* 0x0000 */ struct _MMADDRESS_NODE* Parent;
		}; /* size: 0x0008 */
	} /* size: 0x0008 */ u1;
	/* 0x0008 */ struct _MMADDRESS_NODE* LeftChild;
	/* 0x0010 */ struct _MMADDRESS_NODE* RightChild;
	/* 0x0018 */ unsigned __int64 StartingVpn;
	/* 0x0020 */ unsigned __int64 EndingVpn;
} MMADDRESS_NODE, *PMMADDRESS_NODE; /* size: 0x0028 */

typedef struct _MM_AVL_TABLE
{
	/* 0x0000 */ struct _MMADDRESS_NODE BalancedRoot;
	struct /* bitfield */
	{
		/* 0x0028 */ unsigned __int64 DepthOfTree : 5; /* bit position: 0 */
		/* 0x0028 */ unsigned __int64 Unused : 3; /* bit position: 5 */
		/* 0x0028 */ unsigned __int64 NumberGenericTableElements : 56; /* bit position: 8 */
	}; /* bitfield */
	/* 0x0030 */ void* NodeHint;
	/* 0x0038 */ void* NodeFreeHint;
} MM_AVL_TABLE, *PMM_AVL_TABLE; /* size: 0x0040 */

typedef struct _ALPC_PROCESS_CONTEXT
{
	/* 0x0000 */ struct _EX_PUSH_LOCK Lock;
	/* 0x0008 */ struct _LIST_ENTRY ViewListHead;
	/* 0x0018 */ volatile unsigned __int64 PagedPoolQuotaCache;
} ALPC_PROCESS_CONTEXT, *PALPC_PROCESS_CONTEXT; /* size: 0x0020 */

typedef struct _EPROCESS
{
	/* 0x0000 */ struct _KPROCESS Pcb;
	/* 0x0160 */ struct _EX_PUSH_LOCK ProcessLock;
	/* 0x0168 */ union _LARGE_INTEGER CreateTime;
	/* 0x0170 */ union _LARGE_INTEGER ExitTime;
	/* 0x0178 */ struct _EX_RUNDOWN_REF RundownProtect;
	/* 0x0180 */ void* UniqueProcessId;
	/* 0x0188 */ struct _LIST_ENTRY ActiveProcessLinks;
	/* 0x0198 */ unsigned __int64 ProcessQuotaUsage[2];
	/* 0x01a8 */ unsigned __int64 ProcessQuotaPeak[2];
	/* 0x01b8 */ volatile unsigned __int64 CommitCharge;
	/* 0x01c0 */ struct _EPROCESS_QUOTA_BLOCK* QuotaBlock;
	/* 0x01c8 */ struct _PS_CPU_QUOTA_BLOCK* CpuQuotaBlock;
	/* 0x01d0 */ unsigned __int64 PeakVirtualSize;
	/* 0x01d8 */ unsigned __int64 VirtualSize;
	/* 0x01e0 */ struct _LIST_ENTRY SessionProcessLinks;
	/* 0x01f0 */ void* DebugPort;
	union
	{
		/* 0x01f8 */ void* ExceptionPortData;
		/* 0x01f8 */ unsigned __int64 ExceptionPortValue;
		/* 0x01f8 */ unsigned __int64 ExceptionPortState : 3; /* bit position: 0 */
	}; /* size: 0x0008 */
	/* 0x0200 */ struct _HANDLE_TABLE* ObjectTable;
	/* 0x0208 */ struct _EX_FAST_REF Token;
	/* 0x0210 */ unsigned __int64 WorkingSetPage;
	/* 0x0218 */ struct _EX_PUSH_LOCK AddressCreationLock;
	/* 0x0220 */ struct _ETHREAD* RotateInProgress;
	/* 0x0228 */ struct _ETHREAD* ForkInProgress;
	/* 0x0230 */ unsigned __int64 HardwareTrigger;
	/* 0x0238 */ struct _MM_AVL_TABLE* PhysicalVadRoot;
	/* 0x0240 */ void* CloneRoot;
	/* 0x0248 */ volatile unsigned __int64 NumberOfPrivatePages;
	/* 0x0250 */ volatile unsigned __int64 NumberOfLockedPages;
	/* 0x0258 */ void* Win32Process;
	/* 0x0260 */ struct _EJOB* volatile Job;
	/* 0x0268 */ void* SectionObject;
	/* 0x0270 */ void* SectionBaseAddress;
	/* 0x0278 */ unsigned long Cookie;
	/* 0x027c */ unsigned long UmsScheduledThreads;
	/* 0x0280 */ struct _PAGEFAULT_HISTORY* WorkingSetWatch;
	/* 0x0288 */ void* Win32WindowStation;
	/* 0x0290 */ void* InheritedFromUniqueProcessId;
	/* 0x0298 */ void* LdtInformation;
	/* 0x02a0 */ void* Spare;
	/* 0x02a8 */ unsigned __int64 ConsoleHostProcess;
	/* 0x02b0 */ void* DeviceMap;
	/* 0x02b8 */ void* EtwDataSource;
	/* 0x02c0 */ void* FreeTebHint;
	/* 0x02c8 ThreadListHead:63D4CF8 63D4A20
 */ void* FreeUmsTebHint;
	union
	{
		/* 0x02d0 */ struct _HARDWARE_PTE PageDirectoryPte;
		/* 0x02d0 */ unsigned __int64 Filler;
	}; /* size: 0x0008 */
	/* 0x02d8 */ void* Session;
	/* 0x02e0 */ unsigned char ImageFileName[15];
	/* 0x02ef */ unsigned char PriorityClass;
	/* 0x02f0 */ struct _LIST_ENTRY JobLinks;
	/* 0x0300 */ void* LockedPagesList;
	/* 0x0308 */ struct _LIST_ENTRY ThreadListHead;
	/* 0x0318 */ void* SecurityPort;
	/* 0x0320 */ void* Wow64Process;
	/* 0x0328 */ volatile unsigned long ActiveThreads;
	/* 0x032c */ unsigned long ImagePathHash;
	/* 0x0330 */ unsigned long DefaultHardErrorProcessing;
	/* 0x0334 */ long LastThreadExitStatus;
	/* 0x0338 */ struct _PEB* Peb;
	/* 0x0340 */ struct _EX_FAST_REF PrefetchTrace;
	/* 0x0348 */ union _LARGE_INTEGER ReadOperationCount;
	/* 0x0350 */ union _LARGE_INTEGER WriteOperationCount;
	/* 0x0358 */ union _LARGE_INTEGER OtherOperationCount;
	/* 0x0360 */ union _LARGE_INTEGER ReadTransferCount;
	/* 0x0368 */ union _LARGE_INTEGER WriteTransferCount;
	/* 0x0370 */ union _LARGE_INTEGER OtherTransferCount;
	/* 0x0378 */ unsigned __int64 CommitChargeLimit;
	/* 0x0380 */ volatile unsigned __int64 CommitChargePeak;
	/* 0x0388 */ void* AweInfo;
	/* 0x0390 */ struct _SE_AUDIT_PROCESS_CREATION_INFO SeAuditProcessCreationInfo;
	/* 0x0398 */ struct _MMSUPPORT Vm;
	/* 0x0420 */ struct _LIST_ENTRY MmProcessLinks;
	/* 0x0430 */ void* HighestUserAddress;
	/* 0x0438 */ unsigned long ModifiedPageCount;
	union
	{
		/* 0x043c */ unsigned long Flags2;
		struct /* bitfield */
		{
			/* 0x043c */ unsigned long JobNotReallyActive : 1; /* bit position: 0 */
			/* 0x043c */ unsigned long AccountingFolded : 1; /* bit position: 1 */
			/* 0x043c */ unsigned long NewProcessReported : 1; /* bit position: 2 */
			/* 0x043c */ unsigned long ExitProcessReported : 1; /* bit position: 3 */
			/* 0x043c */ unsigned long ReportCommitChanges : 1; /* bit position: 4 */
			/* 0x043c */ unsigned long LastReportMemory : 1; /* bit position: 5 */
			/* 0x043c */ unsigned long ReportPhysicalPageChanges : 1; /* bit position: 6 */
			/* 0x043c */ unsigned long HandleTableRundown : 1; /* bit position: 7 */
			/* 0x043c */ unsigned long NeedsHandleRundown : 1; /* bit position: 8 */
			/* 0x043c */ unsigned long RefTraceEnabled : 1; /* bit position: 9 */
			/* 0x043c */ unsigned long NumaAware : 1; /* bit position: 10 */
			/* 0x043c */ unsigned long ProtectedProcess : 1; /* bit position: 11 */
			/* 0x043c */ unsigned long DefaultPagePriority : 3; /* bit position: 12 */
			/* 0x043c */ unsigned long PrimaryTokenFrozen : 1; /* bit position: 15 */
			/* 0x043c */ unsigned long ProcessVerifierTarget : 1; /* bit position: 16 */
			/* 0x043c */ unsigned long StackRandomizationDisabled : 1; /* bit position: 17 */
			/* 0x043c */ unsigned long AffinityPermanent : 1; /* bit position: 18 */
			/* 0x043c */ unsigned long AffinityUpdateEnable : 1; /* bit position: 19 */
			/* 0x043c */ unsigned long PropagateNode : 1; /* bit position: 20 */
			/* 0x043c */ unsigned long ExplicitAffinity : 1; /* bit position: 21 */
		}; /* bitfield */
	}; /* size: 0x0004 */
	union
	{
		/* 0x0440 */ unsigned long Flags;
		struct /* bitfield */
		{
			/* 0x0440 */ unsigned long CreateReported : 1; /* bit position: 0 */
			/* 0x0440 */ unsigned long NoDebugInherit : 1; /* bit position: 1 */
			/* 0x0440 */ unsigned long ProcessExiting : 1; /* bit position: 2 */
			/* 0x0440 */ unsigned long ProcessDelete : 1; /* bit position: 3 */
			/* 0x0440 */ unsigned long Wow64SplitPages : 1; /* bit position: 4 */
			/* 0x0440 */ unsigned long VmDeleted : 1; /* bit position: 5 */
			/* 0x0440 */ unsigned long OutswapEnabled : 1; /* bit position: 6 */
			/* 0x0440 */ unsigned long Outswapped : 1; /* bit position: 7 */
			/* 0x0440 */ unsigned long ForkFailed : 1; /* bit position: 8 */
			/* 0x0440 */ unsigned long Wow64VaSpace4Gb : 1; /* bit position: 9 */
			/* 0x0440 */ unsigned long AddressSpaceInitialized : 2; /* bit position: 10 */
			/* 0x0440 */ unsigned long SetTimerResolution : 1; /* bit position: 12 */
			/* 0x0440 */ unsigned long BreakOnTermination : 1; /* bit position: 13 */
			/* 0x0440 */ unsigned long DeprioritizeViews : 1; /* bit position: 14 */
			/* 0x0440 */ unsigned long WriteWatch : 1; /* bit position: 15 */
			/* 0x0440 */ unsigned long ProcessInSession : 1; /* bit position: 16 */
			/* 0x0440 */ unsigned long OverrideAddressSpace : 1; /* bit position: 17 */
			/* 0x0440 */ unsigned long HasAddressSpace : 1; /* bit position: 18 */
			/* 0x0440 */ unsigned long LaunchPrefetched : 1; /* bit position: 19 */
			/* 0x0440 */ unsigned long InjectInpageErrors : 1; /* bit position: 20 */
			/* 0x0440 */ unsigned long VmTopDown : 1; /* bit position: 21 */
			/* 0x0440 */ unsigned long ImageNotifyDone : 1; /* bit position: 22 */
			/* 0x0440 */ unsigned long PdeUpdateNeeded : 1; /* bit position: 23 */
			/* 0x0440 */ unsigned long VdmAllowed : 1; /* bit position: 24 */
			/* 0x0440 */ unsigned long CrossSessionCreate : 1; /* bit position: 25 */
			/* 0x0440 */ unsigned long ProcessInserted : 1; /* bit position: 26 */
			/* 0x0440 */ unsigned long DefaultIoPriority : 3; /* bit position: 27 */
			/* 0x0440 */ unsigned long ProcessSelfDelete : 1; /* bit position: 30 */
			/* 0x0440 */ unsigned long SetTimerResolutionLink : 1; /* bit position: 31 */
		}; /* bitfield */
	}; /* size: 0x0004 */
	/* 0x0444 */ long ExitStatus;
	/* 0x0448 */ struct _MM_AVL_TABLE VadRoot;
	/* 0x0488 */ struct _ALPC_PROCESS_CONTEXT AlpcContext;
	/* 0x04a8 */ struct _LIST_ENTRY TimerResolutionLink;
	/* 0x04b8 */ unsigned long RequestedTimerResolution;
	/* 0x04bc */ unsigned long ActiveThreadsHighWatermark;
	/* 0x04c0 */ unsigned long SmallestTimerResolution;
	/* 0x04c8 */ struct _PO_DIAG_STACK_RECORD* TimerResolutionStackRecord;
} My_EPROCESSW7, *My_PEPROCESSW7; /* size: 0x04d0 */











typedef union _KWAIT_STATUS_REGISTER
{
	union
	{
		/* 0x0000 */ unsigned char Flags;
		struct /* bitfield */
		{
			/* 0x0000 */ unsigned char State : 2; /* bit position: 0 */
			/* 0x0000 */ unsigned char Affinity : 1; /* bit position: 2 */
			/* 0x0000 */ unsigned char Priority : 1; /* bit position: 3 */
			/* 0x0000 */ unsigned char Apc : 1; /* bit position: 4 */
			/* 0x0000 */ unsigned char UserApc : 1; /* bit position: 5 */
			/* 0x0000 */ unsigned char Alert : 1; /* bit position: 6 */
			/* 0x0000 */ unsigned char Unused : 1; /* bit position: 7 */
		}; /* bitfield */
	}; /* size: 0x0001 */
} KWAIT_STATUS_REGISTER, *PKWAIT_STATUS_REGISTER; /* size: 0x0001 */






typedef struct _KTHREAD
{
	/* 0x0000 */ struct _DISPATCHER_HEADER Header;
	/* 0x0018 */ volatile unsigned __int64 CycleTime;
	/* 0x0020 */ unsigned __int64 QuantumTarget;
	/* 0x0028 */ void* InitialStack;
	/* 0x0030 */ void* volatile StackLimit;
	/* 0x0038 */ void* KernelStack;
	/* 0x0040 */ unsigned __int64 ThreadLock;
	/* 0x0048 */ union _KWAIT_STATUS_REGISTER WaitRegister;
	/* 0x0049 */ volatile unsigned char Running;
	/* 0x004a */ unsigned char Alerted[2];
	union
	{
		struct /* bitfield */
		{
			/* 0x004c */ unsigned long KernelStackResident : 1; /* bit position: 0 */
			/* 0x004c */ unsigned long ReadyTransition : 1; /* bit position: 1 */
			/* 0x004c */ unsigned long ProcessReadyQueue : 1; /* bit position: 2 */
			/* 0x004c */ unsigned long WaitNext : 1; /* bit position: 3 */
			/* 0x004c */ unsigned long SystemAffinityActive : 1; /* bit position: 4 */
			/* 0x004c */ unsigned long Alertable : 1; /* bit position: 5 */
			/* 0x004c */ unsigned long GdiFlushActive : 1; /* bit position: 6 */
			/* 0x004c */ unsigned long UserStackWalkActive : 1; /* bit position: 7 */
			/* 0x004c */ unsigned long ApcInterruptRequest : 1; /* bit position: 8 */
			/* 0x004c */ unsigned long ForceDeferSchedule : 1; /* bit position: 9 */
			/* 0x004c */ unsigned long QuantumEndMigrate : 1; /* bit position: 10 */
			/* 0x004c */ unsigned long UmsDirectedSwitchEnable : 1; /* bit position: 11 */
			/* 0x004c */ unsigned long TimerActive : 1; /* bit position: 12 */
			/* 0x004c */ unsigned long Reserved : 19; /* bit position: 13 */
		}; /* bitfield */
		/* 0x004c */ long MiscFlags;
	}; /* size: 0x0004 */
	union
	{
		/* 0x0050 */ struct _KAPC_STATE ApcState;
		struct
		{
			/* 0x0050 */ unsigned char ApcStateFill[43];
			/* 0x007b */ char Priority;
			/* 0x007c */ volatile unsigned long NextProcessor;
		}; /* size: 0x0030 */
	}; /* size: 0x0030 */
	/* 0x0080 */ volatile unsigned long DeferredProcessor;
	/* 0x0088 */ unsigned __int64 ApcQueueLock;
	/* 0x0090 */ volatile __int64 WaitStatus;
	/* 0x0098 */ struct _KWAIT_BLOCK* WaitBlockList;
	union
	{
		/* 0x00a0 */ struct _LIST_ENTRY WaitListEntry;
		/* 0x00a0 */ struct _SINGLE_LIST_ENTRY SwapListEntry;
	}; /* size: 0x0010 */
	/* 0x00b0 */ struct _KQUEUE* volatile Queue;
	/* 0x00b8 */ void* Teb;
	/* 0x00c0 */ struct _KTIMER Timer;
	union
	{
		struct /* bitfield */
		{
			/* 0x0100 */ volatile unsigned long AutoAlignment : 1; /* bit position: 0 */
			/* 0x0100 */ volatile unsigned long DisableBoost : 1; /* bit position: 1 */
			/* 0x0100 */ volatile unsigned long EtwStackTraceApc1Inserted : 1; /* bit position: 2 */
			/* 0x0100 */ volatile unsigned long EtwStackTraceApc2Inserted : 1; /* bit position: 3 */
			/* 0x0100 */ volatile unsigned long CalloutActive : 1; /* bit position: 4 */
			/* 0x0100 */ volatile unsigned long ApcQueueable : 1; /* bit position: 5 */
			/* 0x0100 */ volatile unsigned long EnableStackSwap : 1; /* bit position: 6 */
			/* 0x0100 */ volatile unsigned long GuiThread : 1; /* bit position: 7 */
			/* 0x0100 */ volatile unsigned long UmsPerformingSyscall : 1; /* bit position: 8 */
			/* 0x0100 */ volatile unsigned long ReservedFlags : 23; /* bit position: 9 */
		}; /* bitfield */
		/* 0x0100 */ volatile long ThreadFlags;
	}; /* size: 0x0004 */
	/* 0x0104 */ unsigned long Spare0;
	union
	{
		/* 0x0108 */ struct _KWAIT_BLOCK WaitBlock[4];
		struct
		{
			/* 0x0108 */ unsigned char WaitBlockFill4[44];
			/* 0x0134 */ unsigned long ContextSwitches;
		}; /* size: 0x0030 */
		struct
		{
			/* 0x0108 */ unsigned char WaitBlockFill5[92];
			/* 0x0164 */ volatile unsigned char State;
			/* 0x0165 */ char NpxState;
			/* 0x0166 */ unsigned char WaitIrql;
			/* 0x0167 */ char WaitMode;
		}; /* size: 0x0060 */
		struct
		{
			/* 0x0108 */ unsigned char WaitBlockFill6[140];
			/* 0x0194 */ unsigned long WaitTime;
		}; /* size: 0x0090 */
		struct
		{
			/* 0x0108 */ unsigned char WaitBlockFill7[168];
			/* 0x01b0 */ void* TebMappedLowVa;
			/* 0x01b8 */ struct _UMS_CONTROL_BLOCK* Ucb;
		}; /* size: 0x00b8 */
		struct
		{
			/* 0x0108 */ unsigned char WaitBlockFill8[188];
			union
			{
				struct
				{
					/* 0x01c4 */ short KernelApcDisable;
					/* 0x01c6 */ short SpecialApcDisable;
				}; /* size: 0x0004 */
				/* 0x01c4 */ unsigned long CombinedApcDisable;
			}; /* size: 0x0004 */
		}; /* size: 0x00c0 */
	}; /* size: 0x00c0 */
	/* 0x01c8 */ struct _LIST_ENTRY QueueListEntry;
	/* 0x01d8 */ struct _KTRAP_FRAME* TrapFrame;
	/* 0x01e0 */ void* FirstArgument;
	union
	{
		/* 0x01e8 */ void* CallbackStack;
		/* 0x01e8 */ unsigned __int64 CallbackDepth;
	}; /* size: 0x0008 */
	/* 0x01f0 */ unsigned char ApcStateIndex;
	/* 0x01f1 */ char BasePriority;
	union
	{
		/* 0x01f2 */ char PriorityDecrement;
		struct /* bitfield */
		{
			/* 0x01f2 */ unsigned char ForegroundBoost : 4; /* bit position: 0 */
			/* 0x01f2 */ unsigned char UnusualBoost : 4; /* bit position: 4 */
		}; /* bitfield */
	}; /* size: 0x0001 */
	/* 0x01f3 */ unsigned char Preempted;
	/* 0x01f4 */ unsigned char AdjustReason;
	/* 0x01f5 */ char AdjustIncrement;
	/* 0x01f6 */ char PreviousMode;
	/* 0x01f7 */ char Saturation;
	/* 0x01f8 */ unsigned long SystemCallNumber;
	/* 0x01fc */ unsigned long FreezeCount;
	/* 0x0200 */ volatile struct _GROUP_AFFINITY UserAffinity;
	/* 0x0210 */ struct _KPROCESS* Process;
	/* 0x0218 */ volatile struct _GROUP_AFFINITY Affinity;
	/* 0x0228 */ unsigned long IdealProcessor;
	/* 0x022c */ unsigned long UserIdealProcessor;
	/* 0x0230 */ struct _KAPC_STATE* ApcStatePointer[2];
	union
	{
		/* 0x0240 */ struct _KAPC_STATE SavedApcState;
		struct
		{
			/* 0x0240 */ unsigned char SavedApcStateFill[43];
			/* 0x026b */ unsigned char WaitReason;
			/* 0x026c */ char SuspendCount;
			/* 0x026d */ char Spare1;
			/* 0x026e */ unsigned char CodePatchInProgress;
		}; /* size: 0x002f */
	}; /* size: 0x0030 */
	/* 0x0270 */ void* volatile Win32Thread;
	/* 0x0278 */ void* StackBase;
	union
	{
		/* 0x0280 */ struct _KAPC SuspendApc;
		struct
		{
			/* 0x0280 */ unsigned char SuspendApcFill0[1];
			/* 0x0281 */ unsigned char ResourceIndex;
		}; /* size: 0x0002 */
		struct
		{
			/* 0x0280 */ unsigned char SuspendApcFill1[3];
			/* 0x0283 */ unsigned char QuantumReset;
		}; /* size: 0x0004 */
		struct
		{
			/* 0x0280 */ unsigned char SuspendApcFill2[4];
			/* 0x0284 */ unsigned long KernelTime;
		}; /* size: 0x0008 */
		struct
		{
			/* 0x0280 */ unsigned char SuspendApcFill3[64];
			/* 0x02c0 */ struct _KPRCB* volatile WaitPrcb;
		}; /* size: 0x0048 */
		struct
		{
			/* 0x0280 */ unsigned char SuspendApcFill4[72];
			/* 0x02c8 */ void* LegoData;
		}; /* size: 0x0050 */
		struct
		{
			/* 0x0280 */ unsigned char SuspendApcFill5[83];
			/* 0x02d3 */ unsigned char LargeStack;
			/* 0x02d4 */ unsigned long UserTime;
		}; /* size: 0x0058 */
	}; /* size: 0x0058 */
	union
	{
		/* 0x02d8 */ struct _KSEMAPHORE SuspendSemaphore;
		struct
		{
			/* 0x02d8 */ unsigned char SuspendSemaphorefill[28];
			/* 0x02f4 */ unsigned long SListFaultCount;
		}; /* size: 0x0020 */
	}; /* size: 0x0020 */
	/* 0x02f8 */ struct _LIST_ENTRY ThreadListEntry;
	/* 0x0308 */ struct _LIST_ENTRY MutantListHead;
	/* 0x0318 */ void* SListFaultAddress;
	/* 0x0320 */ __int64 ReadOperationCount;
	/* 0x0328 */ __int64 WriteOperationCount;
	/* 0x0330 */ __int64 OtherOperationCount;
	/* 0x0338 */ __int64 ReadTransferCount;
	/* 0x0340 */ __int64 WriteTransferCount;
	/* 0x0348 */ __int64 OtherTransferCount;
	/* 0x0350 */ struct _KTHREAD_COUNTERS* ThreadCounters;
	/* 0x0358 */ struct _XSTATE_SAVE* XStateSave;
} KTHREAD, *PKTHREAD; /* size: 0x0360 */




typedef union _PS_CLIENT_SECURITY_CONTEXT
{
	union
	{
		/* 0x0000 */ unsigned __int64 ImpersonationData;
		/* 0x0000 */ void* ImpersonationToken;
		struct /* bitfield */
		{
			/* 0x0000 */ unsigned __int64 ImpersonationLevel : 2; /* bit position: 0 */
			/* 0x0000 */ unsigned __int64 EffectiveOnly : 1; /* bit position: 2 */
		}; /* bitfield */
	}; /* size: 0x0008 */
} PS_CLIENT_SECURITY_CONTEXT, *PPS_CLIENT_SECURITY_CONTEXT; /* size: 0x0008 */


typedef struct _ETHREAD
{
	/* 0x0000 */ struct _KTHREAD Tcb;
	/* 0x0360 */ union _LARGE_INTEGER CreateTime;
	union
	{
		/* 0x0368 */ union _LARGE_INTEGER ExitTime;
		/* 0x0368 */ struct _LIST_ENTRY KeyedWaitChain;
	}; /* size: 0x0010 */
	/* 0x0378 */ long ExitStatus;
	union
	{
		/* 0x0380 */ struct _LIST_ENTRY PostBlockList;
		struct
		{
			/* 0x0380 */ void* ForwardLinkShadow;
			/* 0x0388 */ void* StartAddress;
		}; /* size: 0x0010 */
	}; /* size: 0x0010 */
	union
	{
		/* 0x0390 */ struct _TERMINATION_PORT* TerminationPort;
		/* 0x0390 */ struct _ETHREAD* ReaperLink;
		/* 0x0390 */ void* KeyedWaitValue;
	}; /* size: 0x0008 */
	/* 0x0398 */ unsigned __int64 ActiveTimerListLock;
	/* 0x03a0 */ struct _LIST_ENTRY ActiveTimerListHead;
	/* 0x03b0 */ struct _CLIENT_ID Cid;
	union
	{
		/* 0x03c0 */ struct _KSEMAPHORE KeyedWaitSemaphore;
		/* 0x03c0 */ struct _KSEMAPHORE AlpcWaitSemaphore;
	}; /* size: 0x0020 */
	/* 0x03e0 */ union _PS_CLIENT_SECURITY_CONTEXT ClientSecurity;
	/* 0x03e8 */ struct _LIST_ENTRY IrpList;
	/* 0x03f8 */ unsigned __int64 TopLevelIrp;
	/* 0x0400 */ struct _DEVICE_OBJECT* DeviceToVerify;
	/* 0x0408 */ union _PSP_CPU_QUOTA_APC* CpuQuotaApc;
	/* 0x0410 */ void* Win32StartAddress;
	/* 0x0418 */ void* LegacyPowerObject;
	/* 0x0420 */ struct _LIST_ENTRY ThreadListEntry;
	/* 0x0430 */ struct _EX_RUNDOWN_REF RundownProtect;
	/* 0x0438 */ struct _EX_PUSH_LOCK ThreadLock;
	/* 0x0440 */ unsigned long ReadClusterSize;
	/* 0x0444 */ volatile long MmLockOrdering;
	union
	{
		/* 0x0448 */ unsigned long CrossThreadFlags;
		struct /* bitfield */
		{
			/* 0x0448 */ unsigned long Terminated : 1; /* bit position: 0 */
			/* 0x0448 */ unsigned long ThreadInserted : 1; /* bit position: 1 */
			/* 0x0448 */ unsigned long HideFromDebugger : 1; /* bit position: 2 */
			/* 0x0448 */ unsigned long ActiveImpersonationInfo : 1; /* bit position: 3 */
			/* 0x0448 */ unsigned long SystemThread : 1; /* bit position: 4 */
			/* 0x0448 */ unsigned long HardErrorsAreDisabled : 1; /* bit position: 5 */
			/* 0x0448 */ unsigned long BreakOnTermination : 1; /* bit position: 6 */
			/* 0x0448 */ unsigned long SkipCreationMsg : 1; /* bit position: 7 */
			/* 0x0448 */ unsigned long SkipTerminationMsg : 1; /* bit position: 8 */
			/* 0x0448 */ unsigned long CopyTokenOnOpen : 1; /* bit position: 9 */
			/* 0x0448 */ unsigned long ThreadIoPriority : 3; /* bit position: 10 */
			/* 0x0448 */ unsigned long ThreadPagePriority : 3; /* bit position: 13 */
			/* 0x0448 */ unsigned long RundownFail : 1; /* bit position: 16 */
			/* 0x0448 */ unsigned long NeedsWorkingSetAging : 1; /* bit position: 17 */
		}; /* bitfield */
	}; /* size: 0x0004 */
	union
	{
		/* 0x044c */ unsigned long SameThreadPassiveFlags;
		struct /* bitfield */
		{
			/* 0x044c */ unsigned long ActiveExWorker : 1; /* bit position: 0 */
			/* 0x044c */ unsigned long ExWorkerCanWaitUser : 1; /* bit position: 1 */
			/* 0x044c */ unsigned long MemoryMaker : 1; /* bit position: 2 */
			/* 0x044c */ unsigned long ClonedThread : 1; /* bit position: 3 */
			/* 0x044c */ unsigned long KeyedEventInUse : 1; /* bit position: 4 */
			/* 0x044c */ unsigned long RateApcState : 2; /* bit position: 5 */
			/* 0x044c */ unsigned long SelfTerminate : 1; /* bit position: 7 */
		}; /* bitfield */
	}; /* size: 0x0004 */
	union
	{
		/* 0x0450 */ unsigned long SameThreadApcFlags;
		struct
		{
			struct /* bitfield */
			{
				/* 0x0450 */ unsigned char Spare : 1; /* bit position: 0 */
				/* 0x0450 */ volatile unsigned char StartAddressInvalid : 1; /* bit position: 1 */
				/* 0x0450 */ unsigned char EtwPageFaultCalloutActive : 1; /* bit position: 2 */
				/* 0x0450 */ unsigned char OwnsProcessWorkingSetExclusive : 1; /* bit position: 3 */
				/* 0x0450 */ unsigned char OwnsProcessWorkingSetShared : 1; /* bit position: 4 */
				/* 0x0450 */ unsigned char OwnsSystemCacheWorkingSetExclusive : 1; /* bit position: 5 */
				/* 0x0450 */ unsigned char OwnsSystemCacheWorkingSetShared : 1; /* bit position: 6 */
				/* 0x0450 */ unsigned char OwnsSessionWorkingSetExclusive : 1; /* bit position: 7 */
			}; /* bitfield */
			struct /* bitfield */
			{
				/* 0x0451 */ unsigned char OwnsSessionWorkingSetShared : 1; /* bit position: 0 */
				/* 0x0451 */ unsigned char OwnsProcessAddressSpaceExclusive : 1; /* bit position: 1 */
				/* 0x0451 */ unsigned char OwnsProcessAddressSpaceShared : 1; /* bit position: 2 */
				/* 0x0451 */ unsigned char SuppressSymbolLoad : 1; /* bit position: 3 */
				/* 0x0451 */ unsigned char Prefetching : 1; /* bit position: 4 */
				/* 0x0451 */ unsigned char OwnsDynamicMemoryShared : 1; /* bit position: 5 */
				/* 0x0451 */ unsigned char OwnsChangeControlAreaExclusive : 1; /* bit position: 6 */
				/* 0x0451 */ unsigned char OwnsChangeControlAreaShared : 1; /* bit position: 7 */
			}; /* bitfield */
			struct /* bitfield */
			{
				/* 0x0452 */ unsigned char OwnsPagedPoolWorkingSetExclusive : 1; /* bit position: 0 */
				/* 0x0452 */ unsigned char OwnsPagedPoolWorkingSetShared : 1; /* bit position: 1 */
				/* 0x0452 */ unsigned char OwnsSystemPtesWorkingSetExclusive : 1; /* bit position: 2 */
				/* 0x0452 */ unsigned char OwnsSystemPtesWorkingSetShared : 1; /* bit position: 3 */
				/* 0x0452 */ unsigned char TrimTrigger : 2; /* bit position: 4 */
				/* 0x0452 */ unsigned char Spare1 : 2; /* bit position: 6 */
			}; /* bitfield */
			/* 0x0453 */ unsigned char PriorityRegionActive;
		}; /* size: 0x0004 */
	}; /* size: 0x0004 */
	/* 0x0454 */ unsigned char CacheManagerActive;
	/* 0x0455 */ unsigned char DisablePageFaultClustering;
	/* 0x0456 */ unsigned char ActiveFaultCount;
	/* 0x0457 */ unsigned char LockOrderState;
	/* 0x0458 */ unsigned __int64 AlpcMessageId;
	union
	{
		/* 0x0460 */ void* AlpcMessage;
		/* 0x0460 */ unsigned long AlpcReceiveAttributeSet;
	}; /* size: 0x0008 */
	/* 0x0468 */ struct _LIST_ENTRY AlpcWaitListEntry;
	/* 0x0478 */ unsigned long CacheManagerCount;
	/* 0x047c */ unsigned long IoBoostCount;
	/* 0x0480 */ unsigned __int64 IrpListLock;
	/* 0x0488 */ void* ReservedForSynchTracking;
	/* 0x0490 */ struct _SINGLE_LIST_ENTRY CmCallbackListHead;
} My_ETHREADW7, *My_PETHREADW7; /* size: 0x0498 */


typedef struct _SYSTEM_THREAD_INFORMATION
{
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PVOID StartAddress;
	CLIENT_ID ClientId;
	KPRIORITY Priority;
	LONG BasePriority;
	ULONG ContextSwitches;
	ULONG ThreadState;
	KWAIT_REASON WaitReason;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFO
{
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER WorkingSetPrivateSize;
	ULONG HardFaultCount;
	ULONG NumberOfThreadsHighWatermark;
	ULONGLONG CycleTime;
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	KPRIORITY BasePriority;
	HANDLE UniqueProcessId;
	HANDLE InheritedFromUniqueProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR UniqueProcessKey;
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
	SYSTEM_THREAD_INFORMATION Threads[1];
} SYSTEM_PROCESS_INFO, *PSYSTEM_PROCESS_INFO;



#pragma pack(4)
typedef struct _PEB32
{
	UCHAR InheritedAddressSpace;
	UCHAR ReadImageFileExecOptions;
	UCHAR BeingDebugged;
	UCHAR BitField;
	ULONG Mutant;
	ULONG ImageBaseAddress;
	ULONG Ldr;
	ULONG ProcessParameters;
	ULONG SubSystemData;
	ULONG ProcessHeap;
	ULONG FastPebLock;
	ULONG AtlThunkSListPtr;
	ULONG IFEOKey;
	ULONG CrossProcessFlags;
	ULONG UserSharedInfoPtr;
	ULONG SystemReserved;
	ULONG AtlThunkSListPtr32;
	ULONG ApiSetMap;
} PEB32, *PPEB32;

typedef struct _PEB_LDR_DATA32
{
	ULONG Length;
	UCHAR Initialized;
	ULONG SsHandle;
	LIST_ENTRY32 InLoadOrderModuleList;
	LIST_ENTRY32 InMemoryOrderModuleList;
	LIST_ENTRY32 InInitializationOrderModuleList;
} PEB_LDR_DATA32, *PPEB_LDR_DATA32;

typedef struct _LDR_DATA_TABLE_ENTRY32
{
	LIST_ENTRY32 InLoadOrderLinks;
	LIST_ENTRY32 InMemoryOrderLinks;
	LIST_ENTRY32 InInitializationOrderLinks;
	ULONG DllBase;
	ULONG EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING32 FullDllName;
	UNICODE_STRING32 BaseDllName;
	ULONG Flags;
	USHORT LoadCount;
	USHORT TlsIndex;
	LIST_ENTRY32 HashLinks;
	ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY32, *PLDR_DATA_TABLE_ENTRY32;
#pragma pack()
#define HB_POOL_TAG                '0mVZ'
#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES        16
typedef struct _IMAGE_SECTION_HEADER
{
	UCHAR  Name[8];
	union
	{
		ULONG PhysicalAddress;
		ULONG VirtualSize;
	} Misc;
	ULONG VirtualAddress;
	ULONG SizeOfRawData;
	ULONG PointerToRawData;
	ULONG PointerToRelocations;
	ULONG PointerToLinenumbers;
	USHORT  NumberOfRelocations;
	USHORT  NumberOfLinenumbers;
	ULONG Characteristics;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;
typedef struct _IMAGE_DATA_DIRECTORY
{
	ULONG VirtualAddress;
	ULONG Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;



typedef struct _SYSTEM_MODULE_INFORMATION {
	HANDLE Section;
	PVOID MappedBase;
	PVOID Base;
	ULONG Size;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT PathLength;
	CHAR ImageName[256];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

typedef struct _KLDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY64 InLoadOrderLinks;
	ULONG64 __Undefined1;
	ULONG64 __Undefined2;
	ULONG64 __Undefined3;
	ULONG64 NonPagedDebugInfo;
	ULONG64 DllBase;
	ULONG64 EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG   Flags;
	USHORT  LoadCount;
	USHORT  __Undefined5;
	ULONG64 __Undefined6;
	ULONG   CheckSum;
	ULONG   __padding1;
	ULONG   TimeDateStamp;
	ULONG   __padding2;
}KLDR_DATA_TABLE_ENTRY, *PKLDR_DATA_TABLE_ENTRY;



typedef struct _IMAGE_FILE_HEADER // Size=20
{
	USHORT Machine;
	USHORT NumberOfSections;
	ULONG TimeDateStamp;
	ULONG PointerToSymbolTable;
	ULONG NumberOfSymbols;
	USHORT SizeOfOptionalHeader;
	USHORT Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
typedef struct _IMAGE_OPTIONAL_HEADER64
{
	USHORT Magic;
	UCHAR MajorLinkerVersion;
	UCHAR MinorLinkerVersion;
	ULONG SizeOfCode;
	ULONG SizeOfInitializedData;
	ULONG SizeOfUninitializedData;
	ULONG AddressOfEntryPoint;
	ULONG BaseOfCode;
	ULONGLONG ImageBase;
	ULONG SectionAlignment;
	ULONG FileAlignment;
	USHORT MajorOperatingSystemVersion;
	USHORT MinorOperatingSystemVersion;
	USHORT MajorImageVersion;
	USHORT MinorImageVersion;
	USHORT MajorSubsystemVersion;
	USHORT MinorSubsystemVersion;
	ULONG Win32VersionValue;
	ULONG SizeOfImage;
	ULONG SizeOfHeaders;
	ULONG CheckSum;
	USHORT Subsystem;
	USHORT DllCharacteristics;
	ULONGLONG SizeOfStackReserve;
	ULONGLONG SizeOfStackCommit;
	ULONGLONG SizeOfHeapReserve;
	ULONGLONG SizeOfHeapCommit;
	ULONG LoaderFlags;
	ULONG NumberOfRvaAndSizes;
	struct _IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;
typedef struct _IMAGE_NT_HEADERS64
{
	ULONG Signature;
	struct _IMAGE_FILE_HEADER FileHeader;
	struct _IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;
typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	HANDLE Section;         // Not filled in
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR  FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;
typedef struct _RTL_PROCESS_MODULES
{
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;
typedef struct _MY_SYSTEM_HANDLE_TABLE_ENTRY_INFO {
	USHORT UniqueProcessId;
	USHORT CreatorBackTraceIndex;
	UCHAR ObjectTypeIndex;
	UCHAR HandleAttributes;
	USHORT HandleValue;
	PVOID Object;
	ULONG GrantedAccess;
} MY_SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PMY_SYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _MY_SYSTEM_HANDLE_INFORMATION {
	ULONG NumberOfHandles;
	MY_SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} MY_SYSTEM_HANDLE_INFORMATION, *PMY_SYSTEM_HANDLE_INFORMATION;


typedef enum _SYSTEM_INFORMATION_CLASS
{
	SystemBasicInformation = 0x0,
	SystemProcessorInformation = 0x1,
	SystemPerformanceInformation = 0x2,
	SystemTimeOfDayInformation = 0x3,
	SystemPathInformation = 0x4,
	SystemProcessInformation = 0x5,
	SystemCallCountInformation = 0x6,
	SystemDeviceInformation = 0x7,
	SystemProcessorPerformanceInformation = 0x8,
	SystemFlagsInformation = 0x9,
	SystemCallTimeInformation = 0xa,
	SystemModuleInformation = 0xb,
	SystemLocksInformation = 0xc,
	SystemStackTraceInformation = 0xd,
	SystemPagedPoolInformation = 0xe,
	SystemNonPagedPoolInformation = 0xf,
	SystemHandleInformation = 0x10,
	SystemObjectInformation = 0x11,
	SystemPageFileInformation = 0x12,
	SystemVdmInstemulInformation = 0x13,
	SystemVdmBopInformation = 0x14,
	SystemFileCacheInformation = 0x15,
	SystemPoolTagInformation = 0x16,
	SystemInterruptInformation = 0x17,
	SystemDpcBehaviorInformation = 0x18,
	SystemFullMemoryInformation = 0x19,
	SystemLoadGdiDriverInformation = 0x1a,
	SystemUnloadGdiDriverInformation = 0x1b,
	SystemTimeAdjustmentInformation = 0x1c,
	SystemSummaryMemoryInformation = 0x1d,
	SystemMirrorMemoryInformation = 0x1e,
	SystemPerformanceTraceInformation = 0x1f,
	SystemObsolete0 = 0x20,
	SystemExceptionInformation = 0x21,
	SystemCrashDumpStateInformation = 0x22,
	SystemKernelDebuggerInformation = 0x23,
	SystemContextSwitchInformation = 0x24,
	SystemRegistryQuotaInformation = 0x25,
	SystemExtendServiceTableInformation = 0x26,
	SystemPrioritySeperation = 0x27,
	SystemVerifierAddDriverInformation = 0x28,
	SystemVerifierRemoveDriverInformation = 0x29,
	SystemProcessorIdleInformation = 0x2a,
	SystemLegacyDriverInformation = 0x2b,
	SystemCurrentTimeZoneInformation = 0x2c,
	SystemLookasideInformation = 0x2d,
	SystemTimeSlipNotification = 0x2e,
	SystemSessionCreate = 0x2f,
	SystemSessionDetach = 0x30,
	SystemSessionInformation = 0x31,
	SystemRangeStartInformation = 0x32,
	SystemVerifierInformation = 0x33,
	SystemVerifierThunkExtend = 0x34,
	SystemSessionProcessInformation = 0x35,
	SystemLoadGdiDriverInSystemSpace = 0x36,
	SystemNumaProcessorMap = 0x37,
	SystemPrefetcherInformation = 0x38,
	SystemExtendedProcessInformation = 0x39,
	SystemRecommendedSharedDataAlignment = 0x3a,
	SystemComPlusPackage = 0x3b,
	SystemNumaAvailableMemory = 0x3c,
	SystemProcessorPowerInformation = 0x3d,
	SystemEmulationBasicInformation = 0x3e,
	SystemEmulationProcessorInformation = 0x3f,
	SystemExtendedHandleInformation = 0x40,
	SystemLostDelayedWriteInformation = 0x41,
	SystemBigPoolInformation = 0x42,
	SystemSessionPoolTagInformation = 0x43,
	SystemSessionMappedViewInformation = 0x44,
	SystemHotpatchInformation = 0x45,
	SystemObjectSecurityMode = 0x46,
	SystemWatchdogTimerHandler = 0x47,
	SystemWatchdogTimerInformation = 0x48,
	SystemLogicalProcessorInformation = 0x49,
	SystemWow64SharedInformationObsolete = 0x4a,
	SystemRegisterFirmwareTableInformationHandler = 0x4b,
	SystemFirmwareTableInformation = 0x4c,
	SystemModuleInformationEx = 0x4d,
	SystemVerifierTriageInformation = 0x4e,
	SystemSuperfetchInformation = 0x4f,
	SystemMemoryListInformation = 0x50,
	SystemFileCacheInformationEx = 0x51,
	SystemThreadPriorityClientIdInformation = 0x52,
	SystemProcessorIdleCycleTimeInformation = 0x53,
	SystemVerifierCancellationInformation = 0x54,
	SystemProcessorPowerInformationEx = 0x55,
	SystemRefTraceInformation = 0x56,
	SystemSpecialPoolInformation = 0x57,
	SystemProcessIdInformation = 0x58,
	SystemErrorPortInformation = 0x59,
	SystemBootEnvironmentInformation = 0x5a,
	SystemHypervisorInformation = 0x5b,
	SystemVerifierInformationEx = 0x5c,
	SystemTimeZoneInformation = 0x5d,
	SystemImageFileExecutionOptionsInformation = 0x5e,
	SystemCoverageInformation = 0x5f,
	SystemPrefetchPatchInformation = 0x60,
	SystemVerifierFaultsInformation = 0x61,
	SystemSystemPartitionInformation = 0x62,
	SystemSystemDiskInformation = 0x63,
	SystemProcessorPerformanceDistribution = 0x64,
	SystemNumaProximityNodeInformation = 0x65,
	SystemDynamicTimeZoneInformation = 0x66,
	SystemCodeIntegrityInformation = 0x67,
	SystemProcessorMicrocodeUpdateInformation = 0x68,
	SystemProcessorBrandString = 0x69,
	SystemVirtualAddressInformation = 0x6a,
	SystemLogicalProcessorAndGroupInformation = 0x6b,
	SystemProcessorCycleTimeInformation = 0x6c,
	SystemStoreInformation = 0x6d,
	SystemRegistryAppendString = 0x6e,
	SystemAitSamplingValue = 0x6f,
	SystemVhdBootInformation = 0x70,
	SystemCpuQuotaInformation = 0x71,
	SystemNativeBasicInformation = 0x72,
	SystemErrorPortTimeouts = 0x73,
	SystemLowPriorityIoInformation = 0x74,
	SystemBootEntropyInformation = 0x75,
	SystemVerifierCountersInformation = 0x76,
	SystemPagedPoolInformationEx = 0x77,
	SystemSystemPtesInformationEx = 0x78,
	SystemNodeDistanceInformation = 0x79,
	SystemAcpiAuditInformation = 0x7a,
	SystemBasicPerformanceInformation = 0x7b,
	SystemQueryPerformanceCounterInformation = 0x7c,
	SystemSessionBigPoolInformation = 0x7d,
	SystemBootGraphicsInformation = 0x7e,
	SystemScrubPhysicalMemoryInformation = 0x7f,
	SystemBadPageInformation = 0x80,
	SystemProcessorProfileControlArea = 0x81,
	SystemCombinePhysicalMemoryInformation = 0x82,
	SystemEntropyInterruptTimingInformation = 0x83,
	SystemConsoleInformation = 0x84,
	SystemPlatformBinaryInformation = 0x85,
	SystemThrottleNotificationInformation = 0x86,
	SystemHypervisorProcessorCountInformation = 0x87,
	SystemDeviceDataInformation = 0x88,
	SystemDeviceDataEnumerationInformation = 0x89,
	SystemMemoryTopologyInformation = 0x8a,
	SystemMemoryChannelInformation = 0x8b,
	SystemBootLogoInformation = 0x8c,
	SystemProcessorPerformanceInformationEx = 0x8d,
	SystemSpare0 = 0x8e,
	SystemSecureBootPolicyInformation = 0x8f,
	SystemPageFileInformationEx = 0x90,
	SystemSecureBootInformation = 0x91,
	SystemEntropyInterruptTimingRawInformation = 0x92,
	SystemPortableWorkspaceEfiLauncherInformation = 0x93,
	SystemFullProcessInformation = 0x94,
	SystemKernelDebuggerInformationEx = 0x95,
	SystemBootMetadataInformation = 0x96,
	SystemSoftRebootInformation = 0x97,
	SystemElamCertificateInformation = 0x98,
	SystemOfflineDumpConfigInformation = 0x99,
	SystemProcessorFeaturesInformation = 0x9a,
	SystemRegistryReconciliationInformation = 0x9b,
	MaxSystemInfoClass = 0x9c,
} SYSTEM_INFORMATION_CLASS;



typedef enum _KAPC_ENVIRONMENT
{
	OriginalApcEnvironment,
	AttachedApcEnvironment,
	CurrentApcEnvironment,
	InsertApcEnvironment
} KAPC_ENVIRONMENT;
typedef VOID(*PKNORMAL_ROUTINE) (
	IN PVOID NormalContext,
	IN PVOID SystemArgument1,
	IN PVOID SystemArgument2
	);

typedef VOID(*PKKERNEL_ROUTINE) (
	IN struct _KAPC *Apc,
	IN OUT PKNORMAL_ROUTINE *NormalRoutine,
	IN OUT PVOID *NormalContext,
	IN OUT PVOID *SystemArgument1,
	IN OUT PVOID *SystemArgument2
	);

typedef VOID(*PKRUNDOWN_ROUTINE) (
	IN struct _KAPC *Apc
	);


#ifdef __cplusplus
extern "C"
{
#endif
	NTKERNELAPI
		NTSTATUS
		NTAPI
		ObCreateObject(
			__in KPROCESSOR_MODE ProbeMode,
			__in POBJECT_TYPE ObjectType,
			__in_opt POBJECT_ATTRIBUTES ObjectAttributes,
			__in KPROCESSOR_MODE OwnershipMode,
			__inout_opt PVOID ParseContext,
			__in ULONG ObjectBodySize,
			__in ULONG PagedPoolCharge,
			__in ULONG NonPagedPoolCharge,
			__out PVOID *Object
		);
	NTSTATUS NTAPI MmCopyVirtualMemory(IN PEPROCESS SourceProcess,
		IN PVOID SourceAddress,
		IN PEPROCESS TargetProcess,
		OUT PVOID TargetAddress,
		IN SIZE_T BufferSize,
		IN KPROCESSOR_MODE PreviousMode,
		OUT PSIZE_T ReturnSize);

	VOID NTAPI KeInitializeApc(__in PKAPC 	Apc,
		__in PKTHREAD 	Thread,
		__in KAPC_ENVIRONMENT 	TargetEnvironment,
		__in PKKERNEL_ROUTINE 	KernelRoutine,
		__in_opt PKRUNDOWN_ROUTINE 	RundownRoutine,
		__in PKNORMAL_ROUTINE 	NormalRoutine,
		__in KPROCESSOR_MODE 	Mode,
		__in PVOID 	Context
	);

	BOOLEAN
		NTAPI
		KeInsertQueueApc(IN PKAPC Apc,
			IN PVOID SystemArgument1,
			IN PVOID SystemArgument2,
			IN KPRIORITY PriorityBoost);
	NTKERNELAPI NTSTATUS NTAPI ZwQuerySystemInformation(
		_In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
		_Out_ PVOID SystemInformation,
		_In_ ULONG SystemInformationLength,
		_Out_ PULONG ReturnLength
	);

	NTKERNELAPI PVOID NTAPI PsGetProcessWow64Process(
		_In_ PEPROCESS Process
	);

	NTSYSAPI
		NTSTATUS
		NTAPI
		ZwQueryObject
		(
			HANDLE	Handle,
			OBJECT_INFORMATION_CLASS ObjectInformationClass,
			PVOID	ObjectInformation,
			ULONG	ObjectInformationLength,
			PULONG	ReturnLength OPTIONAL
		);

	NTSYSAPI
		NTSTATUS
		NTAPI
		ZwQuerySystemInformation
		(
			SYSTEM_INFORMATION_CLASS	SystemInformationClass,
			PVOID	SystemInformation,
			ULONG	SystemInformationLength,
			PULONG	ReturnLength
		);

	NTSYSAPI
		NTSTATUS
		NTAPI
		ZwDuplicateObject
		(
			HANDLE	SourceProcessHandle,
			HANDLE	SourceHandle,
			HANDLE	TargetProcessHandle OPTIONAL,
			PHANDLE 	TargetHandle OPTIONAL,
			ACCESS_MASK	DesiredAccess,
			ULONG	HandleAttributes,
			ULONG	Options
		);

	NTSYSAPI
		NTSTATUS
		NTAPI
		ZwOpenProcess
		(
			PHANDLE	ProcessHandle,
			ACCESS_MASK	AccessMask,
			POBJECT_ATTRIBUTES	ObjectAttributes,
			PCLIENT_ID	ClientId
		);


	NTKERNELAPI
		PVOID
		NTAPI
		ObGetObjectType(IN PVOID pObject);


	NTSYSAPI
		PIMAGE_NT_HEADERS
		NTAPI
		RtlImageNtHeader(
			_In_ PVOID Base
		);


#ifdef __cplusplus
}
#endif

