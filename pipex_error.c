/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 11:28:56 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/09 12:17:08 by qfrederi      ########   odam.nl         */
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

void	free_split(char **input, size_t max_index)
{
	size_t	i;

	i = 0;
	while (i < max_index)
	{
		free(input[i]);
		i++;
	}
	free(input);
}