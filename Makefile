# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 19:49:40 by ttavares          #+#    #+#              #
#    Updated: 2023/05/10 12:13:56 by ttavares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc -Wall -Wextra -Werror
RM	= rm -f

SRC = main.c philo.c check_args.c init.c utils.c

OBJS = $(SRC:.c=.o)

NAME = philo

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -pthread $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
fclean:	clean
	$(RM) $(NAME)

re:	fclean all

