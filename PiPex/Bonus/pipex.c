/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkabex <abkabex@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:39:31 by achahrou          #+#    #+#             */
/*   Updated: 2024/01/17 11:17:06 by abkabex          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	openf_check(t_data *pipex, char *f1, char *f2)
{
	pipex->fd2 = open(f2, O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (pipex->fd2 < 0)
		exiti("Error In Open File For Writing\n");
	pipex->fd1 = open(f1, O_RDONLY);
	if (pipex->fd1 < 0)
		exiti("Error In Open File For Reading\n");
	if (access(f1, R_OK) < 0)
		exiti("Error Reading File\n");
	if (access(f2, W_OK) < 0)
		exiti("Error Writing File\n");
}

void	child_p(t_data *pipex, int ac)
{
	if (ft_strcmp(pipex->infile, "here_doc") == 0)
	{
		pipex->fd1 = open("here_doc", O_RDONLY);
		if (pipex->fd1 < 0)
			exiti("Error In Open File For Reading\n");
	}
	dup2 (pipex->fd1, 0);
	if (pipex->i != ac - 2)
		dup2(pipex->fd[1], 1);
	else
	{
		dup2(pipex->fd2, 1);
		close(pipex->fd2);
	}
	close(pipex->fd[0]);
	execve(pipex->path, pipex->cmd, NULL);
	exit(EXIT_FAILURE);
}

void	parent_p(t_data *pipex)
{
	wait(NULL);
	close(pipex->fd[1]);
	pipex->fd1 = pipex->fd[0];
}

void	check_path(t_data *pipex, char *p1)
{
	int i = 0;
	if (access(p1, X_OK) == 0)
		pipex->path = p1;
	else
	{
		char *env_path = getenv("PATH");
		char **path = ft_split(env_path, ':');
		while (path[i])
		{
			char *potential_path = str_concat(path[i], "/");
			potential_path = str_concat(potential_path, p1);
			if (access(potential_path, X_OK) == 0)
			{
				pipex->path = potential_path;
				break;
			}
			i++;
			free(potential_path);
		}
		freex(path);
		if (pipex->path == NULL)
			exiti("Error In Path\n");
	}
}

int	main(int ac, char **av)
{
	t_data	pipex;

	pipex.i = 2;
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		handle_heredoc(&pipex, av[2]);
		pipex.i++;
	}
	else
		openf_check(&pipex, av[1], av[ac -1]);
	while (pipex.i < ac - 1)
	{
		pipex.cmd = ft_split(av[pipex.i], ' ');
		check_path(&pipex, pipex.cmd[0]);
		if (pipe(pipex.fd) < 0)
			exiti("Fork Error\n");
		pipex.pid = fork();
		if (pipex.pid < 0)
			exiti("Fork Error\n");
		else if (pipex.pid == 0)
			child_p(&pipex, ac);
		else
			parent_p(&pipex);
		pipex.i++;
	}
}