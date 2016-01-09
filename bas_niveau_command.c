#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <endian.h>
#include "ll.h"
  

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
		
		int nb_blocks = atoi(argv[2]);
		if( nb_blocks <= 0 ){
			printf("Invalid size of disk.\n");
			return -1;
		}
		
		disk_id fd;
		if( (fd = open(strcat(name,".tfs"), O_WRONLY|O_CREAT, S_IRWXU)) == -1 ){
			perror("Error");
			return -1;
		}
		block b;
		int i;
		
		b[0] = (uint32_t)nb_blocks;
		for(i=1; i<BLOCK_LENGTH-1; i++){
			b[i] = 0;
		}
		
		for(i=0; i<nb_blocks; i++){
			if( write_block(fd,b,i) == -1 ){
				return -1;
			}
			if(i==0)
				b[0] = 0;			
		}
		
			
		if( close(fd) == -1 ){
			return -1;
		}
	} else {
		printf("Invalid command: tfs_create -s size [name]\n");
	}
	return -1;
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
		 	if( strcpy(name,argv[argc-1]) == NULL ){
		 		perror("");
				return -1;
			}
		}
		disk_id fd;
		if( start_disk(name,&fd) == -1 ){
			perror(" ");
			return -1;
		}
		
		block b;
		if( read_block(fd,b,0) == -1 )
			return -1;

		int i;
		if( b[1] != 0 ){
			for(i=2; i<=b[1]; i++)
				b[i] = 0;
		}
		
		int sum = 0;
		b[1] = np;
		int k = 2;
		for(i=2; i <= (np * 2); i+=2){
			int nbp = atoi(argv[i]);
			if( nbp <= 0 ){
				printf("Error negative or null partition\n");
				return -1;
			}
			b[k++] = ((uint32_t)nbp);
			sum += nbp;
		}
		
		if( sum > b[0] ){
			printf("Invalid size of partitions\n");
			return -1;
		}
		
		if( write_block(fd,b,0) == -1 )
			return -1;
			
		if( stop_disk(fd) == -1 )
			return -1;
	} 
	else {
		printf("Invalid command: tfs_partition -p size [-p size]... [name]\n");
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
		disk_id fd;
		if( start_disk(name,&fd) == -1 ){
			perror("");
			return -1;
		}
		
		block b;
		if(read_block(fd,b,0) == -1)
			return -1;
		
		printf("Nombre de block: %d\n",b[0]);
		uint32_t n = b[1];
		if(n == 0){
			printf("Nombre de partition: %d\n",n);
		} 
		else {
			printf("Nombre de partition: %d\n",n);
			int i;
			for(i=2; i<=n+1; i++){
				printf("Partition %d taille: %d\n",i-1,b[i]);
			}
		}
		
		if( stop_disk(fd) == -1 )
			perror("");
			return -1;
	} 
	else {
		printf("Invalid command: tfs_analyze [name]\n");
	}
	return 0;
}
