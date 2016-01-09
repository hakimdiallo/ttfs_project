#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>


int tfs_mkdir(const char *path, mode_t mode){
	return mkdir(path,mode);
}

int tfs_rmdir(const char *path){
	return rmdir(path);
}

int tfs_rename(const char *old, const char *new){
	return rename(old,new);
}

int tfs_open(const char *name,int oflag, ...);

ssize_t tfs_read(int fildes,void *buf,size_t nbytes);

ssize_t tfs_write(int fildes,void *buf,size_t nbytes);

int tfs_close(int fildes){
	if(close(fildes) == -1)
		return 1;
	return 0;
}

off_t tfs_lseek(int fildes,off_t offset,int whence);

DIR *opendir(const char *filename);

struct dirent *readdir(DIR *dirp);
void rewinddir(DIR *dirp);
int closedir(DIR *dirp);

