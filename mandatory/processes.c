/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:26:47 by ppolinta          #+#    #+#             */
/*   Updated: 2024/01/16 20:38:08 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **av, char **env, int *pipend, int ac)
{
	int	fd;

	if (!ac)
	{
		close(pipend[0]);
		if (dup2(pipend[1], STDOUT_FILENO) == -1)
			errors(5, NULL);
		close(pipend[1]);
		execute(av[0], env);
	}
	else
	{
		close(pipend[0]);
		close(pipend[1]);
		fd = get_fd(av[ac], 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			errors(5, NULL);
		close(fd);
		execute(av[0], env);
	}
}

void	parent(int *pipend)
{
	close(pipend[1]);
	if (dup2(pipend[0], STDIN_FILENO) == -1)
		errors(5, NULL);
	close(pipend[0]);
}
