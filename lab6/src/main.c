#include <libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// print device parameters
void PrintDeviceParams(libusb_device * device);

int main()
{
    // list of device pointers
    libusb_device ** devices;

    // libusb context session
    libusb_context * context;

    // initialize the libusb library, open a session with libusb
    int res = libusb_init(&context);
    if (res < 0)
    {
        // get error message by code
        fprintf(stderr,
                "%s\n",
                libusb_error_name(res));
        return EXIT_FAILURE;
    }

    // get a list of all found USB devices
    ssize_t device_count = libusb_get_device_list(context,
                                                  &devices);
    if (device_count < 0)
    {
        fprintf(stderr,
                "%s\n",
                libusb_error_name((int)device_count));
        return EXIT_FAILURE;
    }

    printf("Devices found: %zd\n\n", device_count);
    printf("%-20s %-20s %-20s %-20s\n",
           "Device class",
           "Vendor ID",
           "Product ID",
           "Serial number\n");

    for (int i = 0; i < device_count; i++)
    {
        PrintDeviceParams(devices[i]);
    }

    // free the memory allocated when getting the list of devices
    libusb_free_device_list(devices,
                            1);
    // shut down the libusb library
    libusb_exit(context);

    return EXIT_SUCCESS;
}

void PrintDeviceParams(libusb_device * device)
{
    // device descriptor
    struct libusb_device_descriptor descriptor;

    // get device descriptor
    int status = libusb_get_device_descriptor(device,
                                              &descriptor);
    if (status != 0)
    {
        fprintf(stderr,
                "%s\n",
                libusb_error_name(status));
        return;
    }

    // device handle
    struct libusb_device_handle * handle;

    // open device and get device handle
    status = libusb_open(device,
                         &handle);
    if (status != 0)
    {
        fprintf(stderr,
                "%s\n",
                libusb_error_name(status));
        return;
    }

    unsigned char serial_number[256];
    if (handle && descriptor.iSerialNumber)
    {
        // get string descriptor of serial number fields of the device descriptor
        status = libusb_get_string_descriptor_ascii(handle,
                                                    descriptor.iSerialNumber,
                                                    serial_number,
                                                    sizeof(serial_number));
        if (status <= 0) strncpy(serial_number,
                                 "empty",
                                 sizeof(serial_number));
    }
    else strncpy(serial_number,
                 "null",
                 sizeof(serial_number));

    // close device handle
    libusb_close(handle);

    printf("%-20.2x 0x%-18.4x 0x%-18.4x %-20s\n",
           (int)descriptor.bDeviceClass,
           descriptor.idVendor,
           descriptor.idProduct,
           serial_number);
}