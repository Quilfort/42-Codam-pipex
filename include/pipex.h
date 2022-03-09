/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:24:53 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/09 11:34:11 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

// Main
void	child_one(char *argv[], char**envp, int f1, int *pipefd);
void	child_two(char *argv[], char**envp, int f2, int *pipefd);
void	pipex(char *argv[], char**envp, int *pipefd);

//path
char	**find_path(char **envp);
char	*right_path(char **path, char *path_cmd, int index_split);
void	free_split(char **input, size_t max_index);
int		split_index(char **split);

//error
void	print_error(void);

// Utils
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *str, int fd);

#endif