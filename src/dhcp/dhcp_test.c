
#include <stdio.h>
#include "dhcp.h"


int main()
{
    char ip[] = {"192.168.111.0"};
    int mask = 24;
    dhcp_t *dhcp = NULL;
    ip_address_t avilable_ip = 0;
    ip_address_t non_vaiable_ip = 500;

    dhcp = DHCPCreate(ip, mask);

    avilable_ip = DHCPAllocateIp(dhcp);

    printf("%u\t%d\n", avilable_ip, avilable_ip);

    printf("number of free ip addresses: %ld\n", DHCPCountFree(dhcp));

    if(DHCPRenewIP(dhcp ,avilable_ip) == 1)
    {
        printf("RENEW - existing ip was not found\n");
    }
    if(DHCPRenewIP(dhcp ,non_vaiable_ip) == 0)
    {
        printf("RENEW found a non existing ip\n");
    }

    if(DHCPFreeIp(dhcp, avilable_ip) == 0)
    {
        printf("ip was freed\n");
    }

    DHCPDestroy(dhcp);
    dhcp = NULL;

    return 0;
}