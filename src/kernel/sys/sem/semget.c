#include <nanvix/const.h>
#include <sys/sem.h>

/**
 *  @brief Cria um novo semáforo.
 */
int create_semaphore(unsigned key)
{
    struct semaphore *newsem = NULL;

    for (int i = 0; i < SEM_MAX; i++){
        if (semtab[i].state == INACTIVE){
            newsem = &semtab[i];
            break;
        }
    }

    if (newsem == NULL)
        return -1;
    
    newsem->key = key;
    newsem->value = 1;
    newsem->state = ACTIVE;
    newsem->procpriority = 0;
    newsem->procusing = 0;
    
    associate_semaphore(newsem);

    return newsem->id;
}

/**
 *  @brief Associa o processo a corrente de processos
 *  do semáforo.
 */
int associate_semaphore (struct semaphore *sem)
{
    int table = sem->pos / 16; /* Encontra em qual tabela o semáforo está */
    int pos_table = sem->pos % 16; /* Descobre a posição do semáforo na tabela */
    int comp = 1;

    comp << pos_table; /* Posiciona o valor 1 no bit que será alterado */

    int *b = &curr_proc->shared_sem[table]; /* Pega a tabela que o semáforo está */

    *b = b | comp /* Atribui o valor da tabela a operação de set bit */ 

    sem->procusing++;
 
    return sem->id;
}

/**
 * @brief Cria e/ou retorna o key de um semáforo ativo.
 */
PUBLIC int sys_semget(sem_t key)
{   
    // Busca o semáforo com o key informado.
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) 
            if (semtab[i].key == key){
                return associate_semaphore(&semtab[i]);
            }
    }

    // Cria um semáforo.
    return create_semaphore(key);
}
