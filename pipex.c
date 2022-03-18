/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:16:31 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/16 16:12:57 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(char *argv[], char**envp, int f1, int *pipefd)
{
	char	**path;
	char	**cmd;
	char	*path_cmd;
	char	*my_path;

	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		print_error();
	close(pipefd[0]);
	if (dup2(f1, STDIN_FILENO) == -1)
		perror("Dup Failed");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		perror("Dup Failed");
	path_cmd = ft_strdup(cmd[0]);
	path = find_path(envp);
	my_path = right_path(path, path_cmd);
	if (!my_path)
	{
		free_split(path);
		free_split(cmd);
		free(path_cmd);
		print_error();
	}
	else
		execve(my_path, cmd, envp);
}

void	child_two(char *argv[], char**envp, int f2, int *pipefd)
{
	char	**path;
	char	**cmd;
	char	*path_cmd;
	char	*my_path;

	cmd = ft_split(argv[3], ' ');
	if (!cmd)
		print_error();
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("Dup Failed");
	if (dup2(f2, STDOUT_FILENO) == -1)
		perror("Dup Failed");
	path_cmd = ft_strdup(cmd[0]);
	path = find_path(envp);
	my_path = right_path(path, path_cmd);
	if (!my_path)
	{
		free_split(path);
		free_split(cmd);
		free(path_cmd);
		print_error();
	}
	else
		execve(my_path, cmd, envp);
}

void	pipex(char *argv[], char**envp, int *pipefd)
{
	int		f1;
	int		f2;
	pid_t	child1;
	pid_t	child2;

	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		print_error();
	child1 = fork();
	if (child1 < 0)
		perror("Fork 1 has Failed");
	if (child1 == 0)
		child_one(argv, envp, f1, pipefd);
	child2 = fork();
	if (child2 < 0)
		perror("Fork 2 has Failed");
	if (child2 == 0)
		child_two(argv, envp, f2, pipefd);
	close(f1);
	close(f2);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
}

int	main(int argc, char *argv[], char **envp)
{
	int		pipefd[2];

	if (argc > 5 || argc < 5)
	{
		perror("Need 4 arguments");
		exit (1);
	}
	if (pipe(pipefd) == -1)
		print_error();
	pipex(argv, envp, pipefd);
	return (0);
}
