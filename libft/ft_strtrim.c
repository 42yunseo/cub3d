/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:39:24 by yunseo            #+#    #+#             */
/*   Updated: 2024/02/28 21:50:29 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	while (is_set(s1[begin], set) && s1[begin] != '\0')
		begin++;
	end = ft_strlen(s1);
	while (is_set(s1[end - 1], set) && end > begin)
		end--;
	ptr = (char *)malloc(sizeof(char) * (end - begin + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1 + begin, end - begin + 1);
	return (ptr);
}
