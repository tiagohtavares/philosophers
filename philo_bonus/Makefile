# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 19:49:40 by ttavares          #+#    #+#              #
#    Updated: 2023/05/24 11:27:51 by ttavares         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc -Wall -Wextra -Werror
RM	= rm -f
TH	= -fsanitize=thread

SRC = main.c philo.c check_args.c init.c utils.c

OBJS = $(SRC:.c=.o)

NAME = philo_bonus

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -pthread  $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)
fclean:	clean
	$(RM) $(NAME)

re:	fclean all

