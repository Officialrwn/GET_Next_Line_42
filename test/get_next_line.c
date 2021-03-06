/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 08:59:13 by leo               #+#    #+#             */
/*   Updated: 2021/12/20 16:22:34 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	getlinefromstatic(int fd, char **stat_str, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while (stat_str[fd][i] != '\n')
		i++;
	*line = ft_strsub(stat_str[fd], 0, i);
	temp = ft_strdup(ft_strchr(stat_str[fd], '\n') + 1);
	ft_strdel(&stat_str[fd]);
	stat_str[fd] = temp;
	return (1);
}

static int	getlastline(int fd, char **stat_str, char **line)
{
	int	i;

	i = 0;
	*line = ft_strdup(stat_str[fd]);
	ft_strdel(&stat_str[fd]);
	if (*line[0] != '\0')
		i = 1;
	return (i);
}

static int	cpytostatic(int fd, char **stat_str, char *buffer)
{
	char	*temp;

	if (stat_str[fd] != NULL)
	{
		temp = ft_strjoin(stat_str[fd], buffer);
		ft_strdel(&stat_str[fd]);
		stat_str[fd] = temp;
	}
	else
		stat_str[fd] = ft_strdup(buffer);
	return (2);
}

int	get_next_line(const int fd, char **line)
{
	static char	*stat_str[FD_SIZE];
	char		*buffer;
	int			i;

	i = 2;
	buffer = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || fd >= FD_SIZE)
		i = -1;
	while (i > 0)
	{
		if (stat_str[fd] != NULL && ft_strchr(stat_str[fd], '\n') != NULL)
			i = (getlinefromstatic(fd, stat_str, line));
		if (i == 1)
			break ;
		i = read(fd, buffer, BUFF_SIZE);
		if (i >= 0)
			buffer[i] = '\0';
		if (i > 0)
			i = cpytostatic(fd, stat_str, buffer);
		if (i == 0 && stat_str[fd] != NULL)
			i = (getlastline(fd, stat_str, line));
	}
	ft_strdel(&buffer);
	return (i);
}
