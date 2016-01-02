#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <endian.h>
#include "tfs_create.h"

int main(int argc, char* argv[]){
	if((argc == 3 || argc == 4) && ( strcmp(argv[1],"-s") == 0 ) ){
		char name[255];
		if(argc == 3){
			if(strcpy(name,"disk") == NULL){
				perror("Error");
				return -1;
			}
		} 
		else {
			if(strcpy(name,argv[3]) == NULL){
				perror("Error");
				return -1;
			}
		}
		int fd;
		if( (fd = open(strcat(name,".tfs"), O_WRONLY|O_CREAT, S_IRWXU)) == -1 ){
			perror("Error");
			return -1;
		}
		else {
			uint32_t n = htole32((uint32_t)atoi(argv[2]));
			if( write(fd,(unsigned char *)&n,sizeof(uint32_t)) == -1 ){
				return -1;
			}
			uint32_t i;
			n = htole32(0);
			for(i=0;i<(MAX_BLOCK_SIZE/4)-1;++i){
				if( write(fd,(unsigned char *)&n,sizeof(uint32_t)) == -1 ){
					return -1;
				}
			}
			if( close(fd) == -1 ){
				return -1;
			}
		}
	} else {
		printf("Invalid command:\ntfs_create -p size [name]\n");
	}
	return 0;
}
