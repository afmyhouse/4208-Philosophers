# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 13:50:35 by antoda-s          #+#    #+#              #
#    Updated: 2023/11/15 00:23:02 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name:
NAME			=	philo

# Directories:
OBJSDIR 		= 	build/

# Compiler:
CC				=	cc
CF				=	-Wall -Wextra -Werror
CS				=	-fsanitize=thread
CT				=	-pthread

# Sources:
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

# Objects:
OBJS			=	$(FILES:.c=.o)
#OBJS = $(addprefix $(OBJSDIR), $(FILES:.c=.o))

#Colors:
GRN		=	\e[38;5;118m
YLW		=	\e[38;5;226m
RED		=	\e[38;5;196m
BLU		=	\e[38:5:31m
WHT		=	\e[0m
CYN		:= \33[1;36m
RESET	:= \033[0m
BOLD	:= \033[1m

# Default rule
all: $(NAME)

# Rule to build the program
$(NAME): $(OBJS)
	@printf "\n=> $(GRN)objects$(WHT) ready!$(WHT)\n"
	@printf "$(CYN)Generating $(NAME) executable...$(WHT)\n"
	@$(CC) $(CF) $(CS) $(CT) $(OBJS) -o $(NAME)
	@printf "=> $(GRN)$(NAME)$(WHT) ready!\n"

# Rule to build object files from source files
%.o: %.c
# %.o: %.c
	@$(CC) $(CF) $(TC) -c $< -o $@
	@printf "$(CYN)██$(WHT)"

# Rule to clean objects
clean:
	@printf "=> Cleaning $(GRN)object files <*.o>$(WHT) from project...\n"
	@$(RM) $(OBJS)
#	$(RM) -r $(OBJSDIR)

# Rule to clean objects and executable
fclean:	clean
	@printf "=> Cleaning $(GRN)executable <$(NAME)>$(WHT) from project...\n"
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
