/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfrederi <qfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:32:04 by qfrederi          #+#    #+#             */
/*   Updated: 2022/03/04 12:57:26 by qfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


void	child_two(int f2, char *cmd2)
{
	dup2(f2, STDIN_FILENO);
	close (f2);
	exit(EXIT_FAILURE);
}

void	child_one(int f1, char *cmd1)
{
	dup2(f1, STDIN_FILENO);
	
	close (f1);
	exit(EXIT_FAILURE);
}

void	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child_one(f1, cmd1);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child_two(f2, cmd2);
	close(end[0]);         // this is the parent
	close(end[1]);         // doing nothing
	waitpid(child1, &status, 0);  // supervising the children
	waitpid(child2, &status, 0);  // while they finish their tasks
}

void	find_path(**envp)
{
	
}


int	main(int argc, char *argv[], char **envp)
{
	int	f1;
	int	f2;

	if (argc > 4)
	{
		return (0);
	}
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
	{
		return (-1);
	}
	pipex(f1, f2, cmd1, cmd2);
	return (0);
}
