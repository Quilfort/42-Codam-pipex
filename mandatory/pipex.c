/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:16:31 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/21 13:51:25 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(char *argv[], char**envp, t_vars *vars)
{
	char	*my_path;

	vars->cmd = ft_split(argv[2], ' ');
	if (!vars->cmd)
		print_error();
	close(vars->pipefd[0]);
	if (dup2(vars->f1, STDIN_FILENO) == -1)
		perror("Dup Failed");
	if (dup2(vars->pipefd[1], STDOUT_FILENO) == -1)
		perror("Dup Failed");
	vars->path_cmd = ft_strdup(vars->cmd[0]);
	vars->path = find_path(envp);
	my_path = right_path(vars);
	if (!my_path)
	{
		free_split(vars->path);
		free_split(vars->cmd);
		free(vars->path_cmd);
		print_error();
	}
	else
		execve(my_path, vars->cmd, envp);
}

void	child_two(char *argv[], char**envp, t_vars *vars)
{
	char	*my_path;

	vars->cmd = ft_split(argv[3], ' ');
	if (!vars->cmd)
		print_error();
	close(vars->pipefd[1]);
	if (dup2(vars->pipefd[0], STDIN_FILENO) == -1)
		perror("Dup Failed");
	if (dup2(vars->f2, STDOUT_FILENO) == -1)
		perror("Dup Failed");
	vars->path_cmd = ft_strdup(vars->cmd[0]);
	vars->path = find_path(envp);
	my_path = right_path(vars);
	if (!my_path)
	{
		free_split(vars->path);
		free_split(vars->cmd);
		free(vars->path_cmd);
		print_error();
	}
	else
		execve(my_path, vars->cmd, envp);
}

void	pipex(char *argv[], char**envp, t_vars *vars)
{
	pid_t	child1;
	pid_t	child2;

	child1 = fork();
	if (child1 < 0)
		perror("Fork 1 has Failed");
	if (child1 == 0)
		child_one(argv, envp, vars);
	child2 = fork();
	if (child2 < 0)
		perror("Fork 2 has Failed");
	if (child2 == 0)
		child_two(argv, envp, vars);
	close(vars->f1);
	close(vars->f2);
	close(vars->pipefd[0]);
	close(vars->pipefd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_vars	vars;

	if (argc > 5 || argc < 5)
	{
		perror("Need 4 arguments");
		exit (1);
	}
	if (pipe(vars.pipefd) == -1)
		print_error();
	vars.f1 = open(argv[1], O_RDONLY);
	vars.f2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars.f1 < 0 || vars.f2 < 0)
		print_error();
	pipex(argv, envp, &vars);
	return (0);
}
