/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:37:05 by albokanc          #+#    #+#             */
/*   Updated: 2024/03/27 20:12:57 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child2(char **args, t_pipex *pipex, char **env)
{
	char	**cmd;

	pipex->outfile = open(args[4], O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (pipex->outfile < 0)
		msg_error(ERR_OUTFILE);
	cmd = ft_split(args[3], ' ');
	dup2(pipex->pipefd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close (pipex->pipefd[0]);
	close (pipex->pipefd[1]);
	if (create_path(pipex->path, cmd[0], pipex) != 0)
	{
		if (pipex->cmd != NULL)
			free(pipex->cmd);
		msg0(ERR_CMD);
	}
	execve(pipex->cmd, cmd, env);
	close (pipex->outfile);
	free_tab(cmd);
	free_tab(pipex->path);
	exit (1);
}

void	child1(char **args, t_pipex *pipex, char **env)
{
	char	**cmd;

	pipex->infile = open(args[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		msg_error(ERR_INFILE);
		free_tab(pipex->path);
		exit (1);
	}
	cmd = ft_split(args[2], ' ');
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	dup2(pipex->infile, STDIN_FILENO);
	close (pipex->pipefd[0]);
	close (pipex->pipefd[1]);
	if (create_path(pipex->path, cmd[0], pipex) != 0)
	{
		if (pipex->cmd != NULL)
			free(pipex->cmd);
		msg0(ERR_CMD);
	}
	execve(pipex->cmd, cmd, env);
	close (pipex->infile);
	free_tab(cmd);
	free_tab(pipex->path);
	exit (1);
}

void	parent_process(t_pipex *pipex)
{
	close (pipex->pipefd[0]);
	close (pipex->pipefd[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	pipex.cmd = NULL;
	if (ac != 5)
		return (msg0(ERR_INPUT));
	if (pipe(pipex.pipefd) < 0)
		msg_error(ERR_PIPE);
	find_path(env, &pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child1(av, &pipex, env);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child2(av, &pipex, env);
	free_tab(pipex.path);
	parent_process(&pipex);
	return (0);
}
