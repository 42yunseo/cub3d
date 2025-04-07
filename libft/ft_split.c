/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyungyo <seoyungyo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:51:21 by yunseo            #+#    #+#             */
/*   Updated: 2024/03/08 19:39:25 by seoyungyo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			cnt++;
		i++;
	}
	return (cnt);
}

char	*make_word(char const *s, char c, size_t *idx)
{
	char	*tmp;
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	*idx += i;
	ft_strlcpy(tmp, s, i + 1);
	return (tmp);
}

char	**free_all(char **ptr, int i)
{
	while (i >= 0)
		free(ptr[i--]);
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	len;
	size_t	i;
	size_t	idx;

	if (s == NULL)
		return (NULL);
	i = 0;
	idx = 0;
	len = count_words(s, c);
	ptr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		while (s[idx] == c)
			idx++;
		ptr[i] = make_word(s + idx, c, &idx);
		if (!ptr[i])
			return (free_all(ptr, i));
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
