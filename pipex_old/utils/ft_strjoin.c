/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:39:40 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/16 14:17:43 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*pointer;

	if (!s1 || !s2)
		return (NULL);
	pointer = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (pointer == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		pointer[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{	
		pointer[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	pointer[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (pointer);
}
