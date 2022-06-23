/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:50:29 by egiraldi          #+#    #+#             */
/*   Updated: 2022/06/23 21:11:06 by egiraldi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	clean_buffer(t_buff_data *buff_data)
{
	size_t	index;

	index = 0;
	while (index < BUFFER_SIZE)
		buff_data->buffer[index++] = 0;
	buff_data->index = 0;
}

static void	clear_buff_data(t_buff_data *buff_data)
{
	clean_buffer(buff_data);
	if (buff_data->str)
	{
		free(buff_data->str);
		buff_data->str = NULL;
	}
}

static int	push_in_buffer(t_buff_data *buff_data, char c)
{
	char	*temp;

	if (buff_data->index < BUFFER_SIZE)
	{
		buff_data->buffer[buff_data->index] = c;
		(buff_data->index)++;
	}
	else
	{
		if (!buff_data->str)
		{
			buff_data->str = ft_strdup(buff_data->buffer);
			if (!buff_data->str)
				return (-1);
		}
		else
		{
			temp = buff_data->str;
			buff_data->str = ft_strjoin(buff_data->str, buff_data->buffer);
			free(temp);
			if (!buff_data->str)
				return (-1);
		}
		clean_buffer(buff_data);
		buff_data->buffer[buff_data->index] = c;
		(buff_data->index)++;
	}
	return (0);
}

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
		printf(" -> this frame of the last client was incomplete.\n");
		clear_buff_data(&buff_data);
	}
	last_pid = pid_client;
	byte = byte | bit;
	counter++;
	if (counter == 8)
	{
		if (byte == 0)
		{
			if (buff_data.str)
			{
				printf("%s", buff_data.str);
				free(buff_data.str);
				buff_data.str = NULL;
			}
			printf("%s\n", buff_data.buffer);
			clean_buffer(&buff_data);
			last_pid = 0;
		}
		else
		{
			if (push_in_buffer(&buff_data, byte) < 0)
			{
				clear_buff_data(&buff_data);
				return ;
			}
		}
		byte = 0;
		counter = 0;
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
	pid_t		a;

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
