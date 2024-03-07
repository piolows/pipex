/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:47:36 by ppolinta          #+#    #+#             */
/*   Updated: 2024/01/08 15:24:40 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*envpath(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4))
		i++;
	if (!env[i])
	{
		ft_putstr_fd("No path variable found in environment.\n", 2);
		exit(1);
		return (NULL);
	}
	return (env[i] + 5);
}

char	*pathfinder(char *cmd, char **env)
{
	char	**env_words;
	char	**cmd_words;
	char	*path;
	int		acc;
	int		i;

	i = 0;
	cmd_words = ft_split(cmd, ' ');
	env_words = ft_split(envpath(env), ':');
	while (env_words[i])
	{
		path = slashjoin(env_words[i], cmd_words[0]);
		acc = access(path, F_OK | X_OK);
		if (acc == 0)
		{
			freearray(env_words);
			freearray(cmd_words);
			return (path);
		}
		free(path);
		i++;
	}
	freearray(env_words);
	freearray(cmd_words);
	return (ft_strdup(cmd));
}
