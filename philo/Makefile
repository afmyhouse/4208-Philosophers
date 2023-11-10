# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 13:50:35 by antoda-s          #+#    #+#              #
#    Updated: 2023/11/09 14:57:54 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address

SRCS			=	main.c argparse.c time.c init.c mutex.c routine.c \
					lifeguard.c waiter.c free.c utils.c \

OBJS			=	$(SRCS:.c=.o)

NAME			=	philo

all:				$(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

clean:
					$(RM) $(OBJS)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all
