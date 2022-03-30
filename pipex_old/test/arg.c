#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char *argv[], char **envp)
{
	int	i;
	int	count;

	printf("Dit is aantal argumenten  %d\n\n", argc - 1);
	printf("Dit is de text voor start  %s\n\n", argv[1]);
	printf("Dit is de text voor einde  %s\n\n", argv[argc - 1]);

	i = 2;
	count = 0;
	while (count < (argc - 2))
	{
		printf("Print my arguments  %s\n\n", argv[i]);
		i++;
		count++;
	}
	return (0);
}
