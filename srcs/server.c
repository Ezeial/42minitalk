/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:50:29 by egiraldi          #+#    #+#             */
/*   Updated: 2022/06/23 22:26:01 by egiraldi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	ft_write(int bit, pid_t pid_client)
{
	static unsigned char	byte;
	static int				counter;
	static pid_t			last_pid;
	static t_buff_data		buff_data;

	if (last_pid != 0 && last_pid != pid_client)
	{
		byte = 0;
		counter = 0;
		ft_putstr_fd(" -> this frame of the last client was incomplete.\n", 1);
		clear_buff_data(&buff_data);
	}
	last_pid = pid_client;
	byte = byte | bit;
	counter++;
	if (counter == 8)
		ft_byte_received(&buff_data, &last_pid, &byte, &counter);
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
	pid_t		a;

	a = getpid();
	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(a, 1);
	ft_putstr_fd("\n\n", 1);
	if (register_handler(SIGUSR1) == -1)
	{
		ft_putstr_fd("Error when register SIGUSER1 listener.\n", 1);
		exit(1);
	}
	else if (register_handler(SIGUSR2) == -1)
	{
		ft_putstr_fd("Error when register SIGUSER2 listener.\n", 1);
		exit(1);
	}
	while (42)
		pause();
	return (0);
}
