#include <sys/sem.h>

PUBLIC struct semaphore semtab[SEM_MAX];

void sem_init()
{
    // Inicializa a tabela de semáforos.
    for (int i=0; i<SEM_MAX; i++) {
        semtab[i].state = INACTIVE;
        semtab[i].procusing = 0;
        semtab[i].id = i;
        semtab[i].pos = i;
    }
}

/**
 *  @brief Verifica se o processo está associado ao
 *  semáforo.
 */
int check_valid (semaphore *sem)
{
    int table = sem->pos / 16;
    int pos_table = sem->pos % 16;
    int comp = 1;
    
    comp << pos_table;

    int b = curr_proc->shared_sem[table];
    
    int result = b & comp;
    if (result == 0)
        return -1;

    return 0;
}
