# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunseo <yunseo@student.42gyeongsan.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 03:55:21 by yunseo            #+#    #+#              #
#    Updated: 2024/03/08 21:06:12 by yunseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iget_next_line
AR = ar

GNL_DIR = ./get_next_line

LIBFT_SRCS = 	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c

LIBFT_SRCS_B =  ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

GNL_SRCS =  ${GNL_DIR}/get_next_line.c \
			${GNL_DIR}/get_next_line_utils.c

LIBFT_OBJS = ${LIBFT_SRCS:.c=.o}
LIBFT_OBJS_B = ${LIBFT_SRCS_B:.c=.o}

GNL_OBJS = ${GNL_SRCS:.c=.o}

all : ${NAME}

${NAME} : ${LIBFT_OBJS} ${LIBFT_OBJS_B} ${GNL_OBJS}
	${AR} -rc ${NAME} ${LIBFT_OBJS} ${LIBFT_OBJS_B} ${GNL_OBJS}

%.o : %.c
	${CC} ${CFLAGS} -c $^ -o $@ ${IFLAGS}

clean :
	rm -f ${LIBFT_OBJS} ${LIBFT_OBJS_B} ${GNL_OBJS}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re
