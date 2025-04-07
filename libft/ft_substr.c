/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyungyo <seoyungyo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:14:36 by yunseo            #+#    #+#             */
/*   Updated: 2024/03/08 20:26:44 by seoyungyo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;
	size_t	ptr_len;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	i = 0;
	if (ft_strlen(s) - start < len)
		ptr_len = ft_strlen(s) - start;
	else
		ptr_len = len;
	ptr = (char *)malloc(sizeof(char) * (ptr_len + 1));
	if (!ptr)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
