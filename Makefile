# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/03 by lleineck                  #+#    #+#              #
#    Updated: 2026/04/03 by lleineck                 ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra -pthread
LDFLAGS			=	-pthread

SRCS			=	main.c \
					parsing.c \
					mutex.c \
					philosophers.c \
					utils.c \
					eaten.c \
					hecate.c

OBJS			=	$(SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o:			%.c philosophers.h
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

run_debug:		$(NAME)
				valgrind --leak-check=full --show-leak-kinds=all \
					--track-origins=yes --verbose ./$(NAME) 5 500 200 120 3
run_data: 		$(NAME)
				valgrind --tool=helgrind ./$(NAME) 5 800 200 100

.PHONY:			all clean fclean re run run_debug run_data
