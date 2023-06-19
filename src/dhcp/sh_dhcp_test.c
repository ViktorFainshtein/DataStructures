/*********************************
 * Reviewer:  
 * Author: shani horden
 * File Name: dhcp.h
 * ******************************/
#include <stdio.h>
#include<assert.h>
#include "dhcp.h"

void TestAllocFull();
void TestAll();

int main()
{
    
    TestAll();
    TestAllocFull();


    return 0;
}

void TestAllocFull()
{
    dhcp_t *dhcp = NULL;
    int i = 0;
    dhcp = DHCPCreate("192.000.000.000", 24);

    while(DHCPCountFree(dhcp))
    {
        ++i;
        assert(-1 != (int)DHCPAllocateIp(dhcp));
    }

    assert(253 == i);
    assert(-1 == (int)DHCPAllocateIp(dhcp));

    assert(0 == DHCPFreeIp(dhcp, 3221225476));

    assert(1 == DHCPCountFree(dhcp));

    assert(3221225476 == DHCPAllocateIp(dhcp));

    DHCPDestroy(dhcp);

}


void TestAll()
{
    dhcp_t *dhcp = NULL;
    ip_address_t first = 0, second = 0, third = 0;

    dhcp = DHCPCreate("192.000.000.000", 24);


    /* 11000000000000000000000000000001 */
    first = DHCPAllocateIp(dhcp);
    assert(3221225473 == first);

    /*11000000000000000000000000000010*/
    second = DHCPAllocateIp(dhcp);
    assert(3221225474 == second);

    /* 11000000000000000000000000000011 */
    third = DHCPAllocateIp(dhcp);
    assert(3221225475 == third);

    assert(0 == DHCPFreeIp(dhcp, second));
    assert(second == DHCPAllocateIp(dhcp));

    assert(1 == DHCPFreeIp(dhcp, 3221225476));

    assert(250 == DHCPCountFree(dhcp));


    assert(0 == DHCPRenewIP(dhcp, first));
    assert(1 == DHCPRenewIP(dhcp, 3221225476));

    DHCPDestroy(dhcp);
}