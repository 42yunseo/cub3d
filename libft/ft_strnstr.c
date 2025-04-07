/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:21:46 by yunseo            #+#    #+#             */
/*   Updated: 2024/02/29 18:49:54 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		is_find;

	if (*little == '\0')
		return ((char *)big);
	while (len-- && *big != '\0')
	{
		i = 0;
		is_find = 1;
		while ((little[i] != '\0' && big[i] != '\0') && is_find)
		{
			if (little[i] != big[i] || i > len)
				is_find = 0;
			i++;
		}
		if (is_find && little[i] == '\0')
			return ((char *)big);
		big++;
	}
	return (0);
}
