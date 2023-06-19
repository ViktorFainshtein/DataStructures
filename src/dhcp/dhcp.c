/*********************************
 * Reviewer: Shani Horden
 * Author: Viktor Fainshtein
 * File: dhcp.c
 * ******************************/
#include <stdlib.h> /*malloc free*/
#include <math.h>   /*power*/
#include "dhcp.h"

typedef struct dhcp_node dhcp_node_t;

#define MAX_NUM_OF_BITS 32    /*MAX_NUM_OF_BITS - max len of ip address*/

struct dhcp_node
{
    dhcp_node_t *child[2];
    int is_ocupied;
};

struct dhcp
{
    dhcp_node_t *root;
    ip_address_t net_address;
    int host_mask_bits;
};

static dhcp_t *InitDhcp(dhcp_t *dhcp);
static dhcp_node_t *CreateNode(void);
static void TrieDestroy(dhcp_node_t *node);
static int ConvertStringIpToInt(char *net_address);
static int ConvertCharToNum(char digit);
static int IsBothOcupied(dhcp_node_t *node);
static ip_address_t FindFreeIp(dhcp_node_t *node, int level, ip_address_t ip);
size_t RecCount(dhcp_node_t *node, int level);
int FindIp(dhcp_node_t *node, ip_address_t ip, int level);
int FindAndFreeIp(dhcp_node_t *node, ip_address_t ip, int level);
static int IsChildrenExist(dhcp_node_t *node);

/* net_mask is number of ocupied bits in the ip */
dhcp_t *DHCPCreate(const char *net_address, int net_mask)
{
    dhcp_t *dhcp = NULL;
    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));

    if(!dhcp)
    {
        return NULL;
    }

    dhcp->root = CreateNode();
    if(!dhcp->root)
    {
        free(dhcp);
        dhcp = NULL;
        return NULL;
    }

    dhcp->net_address = ConvertStringIpToInt((char *)net_address);
    dhcp->host_mask_bits = MAX_NUM_OF_BITS - net_mask;

    /*set the 3 first addresses that are saved for the system*/
    if(!InitDhcp(dhcp))
    {
        DHCPDestroy(dhcp);
        dhcp = NULL;
        return NULL;
    }

    return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    TrieDestroy(dhcp->root);
    dhcp->root = NULL;
    dhcp->host_mask_bits = 0;
    dhcp->net_address = 0;
    free(dhcp);
    dhcp = NULL;
}

ip_address_t DHCPAllocateIp(dhcp_t *dhcp)
{
    ip_address_t ip = 0;   
    ip = FindFreeIp(dhcp->root, dhcp->host_mask_bits, ip);
    /*returns 255.255.255.255 in case of error*/
    if(ip == (ip_address_t)-1)
    {
        return -1;
    }
    return dhcp->net_address + ip;
}

int DHCPFreeIp(dhcp_t *dhcp, ip_address_t ip)
{
    /*res is the host ip that we allocated to user ip that he passed to function*/
    ip_address_t res = ip - dhcp->net_address;
    return FindAndFreeIp(dhcp->root, res, dhcp->host_mask_bits);
}

int FindAndFreeIp(dhcp_node_t *node, ip_address_t ip, int level)
{
    /*used to calc the return value*/
    int res = 0;
    /*set bit is the index of the current child*/
    int set_bit = (ip >> (level -1))&1;
    if(node == NULL)
    {
        return 1;
    }
    if(level == 0)
    {
        return 0;
    }
    
    res = FindAndFreeIp(node->child[set_bit], ip, level-1);
    /*if current node child exist*/
    if (IsChildrenExist(node) && res == 0)
    {
        node->is_ocupied = 0;
        /*if grand child does not exist remove child node*/
        if(!IsChildrenExist(node->child[set_bit]))
        {
            free(node->child[set_bit]);
            node->child[set_bit] = NULL;
            return res;            
        }
    }
    
    return res;
}

size_t DHCPCountFree(dhcp_t *dhcp)
{
    /*RecCount - counts the number of allocated nodes*/
    /*pow - return the number of max possible nodes that can be allocated*/
    return pow(2,dhcp->host_mask_bits) - RecCount(dhcp->root, dhcp->host_mask_bits);
}

int DHCPRenewIP(dhcp_t *dhcp, ip_address_t ip)
{
    /*res - recive the host ip portion of the user ip*/
    ip_address_t res = ip - dhcp->net_address;
    return FindIp(dhcp->root, res, dhcp->host_mask_bits);
}
/*find the ip for renewal of lease*/
int FindIp(dhcp_node_t *node, ip_address_t ip, int level)
{
    int curr_bit = (ip >> (level -1)) & 1;
    if(node == NULL)
    {
        return 1;
    }
    if(level == 0)
    {
        return 0;
    }

    return FindIp(node->child[curr_bit], ip, level-1);
}

/*-------------------- STATIC FUN AREA --------------------*/

/*
A function to convert a single char number to int - 
didnt implement it with LUT for lower space complexity
*/
static int ConvertCharToNum(char digit)
{
    switch (digit)
    {
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '6':
            return 6;
            break;
        case '7':
            return 7;
            break;
        case '8':
            return 8;
            break;
        case '9':
            return 9;
            break;
        default:
            return -1;
            break;
    }
}
/*convert string ip to integer ip*/
static int ConvertStringIpToInt(char *net_address)
{
    int ip = 0;
    int temp = 0;

    while (*net_address != '\0')
    {
        temp *= 10;
        temp += ConvertCharToNum(*net_address);
        ++net_address;

        if(*net_address == '.')
        {
            ip <<= 8;
            ip |= temp;
            temp = 0;
            ++net_address;
        }
    }
    ip <<= 8;
    
    return ip;
}
/*recursive function - starts removing from the leaf nodes*/
static void TrieDestroy(dhcp_node_t *node)
{
    if(node == NULL)
    {
        return;
    }

    TrieDestroy(node->child[0]);
    TrieDestroy(node->child[1]);

    free(node);
    node = NULL;
}
/*create and initialize a node*/
static dhcp_node_t *CreateNode(void)
{
    dhcp_node_t *new_node = NULL;
    new_node = (dhcp_node_t *)malloc(sizeof(dhcp_node_t));
    if(!new_node)
    {
        return NULL;
    }
    new_node->child[0] = NULL;
    new_node->child[1] = NULL;
    new_node->is_ocupied = 0;
    return new_node;
}
/*initialzie dhcp struct*/
static dhcp_t *InitDhcp(dhcp_t *dhcp)
{
    int i = 0;
    int size = dhcp->host_mask_bits;
    dhcp_node_t *node = dhcp->root;
    /*create route and set address of 0.0.0.0*/
    for(i = 0; i < size; ++i)
    {
        node->child[0] = CreateNode();
        if(!node->child[0])
        {
            return NULL;
        }
        node = node->child[0];
    }

    node->is_ocupied = 1;
    node = dhcp->root;
    /*creat the route up to 255.255.255.254/5*/
    for(i = 0; i < size-1; ++i)
    {
        node->child[1] = CreateNode();
        if(!node->child[1])
        {
            return NULL;
        }
        node = node->child[1];
    }
    node->is_ocupied = 1;

    /*set address of 255.255.255.255*/
    node->child[1] = CreateNode();
    if(!node->child[1])
    {
        return NULL;
    }
    node->child[1]->is_ocupied = 1;

    /*set address of 255.255.255.254*/
    node->child[0] = CreateNode();
    if(!node->child[0])
    {
        return NULL;
    }
    node->child[0]->is_ocupied = 1;

    return dhcp;
}
/*return to user the free host ip that has been allocated*/
static ip_address_t FindFreeIp(dhcp_node_t *node, int level, ip_address_t ip)
{
    int index = 0;
    /*set the index of the correct child*/
    index = (node->child[0] && node->child[0]->is_ocupied);

    if(level == 0)
    {
        node->is_ocupied = 1;
        return ip;
    }
    /*if child exist and is not ocupied*/
    if(node->child[index] && !node->child[index]->is_ocupied)
    {
        ip <<= 1;
        ip |= index;
        ip = FindFreeIp(node->child[index], level-1, ip);
        node->is_ocupied = IsBothOcupied(node);
        return ip;
    }
    /*if child does not exist*/
    if(!node->child[index])
    {
        node->child[index] = CreateNode();
        if(!node->child[index])
        {
            return -1;
        }
        ip <<= 1;
        ip |= index;
        ip = FindFreeIp(node->child[index], level-1, ip);
        node->is_ocupied = IsBothOcupied(node);
        return ip;
    }

    return -1;
}
/*if both children ocupied return 1 - 0 otherwise*/
static int IsBothOcupied(dhcp_node_t *node)
{
    if(node->child[0] && node->child[1])
    {
        if(node->child[0]->is_ocupied && node->child[1]->is_ocupied)
        {
            return 1;
        }
    }
    return 0;
}
/*recursive leaf count*/
size_t RecCount(dhcp_node_t *node, int level)
{
    if(node == NULL)
    {
        return 0;
    }
    if(level == 0)
    {
        return 1;
    }
    return RecCount(node->child[0], level-1) + RecCount(node->child[1], level-1);
}
/*check if child exist*/
static int IsChildrenExist(dhcp_node_t *node)
{
    if((node->child[0] != NULL) || (node->child[1] != NULL))
    {
        return 1;
    }
    return 0;
}