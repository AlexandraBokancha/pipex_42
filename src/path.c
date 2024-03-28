/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:37:59 by albokanc          #+#    #+#             */
/*   Updated: 2024/03/27 20:13:47 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	absent_cmd(char *cmd, t_pipex *pipex)
{
	if (access(cmd, F_OK | R_OK) == 0)
	{
		free(pipex->cmd);
		pipex->cmd = cmd;
	}
	else
		return (1);
	return (0);
}

int	absent_env(char *cmd, t_pipex *pipex)
{
	if (access(cmd, F_OK | R_OK) == 0)
			pipex->cmd = cmd;
	else
		return (1);
	return (0);
}

int	create_path(char **path, char *cmd, t_pipex *pipex)
{
	int	res;

	if (path == NULL)
		return (absent_env(cmd, pipex));
	else
	{
		pipex->cmd = ft_strjoin(*path, cmd);
		while (*path)
		{	
			res = access(pipex->cmd, F_OK | R_OK);
			if (res == 0)
				break ;
			path++;
			free(pipex->cmd);
			pipex->cmd = ft_strjoin(*path, cmd);
		}
		if (res < 0)
			return (absent_cmd(cmd, pipex));
	}
	return (0);
}

void	path_format(t_pipex *pipex)
{
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	while (pipex->path[i])
	{
		len = ft_strlen(pipex->path[i]);
		if (pipex->path[i][len - 1] != '/')
		{
			tmp = pipex->path[i];
			pipex->path[i] = ft_strjoin(pipex->path[i], "/");
			free (tmp);
		}
		i++;
	}
}

void	find_path(char **env, t_pipex *pipex)
{
	if (env[0] == NULL)
	{
		pipex->path = NULL;
		return ;
	}
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			pipex->path = ft_split(*env + 5, ':');
		env++;
	}
	path_format(pipex);
}
