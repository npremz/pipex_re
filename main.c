/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:03:28 by npremont          #+#    #+#             */
/*   Updated: 2023/12/05 11:51:18 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		perror("Open file failed");
		exit(2);
	}
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	exec(argv[2], envp);
	close(infile);
	close(fd[1]);
}

void	ft_parent(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (outfile == -1)
	{
		perror("Open file failed");
		exit(3);
	}
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	exec(argv[3], envp);
	close(outfile);
	close(fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (perror("Pipe failed"), 1);
		pid1 = fork();
		if (pid1 == -1)
			return (perror("Child process failed"), 1);
		if (pid1 == 0)
			ft_child(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		ft_parent(argv, envp, fd);
	}
	else
		ft_printf("Error: Wrong input format\n");
	return (0);
}
