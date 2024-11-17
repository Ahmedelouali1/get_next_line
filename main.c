#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int	main(int argc, char **argv)
{
	int fd;
	int i = 1;
	char *line;
	
	if (argc >= 2)
	{
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			line = get_next_line(fd);
			while(line)
			{
				 printf("%s", line);
       			    	 free(line);
       			    	 line = get_next_line(fd);
			}	
			free(line);
			if(!fd)
				close(fd);
		i++;
		}
	}
	return(0);
}
