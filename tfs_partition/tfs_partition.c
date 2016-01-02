#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <endian.h>
#include <errno.h>
#include "tfs_partition.h"

int main(int argc, char* argv[]){
	if( argc>2 && ( strcmp(argv[1],"-p") == 0 ) ){
		uint32_t np;
		char name[255];
		if( strcmp(argv[argc-2],"-p") == 0 ){
			if( (argc-1) % 2 != 0 )
				return -1;
			np = (argc-1)/2;
			if( strcpy(name,"disk.tfs") == NULL ){
				perror("");
				return -1;
			}
		}
		else {
			if( (argc-2) % 2 != 0 )
				return -1;
		 	np = (argc-2)/2;
		 	if( strcpy(name,"disk.tfs") == NULL ){
		 		perror("");
				return -1;
			}
		}
		int fd;
		printf("File name: %s\n",name);
		if( (fd = open(name, O_WRONLY, S_IRWXU)) == -1 ){
			perror("Error File name: ");
			return -1;
		}
		printf("1\n");
		if( lseek(fd,sizeof(uint32_t),SEEK_SET) == -1 ){
			perror("lseek: ");
			return -1;
		}
		printf("%d\n",fd);
		uint32_t n = htole32(np);
		if( write(fd,(unsigned char *)&n,sizeof(uint32_t)) == -1 ){
			perror("Error write ");
			return -1;
		}
		uint32_t i = 2;
		while( i <= (np * 2) ){
			uint32_t m = htole32((uint32_t)atoi(argv[i]));
			if( write(fd,(unsigned char *)&m,sizeof(uint32_t)) == -1 ){
				perror("");
				return -1;
			}
			i+=2;
		}
	} 
	else {
		printf("Invalid command:\ntfs_partition -p size [-p size]... [name]\n");
	}
	return 0;
}
