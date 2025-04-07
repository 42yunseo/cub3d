/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyungyo <seoyungyo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:49:58 by yunseo            #+#    #+#             */
/*   Updated: 2024/03/08 18:29:36 by seoyungyo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;

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
