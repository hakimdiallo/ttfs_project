#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <endian.h>
#include "ll.h"
  
//============= Tranforme un uint32 little endian en uint32 normal ===========================
// 
uint32_t little_endian_to_u32(uint32_t a)
{
  uint8_t l[4];
  
  *(uint32_t *) l = a;
 
  return 256*256*256*l[3] + 256*256*l[2] + 256*l[1] + l[0];
}

//============== Cree une un disque avec un le nombre de bloc donne ==========================
//
int tfs_create(int argc, char* argv[]){
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

//======== partitionne un disque ne nombre de partion donne avec pour chacun sa taille =============
//
int tfs_partition(int argc, char* argv[]){
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

//==== Analyse un disque en donnant son nombre de bloc et le nombre de patition et pour chaque partition sa taille ===========
//
int tfs_analyse(int argc, char *argv[]){
	if( argc == 1 || argc == 2 ){
		char name[255];
		if( argc == 2 ){
			if( strcpy(name,argv[1]) == NULL ){
				perror("");
				return -1;
			}
		}
		else {
			if( strcpy(name,"disk.tfs") == NULL ){
				perror("");
				return -1;
			}
		}
		int fd;
		if( (fd = open(name,O_RDONLY,S_IRWXU)) == -1 ){
			perror("");
			return -1;
		}
		unsigned char tmp[255];
		printf("1111\n");
		while( read(fd,tmp,sizeof(uint32_t)) == 0 ){
			printf("1111\n");
			printf("%d\n", little_endian_to_u32(*tmp));
		}
		printf("ssssss %s",tmp);
		if( close(fd) == -1 )
			perror("");
			return -1;
	} 
	else {
		printf("Invalid command:\ntfs_analyze [name]\n");
	}
	return 0;
}
