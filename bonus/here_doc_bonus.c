/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:40:44 by ppolinta          #+#    #+#             */
/*   Updated: 2024/01/17 15:40:08 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_child(char **av, char **env, int *pipend, int ac)
{
	int	fd;

	if (!ac)
	{
		close(pipend[0]);
		if (dup2(pipend[1], STDOUT_FILENO) == -1)
			errors(6, NULL);
		close(pipend[1]);
		execute(av[0], env);
	}
	else
	{
		close(pipend[0]);
		close(pipend[1]);
		fd = get_fd(av[ac], 2);
		if (dup2(fd, STDOUT_FILENO) == -1)
			errors(6, NULL);
		close(fd);
		execute(av[0], env);
	}
}

void	here_doc_pipex(int ac, char **av, char **env)
{
	pid_t	pid;
	int		pipend[2];
	int		i;

	i = 2;
	av += 3;
	while (++i < ac - 1)
	{
		if (pipe(pipend) == -1)
			errors(6, NULL);
		pid = fork();
		if (pid == -1)
			errors(6, NULL);
		if (pid == 0)
			here_doc_child(av, env, pipend, (ac - i - 1) * (i == ac - 2));
		av++;
		parent(pipend);
	}
	exit_check(pid);
}

void	exit_here_doc_check(char **av, char *line)
{
	if (!ft_strncmp(line, av[2], ft_strlen(av[2]))
		&& ft_strlen(line) - 1 == ft_strlen(av[2]))
	{
		free(line);
		exit(0);
	}
}

void	here_doc(char **av, pid_t pid, char *line)
{
	int		pipend[2];

	if (pipe(pipend) == -1)
		errors(6, NULL);
	pid = fork();
	if (pid == -1)
		errors(6, NULL);
	if (pid == 0)
	{
		close(pipend[0]);
		while (1)
		{
			line = get_next_line(0);
			exit_here_doc_check(av, line);
			ft_putstr_fd(line, pipend[1]);
			free(line);
		}
	}
	else
	{
		close(pipend[1]);
		if (dup2(pipend[0], STDIN_FILENO) == -1)
			errors(6, NULL);
		wait(NULL);
	}
}
