#include <nanvix/const.h>
#include <sys/sem.h>

/**
 * @brief: Retorna o valor corrente do semáforo
 */
int getval (int semid)
{
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) { 
            if (semtab[i].id == semid) {
                return semtab[i].value;
            }
        }
    }
    return -1;
}

/**
 * @brief: Define o valor do semáforo como sendo val.
 */
int setval (int semid, int val){
    
    // Busca o semáforo com o id informado.
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) 
            if (semtab[i].id == semid) {
                semtab[i].value = val;
                break;
            }
    }
}

/**
 * @brief: Diminui o valor do semáforo e destrói ele se possível
 */
int ipc_rmid (int semid)
{
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) { 
            if (semtab[i].id == semid) {
                return semtab[i].procusing--;
            }
            if (semtab[i].procusing == 0) {
                semtab[i].state = INACTIVE;
            }
        }
    }
}

/**
 * @brief Executa uma série de operações no semáforo
 *        definidas pela variável cmd.
 */
PUBLIC int sys_semctl (int semid, int cmd, int val)
{
    switch (cmd) {
        case GETVAL:
            return getval(semid);
        case SETVAL:
            return setval(semid, val);
        case IPC_RMID:
            return ipc_rmid(semid);
    }
}
