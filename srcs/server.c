#include "../includes/minitalk.h"

static void	reset_vars(unsigned char *byte, int *counter)
{
	*byte = 0;
	*counter = 0;
}

static void	ft_write(int bit, pid_t pid_client)
{
	static unsigned char	byte;
	static int				counter;
	static pid_t			last_pid;

	if (last_pid != 0 && last_pid != pid_client)
	{
		reset_vars(&byte, &counter);
		printf(" -> this frame of the last client was incomplete.\n");
	}
	last_pid = pid_client;
	byte = byte | bit;
	counter++;
	if (counter == 8)
	{
		if (byte == 0)
		{
			printf("\n");
			last_pid = 0;
		}
		else
			printf("%c", byte);
		reset_vars(&byte, &counter);
	}
	else
		byte = byte << 1;
}

static void	handle_signal(int signum, siginfo_t *sig_info, void *ucontext_t)
{
	(void)sig_info;
	(void)ucontext_t;
	if (signum == SIGUSR1)
		ft_write(0, sig_info->si_pid);
	if (signum == SIGUSR2)
		ft_write(1, sig_info->si_pid);
}

static int	register_handler(int signum)
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = handle_signal;
	return (sigaction(signum, &sig, NULL));
}

int	main(void)
{
	pid_t	a;

	a = getpid();
	printf("PID : %d\n\n", a);
	if (register_handler(SIGUSR1) == -1)
	{
		printf("Error when register SIGUSER1 listener.\n");
		exit(1);
	}
	else if (register_handler(SIGUSR2) == -1)
	{
		printf("Error when register SIGUSER2 listener.\n");
		exit(1);
	}
	while (42)
		pause();
	return (0);
}
