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
                if (check_valid(&semtab[i]) == -1) return -1;

                return semtab[i].value;
            }
        }
    }
    return -1;
}

/**
 * @brief: Define o valor do semáforo como sendo val.
 */
int setval (int semid, int val)
{
    // Busca o semáforo com o id informado.
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) 
            if (semtab[i].id == semid) {
                if (check_valid(&semtab[i]) == -1) return -1;
                semtab[i].value = val;
                return 0;
            }
    }

    return -1;
}

/**
 * @brief: Diminui o valor da variável procusing e destrói o semáforo caso o valor resultante
 *         seja 0.
 */
int ipc_rmid (int semid)
{
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) { 
            if (semtab[i].id == semid) {

                if (check_valid(&semtab[i]) == -1) return -1;

                struct semaphore *sem = &semtab[i]; /* Cria um ponteiro para o semáforo */
                int table = sem->pos / 16; /* Encontra em qual tabela o semáforo está */
                int pos_table = sem->pos % 16; /* Descobre a posição do semáforo na tabela */
                int comp = 1;
    
                comp = comp << pos_table; /* Posiciona o valor 1 no bit que será alterado */

                int *b = &curr_proc->shared_sem[table]; /* Pega a tabela que o semáforo está */

                *b = *b & (~comp); /* Atribui o valor da tabela a operação de set bit*/ 

                sem->procusing--;

                if (sem->procusing == 0) {
                    sem->state = INACTIVE;
                    return 0;
                }
                return 0;
            }
        }
    }

    return -1;
}

/**
 * @brief Executa uma série de operações no semáforo
 *        definidas pela variável cmd.
 */
PUBLIC int sys_semctl (int semid, int cmd, int val)
{
    // Verifica se o processo atual pode realizar operações no semáforo.

    switch (cmd) {
        case GETVAL:
            return getval(semid);
        case SETVAL:
            return setval(semid, val);
        case IPC_RMID:
            return ipc_rmid(semid);
    }

    return -1;
}
