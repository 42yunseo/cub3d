/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyungyo <seoyungyo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:11:11 by yunseo            #+#    #+#             */
/*   Updated: 2024/03/08 19:10:54 by seoyungyo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = NULL;
	while (*s != '\0')
	{
		if (*s == (unsigned char) c)
			tmp = (char *) s;
		s++;
	}
	if ((unsigned char) c == 0)
		return ((char *) s);
	return (tmp);
}
