/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:32:19 by albokanc          #+#    #+#             */
/*   Updated: 2024/03/27 19:37:36 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	msg0(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

int	msg127(char *err)
{
	write(2, err, ft_strlen(err));
	return (127);
}

void	msg_error(char *err)
{
	write(2, err, ft_strlen(err));
}
