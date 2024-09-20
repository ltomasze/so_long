# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltomasze <ltomasze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 13:01:15 by ltomasze          #+#    #+#              #
#    Updated: 2024/09/20 14:33:06 by ltomasze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGRAM = so_long
NAME = $(PROGRAM).a
MAIN = so_long.c
SOURCES = 
OBJECTS = $(SOURCES:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
LIBFT = Libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a

all: $(PROGRAM)

$(LIBFT):
	$(MAKE) -C Libft

$(MINILIBX):
	$(MAKE) -C minilibx-linux

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(PROGRAM): $(MINILIBX) $(LIBFT) $(NAME)
	$(CC) $(CFLAGS) $(MAIN) $(NAME) $(LIBFT) $(MINILIBX) -o $(PROGRAM) -lXext -lX11

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C Libft clean
	$(MAKE) -C minilibx-linux clean

fclean: clean
	rm -f $(NAME) $(PROGRAM)
	$(MAKE) -C Libft fclean
	$(MAKE) -C minilibx-linux clean

re: fclean all

full: all clean

.PHONY: all clean fclean re full