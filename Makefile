# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lribette <lribette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 17:27:08 by lribette          #+#    #+#              #
#    Updated: 2024/01/21 11:00:45 by lribette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SOURCES = childs.c ft_split.c main.c pipes.c search_path.c 

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
PRINTF = ./ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJECTS) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJECTS) $(PRINTF) -o $(NAME)

$(PRINTF):
	make -C ./ft_printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	make clean -C ./ft_printf

fclean: clean
	$(RM) $(NAME) $(PRINTF)

re: fclean all

.PHONY: all clean fclean re
