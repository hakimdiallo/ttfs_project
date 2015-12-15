#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <endian.h>
#include "ll.h"


error read_physical_block(disk_id id,block b,uint32_t num){
	if( id != -1){
		unsigned char buf[MAX_BLOCK_SIZE];
		if( lseek(id,MAX_BLOCK_SIZE*num,SEEK_SET) == -1 ){
			return -1;
		}
		if( read(id,buf,MAX_BLOCK_SIZE) == -1 ){
			return -1;
		}
		if( memcpy(b,buf,MAX_BLOCK_SIZE) == NULL ){
			return -1;
		}
		return 0;
	}
	return -1;
}

error write_physical_block(disk_id id,block b,uint32_t num){
	if( id != -1){
		if( lseek(id,MAX_BLOCK_SIZE*num,SEEK_SET) == -1 ){
			return -1;
		}

		if( write(id,b,MAX_BLOCK_SIZE) == -1 ){
			return -1;
		}
		return 0;
	}
	return -1;
}

/************** Fontions de manipulation visibles par les couches superieurs **************************/

error start_disk(char *name,disk_id *id){
	if( ( *id = open(name,O_RDWR,S_IRWXU) ) == -1 ){
		perror("Error");
		return -1;
	}
	return 0;
}

error read_block(disk_id id,block b,uint32_t num){
	return read_physical_block(id,b,num);
}

error write_block(disk_id id,block b,uint32_t num){
	return write_physical_block(id,b,num);
}

error sync_disk(disk_id id){
	return 0;
}

error stop_disk(disk_id id){
	return close(id);
}

