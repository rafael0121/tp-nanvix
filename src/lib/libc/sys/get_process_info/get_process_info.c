#include <nanvix/syscall.h>
#include <nanvix/pm.h>
#include <errno.h>

int get_process_info(pid_t pid, struct process_buf *buf)
{
	int ret;

	__asm__ volatile
	(
		"int $0x80"
		: "=a" (ret)
		: "0" (NR_getinfo),
		  "b" (pid),
		  "c" (buf) 
	);

	if (ret < 0)
	{
		errno = -ret;
		return -1;
	}
	
	return(ret);
}
