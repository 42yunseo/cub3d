# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 19:43:35 by yunseo            #+#    #+#              #
#    Updated: 2025/03/31 19:43:35 by yunseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
lFLAGS = -lm -lmlx -lXext -lX11 -lft
LFLAGS = -Lminilibx-linux -Llibft
IFLAGS = -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR)

MLX_DIR = ./minilibx-linux
LIBFT_DIR = ./libft
GNL_DIR = $(LIBFT_DIR)/get_next_line

MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = 	main.c \
		info.c \
		element.c \
		texture.c \
		color.c \
		map.c \
		player.c \
		utils.c 


OBJS = $(SRCS:.c=.o)

all : $(LIBFT) $(MLX) $(NAME)

$(LIBFT) :
	make -sC $(LIBFT_DIR)

$(MLX) :
	make -sC $(MLX_DIR)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(lFLAGS) $(LFLAGS) $(IFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

clean :
	rm -rf $(OBJS)
	make -sC $(LIBFT_DIR) clean
	make -sC  $(MLX_DIR) clean

fclean :
	make clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)
	rm -rf $(MLX)

re :
	make fclean
	make all

.PHONY=all clean fclean re
