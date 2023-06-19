/* *******************************
 * Reviewer: Nofar
 * Author: Viktor Fainshtein
 * File: uid.h
 * ******************************/
#ifndef __UID_H__
#define __UID_H__

#include <time.h>								/*time_t*/
#include <sys/types.h>								/*pid_t size_t*/

typedef struct UID ilrd_uid_t;

extern const ilrd_uid_t g_bad_uid;

ilrd_uid_t UIDGet(void);
/* description: gives the user a UID to use
   params: non
   return value: ilrd_uid_t 
   O(1) */


int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);
/* description: compare two UID's 
   params: two UID's
   return value: 1 if they are the same 0 if not
   undefined behavior:
   O(1) */

ilrd_uid_t UIDGetNull(void);
/* description: initialize a ilrd_uid_t with value 0 
   params: non
   return value: ilrd_uid_t with value 0
   undefined behavior:
   O(n) */

struct UID                                                                                                                                    
{                                                
  size_t count;
  time_t time;
  pid_t pid;
};

#endif
