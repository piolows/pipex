/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:45:52 by ppolinta          #+#    #+#             */
/*   Updated: 2024/01/17 15:22:53 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line_bonus.h"
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
void	here_doc(char **av, pid_t pid, char *line);
void	child(char **av, char **env, int *pipend, int ac);
void	parent(int *pipend);
void	execute(char *cmd, char **env);
int		ft_strcmp(const char *s1, const char *s2);
void	here_doc_pipex(int ac, char **av, char **env);
void	exit_check(pid_t pid);
void	fd_check(int fd);

#endif