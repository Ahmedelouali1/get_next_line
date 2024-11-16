/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmel-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:37:10 by ahmel-ou          #+#    #+#             */
/*   Updated: 2024/11/10 16:07:53 by ahmel-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_update(char *str)
{
	int		i;
	int		j;
	char	*scnd_str;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	scnd_str = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!scnd_str)
		return (free(str), NULL);
	i++;
	while (str[i] != '\0')
		scnd_str[j++] = str[i++];
	scnd_str[j] = '\0';
	free(str);
	return (scnd_str);
}

size_t	ft_newlinelengh(const char *s)
{
	size_t	lengh;

	lengh = 0;
	if (!s)
		return (0);
	while (s[lengh] != '\0' && s[lengh] != '\n')
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
			return (free(buf), NULL);
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
	static char	*svariable;
	char		*line;
	char		*second_str;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	svariable = ft_read(buf, svariable, fd);
	if (!svariable)
		return (NULL);
	if (*svariable == '\0')
		return (free(svariable), svariable = 0);
	second_str = svariable;
	line = ft_substr(second_str, 0, ft_newlinelengh(second_str) + 1);
	if (!*line)
		return (free(line), NULL);
	svariable = ft_update(svariable);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int main() {
    // Open the file test1.txt for reading
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the file line by line
    char *line;
    while ((line = get_next_line(fileno(file))) != NULL) {
        // Print the line
        printf("%s", line);
        free(line);  // Don't forget to free the memory after use!
    }

    // Close the file after reading
    fclose(file);
    return 0;
}
*/
