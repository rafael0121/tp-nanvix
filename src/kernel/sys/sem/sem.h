#ifdef SEM_H_
#define SEM_H_

    EXTERN int sys_semget(unsigned key);
    EXTERN int sys_semop(int semid, int semop);
    EXTERN int sys_semctl(int semid, int cmd, int val);

#endif
