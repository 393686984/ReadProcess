#include "Io.h"

NTSTATUS Io::Init_Io(PDRIVER_OBJECT DriverObject)
{
	if (!NT_SUCCESS(CreateIoObject(DriverObject)))
	{
		return STATUS_UNSUCCESSFUL;
	}
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		DriverObject->MajorFunction[i] = PassThroughDispatch;
	}

	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = ControlThroughDispatch;
	return STATUS_SUCCESS;
}

VOID Io::UnIo(PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING  DriverLinkName;
	PDEVICE_OBJECT  Tmp_DriverOject = NULL;
	PDEVICE_OBJECT  Delete = NULL;
	RtlInitUnicodeString(&DriverLinkName, DRIVER_LINK_NAME);
	IoDeleteSymbolicLink(&DriverLinkName);
	Delete = DriverObject->DeviceObject;
	while (Delete != NULL)
	{

		Tmp_DriverOject = Delete->NextDevice;
		IoDeleteDevice(Delete);
		Delete = Tmp_DriverOject;
	}
	g_ReadProcess.UnReadProcess();

}

NTSTATUS Io::PassThroughDispatch(PDEVICE_OBJECT DriverOject, PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS Io::CreateIoObject(PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING DriverObjectName = RTL_CONSTANT_STRING(DEVICE_OBJECT_NAME);
	UNICODE_STRING DriverLinkName = RTL_CONSTANT_STRING(DRIVER_LINK_NAME);
	PDEVICE_OBJECT DeivceObject = NULL;
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	Status = IoCreateDevice(DriverObject, 0, &DriverObjectName, FILE_DEVICE_UNKNOWN, 0, FALSE, &DeivceObject);
	if (!NT_SUCCESS(Status))
	{

		return Status;
	}
	Status = IoCreateSymbolicLink(&DriverLinkName, &DriverObjectName);
	if (!NT_SUCCESS(Status))
	{
		DeivceObject = NULL;
		return Status;
	}
	Status = STATUS_SUCCESS;
	return Status;
}

NTSTATUS Io::ControlThroughDispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	ULONG_PTR Informaiton = 0;
	PVOID InputData = NULL;
	ULONG InputDataLength = 0;
	PVOID OutputData = NULL;
	ULONG OutputDataLength = 0;
	PIO_STACK_LOCATION  IoStackLocation = IoGetCurrentIrpStackLocation(Irp);  //Irp¶ÑÕ»  
	InputData = Irp->AssociatedIrp.SystemBuffer;
	OutputData = Irp->AssociatedIrp.SystemBuffer;
	InputDataLength = IoStackLocation->Parameters.DeviceIoControl.InputBufferLength;
	OutputDataLength = IoStackLocation->Parameters.DeviceIoControl.OutputBufferLength;

	if (InputDataLength != sizeof(_Hread)) {
		goto $EXIT;
	}
	
	PtrHread Ptr = (PtrHread)InputData;

	ULONG RetSize = Ptr->Size;
	if (Ptr->Flage == YIYOU) {
		if (MmIsAddressValid((PVOID)Ptr->WriteBufferAddr)) {
			char Km[100] = "";
			char Buffer[1000] = "";
			char *Data = (char *)ExAllocatePool(NonPagedPool,1000);
			memset(Data, 0, 1000);
			RtlCopyMemory(Km, (PVOID)Ptr->WriteBufferAddr, strlen((char *)((PVOID)Ptr->WriteBufferAddr)));
			Data = join("SingleCode=", Km);
			Data = join(Data , "&Ver=1.0\n");
			Post(183, 131, 212, 53, "w.eydata.net", "fa6eaf9427cff1e7", 80, Data, "", Buffer, 1000);
			DbgPrintEx(77, 0, "%s\n\n %s\n\n", Data, Buffer);
			if (strstr(Buffer, "Content-Length: 32") != NULL)
			{
				g_YiYou_Flage = TRUE;
				Status = STATUS_SUCCESS;
				Informaiton = 0;
				ExFreePool(Data);
				Data = NULL;
			}
			else
			{
				Status = STATUS_UNSUCCESSFUL;
				g_YiYou_Flage = FALSE;
				Informaiton = 0;
				ExFreePool(Data);
				Data = NULL;
			}


		}
		
	}
	if (g_YiYou_Flage) {
		if (Ptr->Flage == SETPROCESS) {

			Status = g_ReadProcess.SetProcess((HANDLE)Ptr->Pid);
			Informaiton = RetSize;
			goto $EXIT;
		}

		if (Ptr->Flage == READPROCESS) {
			if (Ptr->IsWin10) {
				if (g_ReadProcess.WIN10_ReadProcessMemory(Ptr->Addr, Ptr->Size, OutputData)) {
					Informaiton = RetSize;
					Status = STATUS_SUCCESS;
					goto $EXIT;
				}
				else {
					Status = STATUS_UNSUCCESSFUL;
					goto $EXIT;
				}
			}

			Status = g_ReadProcess.ReadProcessMemory_APC(Ptr->Addr, Ptr->Size, OutputData, 0);
			Informaiton = RetSize;
			goto $EXIT;
		}

		if (Ptr->Flage == WRITEROCESS) {
			g_ReadProcess.WIN10_WriteProcessMemory(Ptr->Addr, Ptr->Size, OutputData);
			Informaiton = RetSize;
			Status = STATUS_SUCCESS;
			goto $EXIT;

			/*Status = g_ReadProcess.ReadProcessMemory_APC(Ptr->Addr, Ptr->Size, OutputData, 1);
			Informaiton = RetSize;
			goto $EXIT;*/
		}

		if (Ptr->Flage == GETDLLBASSE) {
			if (MmIsAddressValid(OutputData)) {

				*(ULONGLONG *)OutputData = g_ReadProcess.IoGetModeuleBaseAddr((char *)Ptr->WriteBufferAddr);
				if (*(ULONGLONG *)OutputData == 0) {
                      Status = STATUS_UNSUCCESSFUL;
				}
				else {
					Status = STATUS_SUCCESS;
				}
				Informaiton = 8;
				
				goto $EXIT;
			}
		}
		if (Ptr->Flage == TP) {
			g_ReadProcess.TpPr((HANDLE)Ptr->Pid);
			Informaiton = 0;
			Status = STATUS_SUCCESS;
			goto $EXIT;
		}
	}


$EXIT:

	Irp->IoStatus.Status = Status;
	Irp->IoStatus.Information = Informaiton;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Status;
}
