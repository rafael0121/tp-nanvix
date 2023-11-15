#include <nanvix/const.h>
#include <sys/sem.h>

<<<<<<< HEAD
int up (int semid)
{

    
}

int down (int semid)
{


}

PUBLIC int sys_semop(int semid, int op){

    if(op > 0)
        return up(semid);       
    
    if(op < 0)
        return down(semid);
    
    return -1;
}
