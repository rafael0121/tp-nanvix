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
            newsem = semtab[i];
            break;
        }
    }

    if (newsem == NULL)
        return -1;
    
    newsem.key = key;
    newsem.value = 1;
    newsem.state = ACTIVE;

    return newsem.id;
}

/**
 * @brief Cria e/ou retorna o key de um semáforo ativo.
 */
PUBLIC int sys_semget(sem_t key)
{   
    // Busca o semáforo com o key informado.
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE){ 
            if (semtab[i].key == key)
                return key;
    }

    // Cria um semáforo.
    return create_semaphore(key);
}
