
#include "./src/libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

int	main(int argc, char *argv[], char **envp)
{
	int f1;
	int f2;
	int f3;
	int f4;

	f1 = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	f2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0644);
	f3 = open(argv[3], O_CREAT | O_RDWR | O_TRUNC, 0644);
	f4 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);

	return(0);
}
