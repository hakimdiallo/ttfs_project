#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <endian.h>
#include "ll.h"


int tfs_create(uint32_t size, char* name){
	if(name == NULL){
		if(strcp(name,"disk") == NULL)
			perror("Error");
	}
	int fd;
	if( (fd = open(strcat(name,".tfs"), O_WRONLY|O_CREAT, S_IRWXU)) == -1 ){
		perror("Error");
	}
	else {
		
	}
	
	return 0;
}
