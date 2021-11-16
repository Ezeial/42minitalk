#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "libft.h"

void	send_byte(int pid, unsigned char byte, int position)
{
	if (position > 0)
	{
		send_byte(pid, byte / 2, position - 1);
	}
	usleep(800);
	if (byte % 2)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	int		pid;
	char	*str;

	pid = atoi(av[1]);
	str = av[2];
	while (*str)
	{
		printf("%c\n", *str);
		send_byte(pid, *str, 7);
		str++;
	}
	send_byte(pid, 0, 7);
	return (0);
}
