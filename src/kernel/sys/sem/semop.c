#include <nanvix/const.h>
#include <sys/sem.h>


PUBLIC int sys_semop(int semid, int semop){

    struct semaphore *sem = NULL;

    // Busca o semáforo com o id informado.
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) 
            if (semtab[i].id == semid) {
                sem = &semtab[i];
                break;
            }
    }

    if(sem == NULL) {
        return -1;
    } 

}
