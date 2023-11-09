#include <sem/sem.h>
#include <stdlib.h>

EXTERN struct proc_assoc_list assoc_list;
EXTERN struct semaphore_list sem_list;

void sem_init()
{
    //Inicia lista de semáforo.
    sem_list.root = malloc(sizeof(struct semaphore));
    sem_list.root.key = 0;
    sem_list.root.value = 0;
    sem_list.root.next = NULL;
    
    sem_list.tail = sem_list.root;
    sem_list.size = 0;
}
