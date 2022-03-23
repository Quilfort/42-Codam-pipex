/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:16:31 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/23 17:53:10 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(char *argv[], char**envp, t_vars *vars)
{
	vars->cmd = ft_split(argv[2], ' ');
	if (!vars->cmd)
		print_error(vars);
	close(vars->pipefd[0]);
	if (dup2(vars->f1, STDIN_FILENO) == -1)
		print_error(vars);
	if (dup2(vars->pipefd[1], STDOUT_FILENO) == -1)
		print_error(vars);
	close(vars->pipefd[0]);
	vars->path_cmd = ft_strdup(vars->cmd[0]);
	right_path(vars);
	if (!vars->my_path)
	{
		free_split(vars->path);
		free_split(vars->cmd);
		free(vars->path_cmd);
		print_error(vars);
	}
	else
		execve(vars->my_path, vars->cmd, envp);
}

void	child_middle(char *argv[], char**envp, t_vars *vars)
{
	vars->cmd = ft_split(argv[vars->argv_index + 1], ' ');
	if (!vars->cmd)
		print_error(vars);
	close(vars->pipefd[0]);
	if (dup2(vars->pipefd[0], STDOUT_FILENO) == -1)
		print_error(vars);
	if (dup2(vars->pipefd[1], STDIN_FILENO) == -1)
		print_error(vars);
	vars->path_cmd = ft_strdup(vars->cmd[0]);
	right_path(vars);
	if (!vars->my_path)
	{
		free_split(vars->path);
		free_split(vars->cmd);
		free(vars->path_cmd);
		print_error(vars);
	}
	else
		execve(vars->my_path, vars->cmd, envp);
}

void	child_last(char *argv[], char**envp, t_vars *vars)
{
	vars->cmd = ft_split(argv[vars->argc - 2], ' ');
	if (!vars->cmd)
		print_error(vars);
	close(vars->pipefd[1]);
	if (dup2(vars->pipefd[0], STDIN_FILENO) == -1)
		print_error(vars);
	if (dup2(vars->f2, STDOUT_FILENO) == -1)
		print_error(vars);
	vars->path_cmd = ft_strdup(vars->cmd[0]);
	right_path(vars);
	if (!vars->my_path)
	{
		free_split(vars->path);
		free_split(vars->cmd);
		free(vars->path_cmd);
		print_error(vars);
	}
	else
		execve(vars->my_path, vars->cmd, envp);
}

void	pipex(char *argv[], char**envp, t_vars *vars)
{
	pid_t	child1;
	pid_t	child_m;

	vars->argv_index = 2;
	// vars->argv_index = 1;
	// while (vars->argv_index < vars->argc - 3)
	// {
	// 	if (pipe(vars->pipefd) == -1)
	// 		print_error(vars);
	// 	child1 = fork();
	// 	if (child1 < 0)
	// 		print_error(vars);
	// 	if (child1 == 0)
	// 		child_one(argv, envp, vars);
	// 	vars->argv_index++;
	// 	if (vars->argv_index < vars->argc - 3)
	// 	{
	// 		close(vars->pipefd[1]);
	// 		if (dup2(vars->pipefd[0], STDIN_FILENO) == -1)
	// 			print_error(vars);
	// 		if (dup2(vars->pipefd[1], STDOUT_FILENO) == -1)
	// 			print_error(vars);
	// 	}
	// }
	if (pipe(vars->pipefd) == -1)
		print_error(vars);
	child1 = fork();
	if (child1 < 0)
		print_error(vars);
	if (child1 == 0)
		child_one(argv, envp, vars);
	while (vars->argv_index < vars->argc - 3)
	{
		if (pipe(vars->pipefd) == -1)
			print_error(vars);
		child_m = fork();
		if (child_m < 0)
			print_error(vars);
		if (child_m == 0)
			child_middle(argv, envp, vars);
		vars->argv_index++;
	}
	child_last(argv, envp, vars);
	close(vars->f1);
	close(vars->f2);
	close(vars->pipefd[0]);
	close(vars->pipefd[1]);
	// waitpid(child1, NULL, 0);
	waitpid(-1, NULL, 0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_vars	vars;

	vars.argc = argc;
	vars.f1 = open(argv[1], O_RDONLY);
	vars.f2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars.f1 < 0)
		exit (1);
	if (vars.f2 < 0)
		exit (1);
	vars.path = find_path(envp, &vars);
	pipex(argv, envp, &vars);
	return (0);
}
