#include <nanvix/const.h>
#include <sys/sem.h>


/**
 *  @brief Cria um novo semáforo.
 */
int create_semaphore(key){
    
    // Cria um novo semáforo. 
    struct semaphore *new_sem = malloc(sizeof(struct semaphore));

    // Inicializa as variáveis do novo semáforo.
    new_sem->key = key;
    new_sem->value = 1;
    new_sem->assoc_list.root->proc;
    new_sem->assoc_list.root->next;
    new_sem->next = NULL;
    
    // Adiciona o semáforo no final da lista encadeada.
    sem_list.tail->next = new_sem;
    sem_list.tail = new_sem;
    size++;
    
    //Chama a função para associar o processo atual ao semáforo.
    associate_semaphore(new_sem);

    return 0;
}

/**
 *  @brief Associa um processo a um semáforo.
 */
int associate_semaphore(struct semaphore *sem){
    
    // Criação de um ponteiro auxiliar.
    struct node_proc *ptr = sem.assoc_list.root;
    
    // Busca se o processo atual já está associado ao semáforo.
    while (ptr!=NULL) {
        if (ptr == curr_proc) {
            return 0;
        }
        ptr = ptr->next;
    }
    
    /* Associa o processo atual ao semáforo. */

    // Cria e inicializa novo nó da fila de processos associados.
    struct node_proc *new = malloc(sizeof(node_proc));
    new->proc = curr_proc;
    new->next == NULL;

    // Associa o novo nó ao final da fila de processos associados.
    ptr = sem.assoc_list.tail;
    sem.assoc_list.tail = new;
    ptr->next = new;
    
}

/**
 * @brief Cria ou associa um processo a um semáforo.
 */
PUBLIC int sys_semget(sem_t key)
{   
    // Criação de um ponteiro auxiliar.
    struct semaphore *sem = sem_list.root;
    
    // Verifica se já existe um processo com essa key.
    while(sem != NULL){
        if(sem->key == key){
            associate_semaphore(sem);
            return 0;
        }
        sem = sem->next;
    }
    
    create_semaphore(key);
    
    return 0;
}
