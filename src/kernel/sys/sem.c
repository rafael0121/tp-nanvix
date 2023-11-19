#include <sys/sem.h>

PUBLIC struct semaphore semtab[SEM_MAX];

void sem_init()
{
    // Inicializa a tabela de semáforos.
    for (int i=0; i<SEM_MAX; i++) {
        semtab[i].state = INACTIVE;
        semtab[i].procusing = 0;
        semtab[i].pos = i;
        semtab[i].id = i;
    }
    int table_num = SEM_MAX / 16;
    for(int i = 0; i < table_num; i++)
        curr_proc->shared_sem[i] = 0;
}

/**
 *  @brief Verifica se o processo está associado ao
 *  semáforo.
 */
int check_valid (struct semaphore *sem)
{
    int table = sem->pos / 16;
    int pos_table = sem->pos % 16;
    int comp = 1;
    
    comp = comp << pos_table;

    int *b = &curr_proc->shared_sem[table];
    
    comp = *b & comp;

    if (comp == 0){
        return -1;
    }

    return 0;
}

