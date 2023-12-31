/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:00:41 by npremont          #+#    #+#             */
/*   Updated: 2023/12/10 09:55:42 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>

void	ft_free_split(char **split);
void	ft_free(void *ptr);
char	*getpath(char *cmd, char **envp);
void	exec(char *arg, char **envp);
void	ft_error(void);

#endif
