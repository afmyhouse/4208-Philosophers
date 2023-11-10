# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 13:51:02 by antoda-s          #+#    #+#              #
#    Updated: 2023/11/09 15:15:12 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror

SRCS			=	main_bonus.c argparse_bonus.c \
					init_bonus.c routine_bonus.c \
					lifeguard_bonus.c waiter_bonus.c \
					free_bonus.c utils_bonus.c \
					time_bonus.c \

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
