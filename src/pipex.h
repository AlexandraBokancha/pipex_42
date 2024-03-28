/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:39:24 by albokanc          #+#    #+#             */
/*   Updated: 2024/03/27 20:16:24 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>

# define ERR_INFILE "No such file or directory.\n"
# define ERR_OUTFILE "Outfile.\n"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe.\n"
# define ERR_CMD "Command not found.\n"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		pipefd[2];
	char	**path;
	char	*cmd;
}				t_pipex;

char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, int n);

int		create_path(char **path, char *cmd, t_pipex *pipex);
void	path_format(t_pipex *pipex);
void	find_path(char **env, t_pipex *pipex);

int		msg0(char *err);
void	msg_error(char *err);
int		msg127(char *err);

void	free_tab(char **tab);

#endif
