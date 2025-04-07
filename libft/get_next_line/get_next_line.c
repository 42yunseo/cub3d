/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyungyo <seoyungyo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:34:02 by yunseo            #+#    #+#             */
/*   Updated: 2024/04/14 12:45:43 by seoyungyo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_newreadline(char *readline)
{
	char	*tmp;

	if (!gnl_strchr(readline, '\n'))
	{
		free(readline);
		return (NULL);
	}
	tmp = gnl_strdup(gnl_strchr(readline, '\n') + 1);
	if (tmp == NULL)
		return (NULL);
	free(readline);
	return (tmp);
}

char	*ft_nextline(char *readline)
{
	int		i;
	int		len;
	char	*tmp;

	if (*readline == '\0')
		return (NULL);
	i = 0;
	while (readline[i] != '\0' && readline[i] != '\n')
		i++;
	if (readline[i] == '\n')
		i++;
	len = i;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tmp[i] = readline[i];
		i++;
	}
	tmp[len] = '\0';
	return (tmp);
}

char	*ft_readline(char *readline, int fd)
{
	char	*buf;
	int		rd;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	rd = 1;
	while (!gnl_strchr(readline, '\n') && rd != 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buf);
			free(readline);
			return (NULL);
		}
		buf[rd] = '\0';
		readline = gnl_strjoin(readline, buf);
	}
	free(buf);
	return (readline);
}

char	*get_next_line(int fd)
{
	char		*nextline;
	static char	*readline;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	readline = ft_readline(readline, fd);
	if (readline == NULL)
		return (NULL);
	nextline = ft_nextline(readline);
	readline = ft_newreadline(readline);
	return (nextline);
}
