#include "../includes/minitalk.h"

/**
 * Return -1 if an error has occurred otherwise 0
 */
static int	send_byte(int pid, unsigned char byte, int position)
{
	if (position > 0 && send_byte(pid, byte / 2, position - 1) == -1)
		return (-1);
	if (usleep(800) == -1)
		return (-1);
	if (byte % 2)
		return (kill(pid, SIGUSR2));
	else
		return (kill(pid, SIGUSR1));
}

static void	check_arg(int ac)
{
	if (ac < 3)
	{
		printf("The 1st must be the PID of the server. " \
			"The 2nd argument must be a string.\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	int		pid;
	char	*str;

	check_arg(ac);
	pid = atoi(av[1]);
	str = av[2];
	while (*str)
	{
		printf("%c\n", *str);
		if (send_byte(pid, *str, 7) == -1)
		{
			printf("An error has occurred when sending the '%c'.\n", *str);
			return (1);
		}
		str++;
	}
	if (send_byte(pid, 0, 7) == -1)
	{
		printf("An error has occurred when sending the end signal.");
		return (1);
	}
	return (0);
}
