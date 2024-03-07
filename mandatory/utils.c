/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:25:51 by ppolinta          #+#    #+#             */
/*   Updated: 2024/01/17 15:25:57 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*slashjoin(char *s1, char *s2)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	str[ft_strlen(s1)] = '/';
	ft_strlcpy(str + ft_strlen(s1) + 1, s2, ft_strlen(s2) + 1);
	return (str);
}

void	freearray(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	get_fd(char *file, int io)
{
	int	fd;

	if (io == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			errors(2, file);
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			errors(3, file);
	}
	return (fd);
}

void	errors(int code, char *str)
{
	if (code == 1)
		ft_putendl_fd
			("Invalid format.\n./pipex infile \"cmd\" \"cmd\" outfile", 2);
	if (code == 2 || code == 3)
	{
		perror(str);
		if (code == 2)
			return ;
	}
	if (code == 4)
	{
		ft_putstr_fd("Command not found: ", 2);
		return ;
	}
	if (code == 5)
		perror("Error");
	exit(1);
}
