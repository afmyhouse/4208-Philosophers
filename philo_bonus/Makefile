# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 17:39:58 by antoda-s          #+#    #+#              #
#    Updated: 2023/11/13 19:16:41 by antoda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name:
NAME			=	philo_bonus

# Directories
OBJSDIR 		= 	build/

# Compilation
CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror

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

all:	$(NAME)

$(NAME): $(OBJS) build
	@printf "$(GRN)Objects$(WHT) ready!$(WHT)\n\n"
	@printf "\n$(CYN)Generating $(NAME) executable...$(WHT)\n"
	$(CC) $(CF) $(OBJS) -lpthread -o $(NAME)
	@printf "$(GRN)$(NAME)$(WHT) ready!\n\n"

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
