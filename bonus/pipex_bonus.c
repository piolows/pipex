/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:45:32 by ppolinta          #+#    #+#             */
/*   Updated: 2024/01/17 15:29:40 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute(char *cmd, char **env)
{
	char	**cmd_words;
	char	*path;

	cmd_words = ft_split(cmd, ' ');
	path = pathfinder(cmd_words[0], env);
	if (execve(path, cmd_words, env) == -1)
	{
		errors(5, NULL);
		ft_putendl_fd(path, 2);
		freearray(cmd_words);
		free(path);
		exit(127);
	}
}

void	exit_check(pid_t pid)
{
	int		status[2];
	pid_t	temp;

	status[1] = 0;
	temp = 1;
	while (temp > 0)
	{
		temp = wait(&status[0]);
		if (temp == pid)
			status[1] = status[0];
	}
	if (WIFEXITED(status[1]))
		exit(WEXITSTATUS(status[1]));
}

void	fd_check(int fd)
{
	if (fd < 0)
		exit(1);
	if (dup2(fd, STDIN_FILENO) == -1)
		errors(6, NULL);
	close(fd);
}

void	pipex(int ac, char **av, char **env, int fd)
{
	pid_t	pid;
	int		pipend[2];
	int		i;

	i = 1;
	av += 2;
	while (++i < ac - 1)
	{
		if (pipe(pipend) == -1)
			errors(6, NULL);
		pid = fork();
		if (pid == -1)
			errors(6, NULL);
		if (pid == 0)
		{
			if (i == 2)
				fd_check(fd);
			child(av, env, pipend, (ac - i - 1) * (i == ac - 2));
		}
		av++;
		parent(pipend);
	}
	exit_check(pid);
}

int	main(int ac, char **av, char **env)
{
	int	fd;

	if (!*env || !env)
	{
		ft_putendl_fd("No environment found.", 2);
		exit(1);
	}
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (ac < 6)
			errors(4, NULL);
		here_doc(av, 0, NULL);
		here_doc_pipex(ac, av, env);
	}
	if (ac < 5)
		errors(1, NULL);
	else
	{
		fd = get_fd(av[1], 0);
		pipex(ac, av, env, fd);
	}
}
