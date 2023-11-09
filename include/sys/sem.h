/*
 * Copyright(C) 2011-2016 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * This file is part of Nanvix.
 *
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SEM_H_
#define SEM_H_
    
    #include <nanvix/const.h>
    #include <nanvix/pm.h>

	/**
	 * @brief Comand values for semaphores.
	 */

    #define sem_t unsigned

	/**@{*/
	#define GETVAL   0 /**< Returns the value of a semaphore. */
	#define SETVAL   1 /**< Sets the value of a semaphore.    */
	#define IPC_RMID 3 /**< Destroys a semaphore.            */
	/**@}*/

	/* Forward definitions. */
	extern int semget(unsigned);
	extern int semctl(int, int, int);
	extern int semop(int, int);

    //Lista de processos associados ao semáfaro
    struct node_proc{
        struct process *proc;
        struct node_proc *next;
    };

    struct proc_assoc_list{
        struct node_proc *root;
        struct node_proc *tail;
        unsigned size;
    };
    
    // Estrutura do semáfaro 
    struct semaphore{
        sem_t key; /* ID do semáforo. */
        int value; /* Valor do semáforo */
        struct proc_assoc_list assoc_list; /* Lista de processos associados*/ 
        struct sem *next; /* Próximo semáforo na lista encadeada */
    };

    // Estrutura da lista.
    struct semaphore_list{
        struct semaphore *root; /*Ponteiro para o primeiro samáforo na lista*/
        struct semaphore *tail; /* Ponteiro para o último semáforo na lista */
        unsigned size; /* Tamanho da lista */
    };
    // Declaração da lista de semafóros.
    EXTERN struct semaphore_list sem_list;  

    // Declaração da função que inicializa o semáforo.
    EXTERN void sem_init();

#endif /* SEM_H_ */
