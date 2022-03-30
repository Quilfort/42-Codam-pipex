/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:29:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/23 13:13:53 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp, t_vars *vars)
{
	char	**path;	
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		print_error(vars);
	return (path);
}

char	*right_path(t_vars *vars)
{
	char	*slash;
	char	*pipex_path;
	int		i;

	if (access(vars->path_cmd, X_OK) == 0)
		return (vars->my_path = ft_strdup(vars->path_cmd));
	i = 0;
	while (vars->path[i] != '\0')
	{
		slash = ft_strjoin(vars->path[i], "/");
		if (!slash)
			print_error(vars);
		pipex_path = ft_strjoin(slash, vars->path_cmd);
		if (!pipex_path)
			print_error(vars);
		if (access(pipex_path, F_OK) == 0)
			vars->my_path = ft_strdup(pipex_path);
		free(slash);
		free(pipex_path);
		i++;
	}
	if (!vars->my_path)
		print_error(vars);
	return (vars->my_path);
}
