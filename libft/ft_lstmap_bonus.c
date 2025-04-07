/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:29:07 by yunseo            #+#    #+#             */
/*   Updated: 2024/03/01 17:34:03 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*tmp;
	void	*tmp_content;

	if (!lst || !f || !del)
		return (NULL);
	start = NULL;
	while (lst != NULL)
	{
		tmp_content = f(lst->content);
		tmp = ft_lstnew(tmp_content);
		if (!tmp || !tmp_content)
		{
			if (!tmp)
				del(tmp_content);
			if (!tmp_content)
				free(tmp);
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, tmp);
		lst = lst->next;
	}
	return (start);
}
