#include <stdio.h>
#include "uid.h"





int main()
{
	ilrd_uid_t id = UIDGet();
	ilrd_uid_t null_id = UIDGetNull();
	
	ilrd_uid_t id1 = UIDGet();
	ilrd_uid_t id2 = UIDGet();
	ilrd_uid_t id3 = UIDGet();
	
	printf("%ld\n", id.count);
	printf("%s\n", ctime(&id.time));
	printf("%d\n", id.pid);
	
	printf("%ld\n", id1.count);
	printf("%ld\n", id1.time);
	printf("%d\n", id1.pid);
	printf("%ld\n", id2.count);
	printf("%ld\n", id2.time);
	printf("%d\n", id2.pid);
	printf("%ld\n", id3.count);
	printf("%ld\n", id3.time);
	printf("%d\n", id3.pid);
	
	printf("%ld\n", null_id.count);
	printf("%ld\n", null_id.time);
	printf("%d\n", null_id.pid);
	
	printf("is same: %d\n", UIDIsSame(id, null_id));
		
	return 0;
}
