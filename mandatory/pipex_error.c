/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 11:28:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/21 18:54:09 by qfrederi      ########   odam.nl         */
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

void	print_error_127(void)
{
	char	*error;

	error = "There is an error 127";
	ft_putstr_fd(error, 2);
	exit(127);
}

void	print_error_0(void)
{
	char	*error;

	error = "There is an error 0";
	ft_putstr_fd(error, 2);
	exit(0);
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
