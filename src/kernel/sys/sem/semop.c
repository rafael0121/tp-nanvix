#include <nanvix/const.h>
#include <sys/sem.h>

int up (int semid)
{   
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) { 
            if (semtab[i].id == semid) {
                if(check_valid(&semtab[i]) == -1) return -1;

                if (semtab[semid].value == 0)
                    wakeup(curr_proc->chain);
                
                semtab[i].value++;

                
                return 0;
            }
        }
    } 
    return -1;
}

int down (int semid)
{
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) { 
            if (semtab[i].id == semid) {
                if(check_valid(&semtab[i]) == -1){
                    return -1;
                }
                while (semtab[i].value == 0) {
                    sleep(curr_proc->chain, curr_proc->priority);
                }

                semtab[i].value--;
                
                return 0;
            }
        }
    }
    return -1;
}

PUBLIC int sys_semop(int semid, int op){

    if (op > 0)
        return up(semid);       
    
    if (op < 0)
        return down(semid);
    
    return -1;
}
