#include <nanvix/const.h>
#include <sys/sem.h>

int create_semaphore(key){

    struct semaphore *new_sem = malloc(sizeof(struct semaphore));

    new_sem->key = key;
    new_sem->value = 1;
    new_sem->assoc_list.root->proc;
    new_sem->assoc_list.root->next;
    new_sem->next = NULL;

    sem_list.tail->next = new_sem;
    sem_list.tail = new_sem;
    size++;
}

int associate_semaphore(struct semaphore *sem){
    struct node_proc *ptr = sem.assoc_list.root;
    
    while (ptr!=NULL) {
        if (ptr == curr_proc) {
            return 0;
        }
        ptr = ptr->next;
    }
    
    struct node_proc *new = malloc(sizeof(node_proc));
    new->proc = curr_proc;
    new->next == NULL;

    ptr = sem.assoc_list.tail;
    sem.assoc_list.tail = new;
    ptr->next = new;
    
}

PUBLIC int sys_semget(sem_t key)
{   
    struct semaphore *sem = sem_list.root;
    
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
