# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 00:11:12 by natferna          #+#    #+#              #
#    Updated: 2025/05/16 00:31:50 by natferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -I.

SRCS = main.c src/die.c src/eat.c src/init.c \
       src/philosophers.c src/sleep.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
