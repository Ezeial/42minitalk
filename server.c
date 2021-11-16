#include <sys/types.h>
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void	ft_write(int bit)
{
	static unsigned char	byte;
	static int				counter;

	byte = byte | bit;
	counter++;
	if (counter == 8)
	{
		if (byte == 0)
			printf("\n");
		else
			printf("%c", byte);
		counter = 0;
		byte = 0;
	}
	else
		byte = byte << 1;
}

void	handle_signal(int signum)
{
	if (signum == SIGUSR1)
		ft_write(0);
	if (signum == SIGUSR2)
		ft_write(1);
}

int	main(int ac, char **av)
{
	pid_t	a;

	a = getpid();
	printf("PID : %d\n\n", a);
	if (signal(SIGUSR1, handle_signal) == SIG_ERR)
	{
		printf("Error\n");
		exit(1);
	}
	if (signal(SIGUSR2, handle_signal) == SIG_ERR)
	{
		printf("Error\n");
		exit(1);
	}
	while (42)
		pause();
	return (0);
}
