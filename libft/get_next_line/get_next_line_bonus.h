/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyungyo <seoyungyo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:11:01 by yunseo            #+#    #+#             */
/*   Updated: 2024/04/14 21:38:33 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char		*get_next_line(int fd);
size_t		gnl_strlen(const char *s);
char		*gnl_strchr(const char *s, int c);
char		*gnl_strjoin(char *s1, char *s2);
char		*gnl_strdup(const char *s);

#endif
