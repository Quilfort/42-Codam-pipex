/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 11:28:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/16 12:00:31 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(void)
{
	char	*error;

	error = "There is an error";
	ft_putstr_fd(error, 2);
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
