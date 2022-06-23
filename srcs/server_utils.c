/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:01:11 by egiraldi          #+#    #+#             */
/*   Updated: 2022/06/23 22:17:40 by egiraldi         ###   ########lyon.fr   */
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

void	clear_buff_data(t_buff_data *buff_data)
{
	clean_buffer(buff_data);
	if (buff_data->str)
	{
		free(buff_data->str);
		buff_data->str = NULL;
	}
}

static void	add_to_buff(t_buff_data *buff_data, char c)
{
	buff_data->buffer[buff_data->index] = c;
	(buff_data->index)++;
}

static int	push_in_buffer(t_buff_data *buff_data, char c)
{
	char	*temp;

	if (buff_data->index < BUFFER_SIZE)
		add_to_buff(buff_data, c);
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
		add_to_buff(buff_data, c);
	}
	return (0);
}

void	ft_byte_received(t_buff_data *buff_data, pid_t *last_pid,
	unsigned char *byte, int *counter)
{
	if (*byte == 0)
	{
		if (buff_data->str)
		{
			ft_putstr_fd(buff_data->str, 1);
			free(buff_data->str);
			buff_data->str = NULL;
		}
		ft_putendl_fd(buff_data->buffer, 1);
		clean_buffer(buff_data);
		*last_pid = 0;
	}
	else
	{
		if (push_in_buffer(buff_data, *byte) < 0)
		{
			clear_buff_data(buff_data);
			*byte = 0;
			*counter = 0;
			return ;
		}
	}
	*byte = 0;
	*counter = 0;
}
