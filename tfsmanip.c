#include <stdio.h>
#include <stdlib.h>
#include "ll.h"


error read_physical_block(disk_id id,block b,uint32_t num){
	error e;
	if( id != NULL){
		uint32_t i;
		for(i=0; i<id.nbblocks; i++){
			if( i == num ){
				b = id.blocks[i];
				e.err = NO_ERROR;
				break;
			}
		}
	}
	return e;
}

error write_physical_block(disk_id id,block b,uint32_t num){
	error e;
	if( id != NULL){
		uint32_t i;
		for(i=0; i<id.nbblocks; i++){
			if( i == num ){
				id.blocks[i] = b;
				e.err = NO_ERROR;
				break;
			}
		}
	}
	return e;
}

error start_disk(char *name,disk_id *id){
	error e;
	if( ( id->fd = open(name,O_RDWR,S_IRWXU) ) == -1 ){
		perror("Error");
	}else {
		// lire le fichier et mettre à jour le nombre de blocs id->nbblocks
		if(/*read(fd) get the number of blocks wrong?*/){
		
		}else {
			//lire pour parcourir les blocks ....
		}
	}
	return e;
}

error read_block(disk_id id,block b,uint32_t num){
	return read_physical_block(id,b,num);
}

error write_block(disk_id id,block b,uint32_t num){
	return write_physical_block(id,b,num);
}

error sync_disk(disk_id id){
	error e;
	return e;
}

error stop_disk(disk_id id){
	error e;
	if(close(id.id) == 0)
		e.err = NO_ERROR;
	return e;
}
