/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:24:53 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/03/23 13:09:04 by qfrederi      ########   odam.nl         */
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

typedef struct s_vars {
	int		f1;
	int		f2;
	int		pipefd[2];
	char	**cmd;
	char	**path;
	char	*path_cmd;
	char	*my_path;
	int		argc;
	int		argv_index;

}				t_vars;

// Main
void	child_one(char *argv[], char**envp, t_vars *vars);
void	child_middle(char *argv[], char**envp, t_vars *vars);
void	child_last(char *argv[], char**envp, t_vars *vars);
void	pipex(char *argv[], char**envp, t_vars *vars);

//path
char	**find_path(char **envp, t_vars *vars);
char	*right_path(t_vars *vars);
void	free_split(char **input);
int		split_index(char **split);

//error
void	print_error(t_vars *vars);

// Utils
char	**ft_split(char const *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *str, int fd);

#endif