

#define MAX_BLOCK_SIZE 1024

#define NO_ERROR 0
#define ERROR -1


typedef struct {
	uint32_t id;
	
} block;

typedef struct {
	int fd;
	char *name;
	block *blocks;
	uint32_t nbblocks;
} disk_id;

typedef struct {
	int err = ERROR;
} error;


/************************************************************/
// Fonctions de l'API de manipulation de disque

error start_disk(char *name,disk_id *id); //qui permet de manipuler un disque en lui associant une identité dynamique
error read_block(disk_id id,block b,uint32_t num); //qui permet de lire un bloc sur le disque
error write_block(disk_id id,block b,uint32_t num); //qui permet d’écrire un bloc sur le disque 
error sync_disk(disk_id id); 
error stop_disk(disk_id id); //qui permet de terminer une session de travail sur un disque


/**********************************************************/
// Commandes de l'API
int tfs_create(int size, char *name);
