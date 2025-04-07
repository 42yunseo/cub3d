/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:06:04 by yunseo            #+#    #+#             */
/*   Updated: 2024/02/28 22:27:33 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ptr;
	int		negative;
	int		tmp;

	len = count_len(n);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	negative = 0;
	if (!ptr)
		return (NULL);
	if (n < 0)
		negative = 1;
	ptr[len] = '\0';
	while (len--)
	{
		tmp = (n % 10);
		if (tmp < 0)
			tmp = -tmp;
		ptr[len] = tmp + '0';
		n /= 10;
	}
	if (negative)
		ptr[0] = '-';
	return (ptr);
}
