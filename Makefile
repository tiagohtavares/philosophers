# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 19:49:40 by ttavares          #+#    #+#              #
#    Updated: 2023/04/26 12:13:24 by ttavares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc -Wall -Wextra -Werror
RM	= rm -f

SRC = philo.c

OBJS = $(SRC:.c=.o)

NAME = philo

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
fclean:	clean
	$(RM) $(NAME)

re:	fclean all
