/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 11:28:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/23 13:10:06 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(t_vars *vars)
{
	if (vars->my_path == NULL)
	{
		perror("Command not found");
		exit(127);
	}
	else
		perror("Whoops, something went wrong");
	exit(1);
}

int	split_index(char **split)
{
	int	index;

	index = 0;
	while (split[index])
		index++;
	return (index);
}

void	free_split(char **input)
{
	size_t	i;
	size_t	max_index;

	max_index = split_index(input);
	i = 0;
	while (i < max_index)
	{
		free(input[i]);
		i++;
	}
	free(input);
}
