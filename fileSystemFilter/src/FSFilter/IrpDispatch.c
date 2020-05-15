#include "FsFilter.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// PassThrough IRP Handler

NTSTATUS FsFilterDispatchPassThrough(
    __in PDEVICE_OBJECT DeviceObject, 
    __in PIRP           Irp
    )
{
    PFSFILTER_DEVICE_EXTENSION pDevExt = (PFSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;

    IoSkipCurrentIrpStackLocation(Irp);
    return IoCallDriver(pDevExt->AttachedToDeviceObject, Irp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// IRP_MJ_CREATE IRP Handler

NTSTATUS FsFilterDispatchCreate(
    __in PDEVICE_OBJECT DeviceObject,
    __in PIRP           Irp
    )
{
    PFILE_OBJECT pFileObject = IoGetCurrentIrpStackLocation(Irp)->FileObject;

    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[FsFilter]: %wZ\n", &pFileObject->FileName);
    DbgPrint("[FsFilter]: %wZ\n", &pFileObject->FileName);
    
    return FsFilterDispatchPassThrough(DeviceObject, Irp);
}