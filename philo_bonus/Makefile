# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 13:51:02 by antoda-s          #+#    #+#              #
#    Updated: 2023/11/07 13:51:06 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror

SRCS			=	philo_main_bonus.c philo_readinput_bonus.c \
					philo_initializer_bonus.c philo_routine_bonus.c \
					philo_bigbrother_bonus.c philo_waiter_bonus.c \
					philo_free_bonus.c philo_utils_bonus.c \
					philo_time_bonus.c \

OBJS			=	$(SRCS:.c=.o)

NAME			=	philo_bonus

all:				$(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

clean:
					$(RM) $(OBJS)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all
