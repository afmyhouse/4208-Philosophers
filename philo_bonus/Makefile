# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 17:39:58 by antoda-s          #+#    #+#              #
#    Updated: 2023/11/15 00:26:24 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name:
NAME			=	philo_bonus

# Directories
OBJSDIR 		= 	build/

# Compilation
CC				=	cc
CF				=	-Wall -Wextra -Werror
CS				=	-fsanitize=thread
CT				=	-pthread

# Sources
FILES			=	main_bonus.c
FILES			+=	init_bonus.c
FILES			+=	loop_bonus.c
FILES			+=	lifeguard_bonus.c
FILES			+=	forks_bonus.c
FILES			+=	free_bonus.c
FILES			+=	ft_tools_bonus.c
FILES			+=	time_bonus.c
FILES			+=	process_bonus.c

# Objects
OBJS			=	$(FILES:.c=.o)
#OBJS = $(addprefix $(OBJSDIR), $(FILES:.c=.o))

# Colors:
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
	@$(CC) $(CF) -c $< -o $@
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