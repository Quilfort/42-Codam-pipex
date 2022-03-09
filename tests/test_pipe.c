#include "./src/libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int		pipefd[2];
	int		child1;
	int		child2;	

	if (pipe(pipefd) == -1)
		return 1;
	child1 = fork();
	if (child1 < 0)
		return 2;
	if (child1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close (pipefd[0]);
		close (pipefd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}

	child2 = fork();
	if (child2 < 0)
		return 3;
	if (child2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		// close (pipefd[0]);
		// close (pipefd[1]);
		execlp("grep" "grep" "round-trip", NULL);
	}

	close (pipefd[0]);
	close (pipefd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	return (0);


}
