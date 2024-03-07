/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:45:52 by ppolinta          #+#    #+#             */
/*   Updated: 2024/01/16 20:37:14 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>

char	*pathfinder(char *cmd, char **env);
char	*envpath(char **env);
char	*slashjoin(char *s1, char *s2);
void	freearray(char **arr);
int		get_fd(char *file, int io);
void	errors(int code, char *str);
void	child(char **av, char **env, int *pipend, int fd);
void	parent(int *pipend);
void	execute(char *cmd, char **env);

#endif