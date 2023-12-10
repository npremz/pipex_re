/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:03:28 by npremont          #+#    #+#             */
/*   Updated: 2023/12/10 14:58:16 by npremont         ###   ########.fr       */
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

	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
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

void	ft_forks(char **argv, char **envp, int *fd)
{
	int	pid1;
	int	pid2;

	pid1 = fork();
	if (pid1 == -1)
		ft_error();
	if (pid1 == 0)
		ft_child(argv, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
		ft_error();
	if (pid2 == 0)
		ft_parent(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (perror("Pipe failed"), 1);
		ft_forks(argv, envp, fd);
	}
	else
		ft_printf("Error: Wrong input format\n");
	return (0);
}
