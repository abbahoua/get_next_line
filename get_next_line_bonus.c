/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbahoua <abbahoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 01:53:32 by abbahoua          #+#    #+#             */
/*   Updated: 2021/12/22 16:38:00 by abbahoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*the_rest(char *line)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	str = ft_substr(line, (i + 1), ft_strlen(line));
	free(line);
	line = NULL;
	return (str);
}

char	*read_one_line(char **line)
{
	int	i;

	i = 0;
	if (line[0][i] == '\0')
	{
		free(*line);
		*line = NULL;
		return (NULL);
	}
	while (line[0][i] != '\n' && line[0][i] != '\0')
		i++;
	return (ft_substr(*line, 0, (i + 1)));
}

char	*read_lines(int fd, char *line)
{
	char	*str;
	ssize_t	i;

	i = 1;
	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (0);
	if (!line)
		line = ft_strdup("");
	while (!ft_strchr(line) && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i < 0)
		{
			free(str);
			free(line);
			line = NULL;
			return (NULL);
		}
		str[i] = '\0';
		line = ft_strjoin(line, str);
	}
	free(str);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = read_lines(fd, line[fd]);
	if (line[fd] == NULL)
		return (NULL);
	str = read_one_line(&line[fd]);
	if (str == NULL)
		return (NULL);
	line[fd] = the_rest(line[fd]);
	return (str);
}
// #include <stdio.h>

// int	main()
//  {
//  	int fd1;
// 	int	fd2;
// 	int i = 0;

//  	fd1 = open("/Users/abbahoua/Desktop/get_next_line/42.txt", O_RDONLY);
// 	fd2 = open("/Users/abbahoua/Desktop/get_next_line/422.txt", O_RDONLY);
// 	while(i < 7)
// 	{
//  		printf("linestr : %s\n", get_next_line(fd2));
// 		 i++;
// 	}
//  }
