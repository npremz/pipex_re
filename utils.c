/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:44:46 by npremont          #+#    #+#             */
/*   Updated: 2023/12/05 11:52:17 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getpath(char **envp)
{
	size_t	i;

	i = 0;
	printf("test");
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (NULL);
}

void	exec(char *arg, char **envp)
{
	char	*path;

	(void)arg;
	path = getpath(envp);
}
