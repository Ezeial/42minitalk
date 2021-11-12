#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "libft.h"

#define SEND_BYTE(pid, byte) send_byte(pid, byte, 7)

void send_byte(int pid, unsigned char byte, int position)
{
	if (position > 0)
	{
		send_byte(pid, byte / 2, position - 1);
	}
	usleep(800);
	kill(pid, byte % 2 ? SIGUSR2 : SIGUSR1);
}

int main(int ac, char **av)
{
	int pid = atoi(av[1]);
	char *str = av[2];
	
	while (*str)
	{
		printf("%c\n", *str);
		SEND_BYTE(pid, *str);
		str++;	
	}
	SEND_BYTE(pid, 0);
	return (0);
}