
#include "./src/libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char	**find_path(char **envp)
{
	char	**path;	
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*right_path(char **path, char *path_cmd)
{
	char	*slash;
	char	*pipex_path;
	char	*my_path;
	int		i;

	i = 0;
	while (i < 6)
	{
		slash = ft_strjoin(path[i], "/");
		pipex_path = ft_strjoin(slash, path_cmd);
		if (access(pipex_path, F_OK) == 0)
		{
			printf("%s\n\n", pipex_path);
			my_path = pipex_path;
		}
		i++;
	}
	return (my_path);
}

void	child_one(char *argv[], char**envp, int f1)
{
	char	**path;
	char	*slash;
	char	**cmd;
	char	*path_cmd;
	char	*my_path;

	cmd = ft_split(argv[2], ' ');
	path_cmd = cmd[0];
	printf("%s\n\n", *cmd);
	path = find_path(envp);
	my_path = right_path(path, path_cmd);
	dup2(f1, STDIN_FILENO);
	execve(my_path, cmd, envp);
}

void	child_two(char *argv[], char**envp, int f2)
{
	char	**path;
	char	*slash;
	char	**cmd;
	char	*path_cmd;
	char	*my_path;

	cmd = ft_split(argv[3], ' ');
	path_cmd = cmd[0];
	printf("%s\n\n", *cmd);
	path = find_path(envp);
	my_path = right_path(path, path_cmd);
	dup2(f2, STDOUT_FILENO);
	execve(my_path, cmd, envp);
}

int	main(int argc, char *argv[], char **envp)
{
	int	f1;
	int	f2;

	if (argc > 4)
	{
		return (0);
	}
	f1 = open(argv[1], O_RDONLY);
	// f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	child_one(argv, envp, f1);
	// child_two(argv, envp, f2);
	return (0);
}
