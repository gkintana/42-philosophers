# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#              #
#    Updated: 2022/02/22 14:05:01 by gkintana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

INC_DIR		=	include
SRC_DIR		=	sources
OBJ_DIR		=	objects

SRCS		=	death_monitor.c \
				events.c \
				find_errors.c \
				modified_atoi.c \
				mutex_and_threads.c \
				philosophers.c \
				print_events.c \
				print_utils.c \
				structs_and_time.c

OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:%c=%o))

CC			=	gcc
CFLAGS		=	-pthread -g -Wall -Wextra -Werror
LIB_AR		=	ar rcs
RM			=	rm -rf

DEFAULT		=	"\033[0m"
RED			=	"\033[0;31m"
GREEN		=	"\033[1;32m"
YELLOW		=	"\033[0;33m"
YELLOW_BU	=	"\033[1;4;33m"
CYAN		=	"\033[3;36m"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
			@mkdir -p objects
			@printf $(CYAN)
			$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $@
			@echo $(DEFAULT)$(GREEN)"Philosophers Ready 🤯"$(DEFAULT)

bonus:		all

clean:
			@$(RM) $(OBJ_DIR)
			@echo $(RED)"Deleted philosophers object files & object folder 🗃️"$(DEFAULT)

fclean:		clean
			@$(RM) $(NAME)
			@echo $(RED)"Deleted philosophers executable 😱"$(DEFAULT)

norm:
			@echo $(DEFAULT)$(YELLOW_BU)"philosophers .c files"$(DEFAULT)$(CYAN)
			@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
			@echo $(DEFAULT)$(YELLOW_BU)"philosophers .h files"$(DEFAULT)$(CYAN)
			@norminette -R CheckDefine $(INC_DIR)/*.h

re:			fclean all

.PHONY:		all clean fclean re bonus
