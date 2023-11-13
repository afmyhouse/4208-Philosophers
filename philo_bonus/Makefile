# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 18:55:14 by amenses-          #+#    #+#              #
#    Updated: 2023/11/13 13:39:07 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror

SRCS			=	main_bonus.c init_bonus.c loop_bonus.c \
					lifeguard_bonus.c waiter_bonus.c \
					free_bonus.c ft_tools_bonus.c time_bonus.c \

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
