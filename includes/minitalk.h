/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:45:54 by egiraldi          #+#    #+#             */
/*   Updated: 2022/06/23 21:05:32 by egiraldi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

# define BUFFER_SIZE 50

typedef struct buff_data {
	char	*str;
	char	buffer[BUFFER_SIZE];
	size_t	index;
}	t_buff_data;

#endif