/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:16:31 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/30 10:31:03 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	preform_cmd(char *argv[], char**envp, t_vars *vars)
{
	vars->cmd = ft_split(argv[vars->argv_index + 1], ' ');
	if (!vars->cmd)
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
		if (execve(vars->my_path, vars->cmd, envp) < 0)
			print_error(vars);
}

static void	fork_proces(char *argv[], char**envp, t_vars *vars)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		print_error(vars);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			print_error(vars);
		preform_cmd(argv, envp, vars);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			print_error(vars);
	}
}

static void	pipex(char *argv[], char**envp, t_vars *vars)
{
	vars->argv_index = 1;
	if (dup2(vars->f1, STDIN_FILENO) == -1)
		print_error(vars);
	if (dup2(vars->f2, STDOUT_FILENO) == -1)
		print_error(vars);
	while (vars->argv_index < vars->argc - 3)
	{
		fork_proces(argv, envp, vars);
		vars->argv_index++;
	}
	preform_cmd(argv, envp, vars);
	close(vars->f1);
	close(vars->f2);
}

int	main(int argc, char *argv[], char **envp)
{
	t_vars	vars;

	if (argc < 5)
		exit (1);
	vars.argc = argc;
	vars.f1 = open(argv[1], O_RDONLY);
	vars.f2 = open(argv[vars.argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars.f1 < 0)
		exit (1);
	if (vars.f2 < 0)
		exit (1);
	vars.path = find_path(envp, &vars);
	pipex(argv, envp, &vars);
	return (0);
}
