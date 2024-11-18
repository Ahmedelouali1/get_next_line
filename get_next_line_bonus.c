/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:21:12 by ahmel-ou          #+#    #+#             */
/*   Updated: 2024/11/18 16:26:32 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_update(char *str)
{
	int		i;
	int		j;
	char	*scnd_str;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	scnd_str = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!scnd_str)
	{
		free(str);
		return (NULL);
	}
	i++;
	while (str[i] != '\0')
		scnd_str[j++] = str[i++];
	scnd_str[j] = '\0';
	free(str);
	return (scnd_str);
}

size_t	ft_newlinelengh(const char *str)
{
	size_t	lengh;

	lengh = 0;
	if (!str)
		return (0);
	while (str[lengh] != '\0' && str[lengh] != '\n')
		lengh++;
	return (lengh);
}

char	*ft_read(char *buf, char *str, int fd)
{
	int		i;
	char	*scnd_str;

	i = 1;
	buf[0] = 0;
	while (i > 0 && !ft_strchr(buf, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = 0;
		scnd_str = str;
		str = ft_strjoin(str, buf);
		free(scnd_str);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*svariable[10240];
	char		*line;
	char		*buf;
	char		*scnd_str;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 10240 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	svariable[fd] = ft_read(buf, svariable[fd], fd);
	if (!svariable[fd])
		return (NULL);
	if (*svariable[fd] == '\0')
		return (free(svariable[fd]), svariable[fd] = 0);
	scnd_str = svariable[fd];
	line = ft_substr(scnd_str, 0, ft_newlinelengh(scnd_str) + 1);
	if (!*line)
		return (free(line), NULL);
	svariable[fd] = ft_update(svariable[fd]);
	return (line);
}
/*
#include <fcntl.h>
int main()
{
	int fd = open("test.txt", O_CREAT | O_RDWR, 0777);
	int fd1 = open("test1.txt", O_CREAT | O_RDWR, 0777);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd1));
}*/
/*
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Open two files for reading
    FILE *file1 = fopen("test.txt", "r");
    FILE *file2 = fopen("test1.txt", "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening files");
        return 1;
    }

    // Read the first file line by line
    printf("Contents of test1.txt:\n");
    char *line;
    while ((line = get_next_line(fileno(file1))) != NULL) {
        printf("%s", line);
        free(line);  // Don't forget to free the memory after use!
    }

    // Read the second file line by line
    printf("\nContents of test2.txt:\n");
    while ((line = get_next_line(fileno(file2))) != NULL) {
        printf("%s", line);
        free(line);  // Don't forget to free the memory after use!
    }

    // Close the files after reading
    fclose(file1);
    fclose(file2);

    return 0;
}

*/
