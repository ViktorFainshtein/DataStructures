/* *******************************
 * Reviewer: Nofar
 * Author: Viktor Fainshtein
 * File: uid.c
 * ******************************/
#include <unistd.h>								/*getpid*/
#include "uid.h"

const ilrd_uid_t g_bad_uid = {-1,-1,-1};

ilrd_uid_t UIDGet(void)
{
	static size_t counter = 0;
	ilrd_uid_t id = UIDGetNull();
	id.count = counter;
	time(&(id.time));
	id.pid = getpid();
	
	counter++;
	
	return id;
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return ((uid1.count == uid2.count) && (uid1.pid == uid2.pid) && (uid1.time == uid2.time));
}

ilrd_uid_t UIDGetNull(void)
{
	ilrd_uid_t id = {0,0,0};
	return id;
}
