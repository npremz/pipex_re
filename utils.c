/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:44:46 by npremont          #+#    #+#             */
/*   Updated: 2023/12/10 09:55:03 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getpath(char *cmd, char **envp)
{
	size_t	i;
	char	**paths;
	char	*path;
	char	*cmd_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		++i;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		++i;
	}
	ft_free_split(paths);
	return (NULL);
}

void	exec(char *arg, char **envp)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		ft_error();
	if (access(cmd[0], F_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			ft_error();
		return ;
	}
	path = getpath(cmd[0], envp);
	if (!path)
	{
		ft_free_split(cmd);
		ft_error();
	}
	if (execve(path, cmd, envp) == -1)
		ft_error();
}

void	ft_error(void)
{
	perror("Error");
	exit(1);
}
