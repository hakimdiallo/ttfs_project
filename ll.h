#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_BLOCK_SIZE 1024

#define NO_ERROR 0
#define ERROR -1

typedef unsigned char block[MAX_BLOCK_SIZE];

typedef int disk_id;

typedef int error;


/************************************************************/
// Fonctions de l'API de manipulation de disque

error start_disk(char *name, disk_id *id); //qui permet de manipuler un disque en lui associant une identité dynamique
error read_block(disk_id id, block b,uint32_t num); //qui permet de lire un bloc sur le disque
error write_block(disk_id id,block b,uint32_t num); //qui permet d’écrire un bloc sur le disque 
error sync_disk(disk_id id); 
error stop_disk(disk_id id); //qui permet de terminer une session de travail sur un disque


/**********************************************************/
// Commandes de l'API
uint32_t little_endian_to_u32(uint32_t a);
int tfs_create(int argc, char* argv[]);
int tfs_partition(int argc, char* argv[]);
int tfs_analyze(int argc, char *argv[]);
