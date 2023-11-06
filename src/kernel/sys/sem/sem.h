#ifdef SEM_H_
#define SEM_H_
   	
    #define GETVAL   0 /**< Returns the value of a semaphore. */
	#define SETVAL   1 /**< Sets the value of a semaphore.    */
	#define IPC_RMID 3 /**< Destroys a semaphore.            */

    EXTERN int sys_semget(unsigned key);
    EXTERN int sys_semop(int semid, int semop);
    EXTERN int sys_semctl(int semid, int cmd, int val);

#endif
