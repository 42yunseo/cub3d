/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyungyo <seoyungyo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:45:07 by yunseo            #+#    #+#             */
/*   Updated: 2024/04/14 12:56:06 by seoyungyo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	char	*tmp;

	if (s == NULL)
		return (NULL);
	tmp = (char *)s;
	while (*tmp != '\0')
	{
		if (*tmp == (unsigned char) c)
			return (tmp);
		tmp++;
	}
	if ((unsigned char) c == 0)
		return (tmp);
	return (0);
}

char	*gnl_strjoin(char *readline, char *buf)
{
	char	*ptr;
	int		i;
	int		j;
	int		len;

	if (readline == NULL)
		readline = gnl_strdup("");
	if (readline == NULL || buf == NULL)
		return (NULL);
	len = gnl_strlen(readline) + gnl_strlen(buf);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (readline[i] != '\0')
	{
		ptr[i] = readline[i];
		i++;
	}
	j = 0;
	while (buf[j] != '\0')
		ptr[i++] = buf[j++];
	ptr[i] = '\0';
	free(readline);
	return (ptr);
}

char	*gnl_strdup(const char *s)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	len = gnl_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
