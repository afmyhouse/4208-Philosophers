# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 13:50:35 by antoda-s          #+#    #+#              #
#    Updated: 2023/11/13 14:29:49 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
OBJSDIR 		= 	build/

CC				=	cc
RM				=	rm -f
CF				=	-Wall -Wextra -Werror -fsanitize=thread

FILES			=	main.c
FILES			+=	time.c
FILES			+=	init.c
FILES			+=	mutex.c
FILES			+=	loop.c
FILES			+=	lifeguard.c
FILES			+=	forks.c
FILES			+=	free.c
FILES			+=	ft_tools.c
FILES			+=	threads.c

#OBJS			=	$(FILES:.c=.o)
OBJS = $(addprefix $(OBJSDIR), $(FILES:.c=.o))

#Colors:
GRN		=	\e[38;5;118m
YLW		=	\e[38;5;226m
RED		=	\e[38;5;196m
BLU		=	\e[38:5:31m
WHT		=	\e[0m
CYN		:= \33[1;36m
RESET	:= \033[0m
BOLD	:= \033[1m

all: $(NAME)

$(NAME): $(OBJS) build
	@printf "$(GRN)Objects$(WHT) ready!$(WHT)\n\n"
	@printf "\n$(CYN)Generating $(NAME) executable...$(WHT)\n"
	$(CC) $(CF) $(OBJS) -lpthread -o $(NAME)
	@printf "$(GRN)$(NAME)$(WHT) Ready!\n\n"

build:
	@mkdir -p $(OBJSDIR)
	@printf "\n$(CYN)Compiling source files...$(WHT)\n"

$(OBJSDIR)%.o: %.c | build
	$(CC) $(CF) -c $< -o $@

clean:
	@printf "\nCleaning all $(GRN)object files$(WHT) from project...\n"
	$(RM) $(OBJS)
	$(RM) -r $(OBJSDIR)

post:
	@printf "\nCleaning $(GRN)objects and executables$(WHT) from project...\n"

fclean:	post clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re build post
