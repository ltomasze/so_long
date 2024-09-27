# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 13:01:15 by ltomasze          #+#    #+#              #
#    Updated: 2024/09/27 15:01:38 by ltomasze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SOURCES = src/get_next_line_utils.c src/get_next_line.c
OBJECTS = $(SOURCES:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
FT_PRINTF = ft_printf/libftprintf.a
LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a

all: $(NAME)

$(FT_PRINTF):
	$(MAKE) -C ft_printf

$(LIBFT):
	$(MAKE) -C libft

$(MINILIBX):
	$(MAKE) -C minilibx-linux

$(NAME): $(OBJECTS) $(FT_PRINTF) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(FT_PRINTF) $(LIBFT) $(MINILIBX) -o $(NAME) -lXext -lX11 -lm -lz -D LINUX -no-pie

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C ft_printf clean
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ft_printf fclean
	$(MAKE) -C libft fclean
	$(MAKE) -C minilibx-linux clean

re: fclean all

full: all clean

.PHONY: all clean fclean re full