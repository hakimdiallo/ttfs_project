#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <endian.h>
#include "ll.h"
  
uint32_t little_endian_to_u32(uint32_t a)
{
  uint8_t l[4];
  
  *(uint32_t *) l = a;
 
  return 256*256*256*l[3] + 256*256*l[2] + 256*l[1] + l[0];
}

int main(int argc, char *argv[]){
	if( argc == 1 || argc == 2 ){
		char *name = NULL;
		if( argc == 2 ){
			if( strcpy(name,argv[1]) == NULL ){
				return -1;
			}
		}
		else {
			if( strcpy(name,"disk.tfs") == NULL ){
				return -1;
			}
		}
		int fd;
		if( (fd = open(name,O_RDONLY,S_IRWXU)) == -1 )
			return -1;
		unsigned char *tmp = NULL;
		while( read(fd,tmp,sizeof(uint32_t)) == 0 ){
			printf("%d\n", little_endian_to_u32(*tmp));
		}
		if( close(fd) == -1 )
			return -1;
	} 
	else {
		printf("Invalid command:\ntfs_analyze [name]\n");
	}
	return 0;
}
