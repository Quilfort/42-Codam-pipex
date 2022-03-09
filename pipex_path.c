/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:29:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/09 12:24:04 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp)
{
	char	**path;	
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		print_error();
	return (path);
}

char	*right_path(char **path, char *path_cmd, int index_split)
{
	char	*slash;
	char	*pipex_path;
	char	*my_path;
	int		i;

	i = 0;
	while (i < index_split)
	{
		slash = ft_strjoin(path[i], "/");
		if (!slash)
			print_error();
		pipex_path = ft_strjoin(slash, path_cmd);
		if (!pipex_path)
			print_error();
		if (access(pipex_path, F_OK) == 0)
		{
			my_path = pipex_path;
		}
		i++;
	}
	free(slash);
	free(pipex_path);
	return (my_path);
}

int	split_index(char **split)
{
	int	index;

	index = 0;
	while (split[index])
		index++;
	return (index);
}
