# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chfederi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 19:32:43 by chfederi          #+#    #+#              #
#    Updated: 2022/03/25 19:32:46 by chfederi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_C = client

NAME_S = server

CC = gcc

SRC_C = client.c

SRC_S = server.c

HEADER = minitalk.h

OBJS_S = $(SRC_S:.c=.o)

OBJS_C = $(SRC_C:.c=.o)

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME_C) $(NAME_S)

$(NAME_S): $(HEADER) server.o
			$(CC) $(CFLAGS) server.o -o $(NAME_S)

$(NAME_C): $(HEADER) client.o
			$(CC) $(CFLAGS) client.o -o $(NAME_C)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME_S) $(NAME_C)

re: fclean all

.PHONY : all clean fclean re