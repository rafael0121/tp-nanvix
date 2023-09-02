#include <nanvix/pm.h>

/*
 * @brief Função de sistema, procura se o processo como o PID informado existe e chama a função do_get_process_info
 * @param pid Identificador do processo
 * @param buf Ponteiro para struct com informações do processo
 * @returns 0 para processo encontrado e -1 para não encontrado
*/

int sys_get_process_info(pid_t pid, struct process_buf *buf)
{	
	struct process *proc; 
	


	for (proc = FIRST_PROC-1; proc <= LAST_PROC; proc++)
  {
		if (pid == proc->pid)
    {
			do_get_process_info(proc, buf);	
			return 0;
		}
	}

	return -1;
}
