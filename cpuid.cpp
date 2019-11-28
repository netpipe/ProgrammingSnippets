//CPU serial number
#include <stdio.h>

void getPSN(char *PSN)
{
int varEAX, varEBX, varECX, varEDX;
char str[9];
//%eax=1 gives most significant 32 bits in eax 
__asm__ __volatile__ ("cpuid": "=a" (varEAX), "=b" (varEBX), "=c" (varECX), "=d" (varEDX) : "a" (1));
sprintf(str, "%08X", varEAX); //i.e. XXXX-XXXX-xxxx-xxxx-xxxx-xxxx
sprintf(PSN, "%C%C%C%C-%C%C%C%C", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
//%eax=3 gives least significant 64 bits in edx and ecx [if PN is enabled]
__asm__ __volatile__ ("cpuid": "=a" (varEAX), "=b" (varEBX), "=c" (varECX), "=d" (varEDX) : "a" (3));
sprintf(str, "%08X", varEDX); //i.e. xxxx-xxxx-XXXX-XXXX-xxxx-xxxx
sprintf(PSN, "%s-%C%C%C%C-%C%C%C%C", PSN, str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
sprintf(str, "%08X", varECX); //i.e. xxxx-xxxx-xxxx-xxxx-XXXX-XXXX
sprintf(PSN, "%s-%C%C%C%C-%C%C%C%C", PSN, str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
}

int main()
{
char PSN[30]; //24 Hex digits, 5 '-' separators, and a '\0'
getPSN(PSN);
printf("%s\n", PSN); //compare with: lshw | grep serial:
return 0;
}




//https://stackoverflow.com/questions/24049367/how-do-i-get-the-disk-drive-serial-number-in-c-c
//static struct hd_driveid hd;
//int fd;
//
//if ((fd = open("/dev/hda", O_RDONLY | O_NONBLOCK)) < 0) {
//    printf("ERROR opening /dev/hda\n");
//    exit(1);
//}
//
//if (!ioctl(fd, HDIO_GET_IDENTITY, &hd)) {
//    printf("%.20s\n", hd.serial_no);
//} else if (errno == -ENOMSG) {
//    printf("No serial number available\n");
//} else {
//    perror("ERROR: HDIO_GET_IDENTITY");
//    exit(1);
//}
//For Windows:
//system("wmic path win32_physicalmedia get SerialNumber");
//Without using system (Based on Getting WMI Data ):
//hres = pSvc->ExecQuery(
//    bstr_t("WQL"),
//    bstr_t("SELECT SerialNumber FROM Win32_PhysicalMedia"),
//    WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
//    NULL,
//    &pEnumerator);
//hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
