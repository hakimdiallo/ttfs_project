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

int tfs_create(int argc, char* argv[]){
	if((argc == 3 || argc == 4) && ( strcmp(argv[1],"-s") == 0 ) ){
		char *name = NULL;
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
			if( close(fd) == -1 ){
				return -1;
			}
		}
	} else {
		printf("Not enough arguments\n");
	}
	return 0;
}

int tfs_partition(int argc, char* argv[]){
	if( argc>2 && ( strcmp(argv[1],"-p") == 0 ) ){
		uint32_t np;
		char *name = NULL;
		if( strcmp(argv[argc-2],"-p") == 0 ){
			if( (argc-1) % 2 != 0 )
				return -1;
			np = (argc-1)/2;
			if( strcpy(name,"disk.tfs") == NULL )
				return -1;
		}
		else {
			if( (argc-2) % 2 != 0 )
				return -1;
		 	np = (argc-2)/2;
		 	if( strcpy(name,"disk.tfs") == NULL )
				return -1;
		}
		int fd;
		if( (fd = open(name, O_APPEND, S_IRWXU)) == -1 )
			return -1;
		if( lseek(fd,sizeof(uint32_t),SEEK_SET) == -1 )
			return -1;
		uint32_t n = htole32(np);
		if( write(fd,(unsigned char *)&n,sizeof(uint32_t)) == -1 )
			return -1;
		uint32_t i = 2;
		while( i < (np * 2) ){
			uint32_t m = htole32((uint32_t)atoi(argv[i]));
			if( write(fd,(unsigned char *)&m,sizeof(uint32_t)) == -1 )
				return -1;
			i+=2;
		}
	} 
	else {
		printf("Not enough arguments\n");
	}
	return 0;
}

int tfs_analyze(int argc, char *argv[]){
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
		printf("Not enough arguments\n");
	}
	return 0;
}
