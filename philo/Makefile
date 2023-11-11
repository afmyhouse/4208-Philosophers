# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 13:50:35 by antoda-s          #+#    #+#              #
#    Updated: 2023/11/11 15:52:29 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc
RM				=	rm -f
CF				=	-Wall -Wextra -Werror -fsanitize=memory -fPIE -pie
CFS				=	-Wall -Wextra -Werror -fsanitize=thread
SRCS			=	main.c argparse.c time.c init.c mutex.c routine.c \
					lifeguard.c waiter.c free.c ft_tools.c \

OBJS			=	$(SRCS:.c=.o)

NAME			=	philo

all:				$(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CF) $(OBJS) -pthread -o $(NAME)

msani:				$(OBJS)
					$(CC) $(CFS) -g $(OBJS) -pthread -o $(NAME)

clean:
					$(RM) $(OBJS)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all
