#include <sys/sem.h>

PUBLIC struct semaphore semtab[SEM_MAX];

void sem_init()
{
    // Inicializa a tabela de semáforos.
    for (int i=0; i<SEM_MAX; i++) {
        semtab[i].state = INACTIVE;
        semtab[i].id = i;
    }
}

