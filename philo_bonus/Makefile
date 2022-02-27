# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#              #
#    Updated: 2022/02/24 22:13:15 by gkintana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus

INC_DIR		=	include
SRC_DIR		=	sources
OBJ_DIR		=	objects

SRCS		=	death_monitor.c \
				events.c \
				find_errors.c \
				modified_atoi.c \
				philosophers_bonus.c \
				print_events.c \
				print_utils.c \
				process_and_semaphores.c \
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
			@echo $(DEFAULT)$(GREEN)"Philosophers_Bonus Ready 🤯"$(DEFAULT)

bonus:		all

clean:
			@$(RM) $(OBJ_DIR)
			@echo $(RED)"Deleted philosophers_bonus object files & object folder 🗃️"$(DEFAULT)

fclean:		clean
			@$(RM) $(NAME)
			@echo $(RED)"Deleted philosophers_bonus executable 😱"$(DEFAULT)

norm:
			@echo $(DEFAULT)$(YELLOW_BU)"philosophers_bonus .c files"$(DEFAULT)$(CYAN)
			@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
			@echo $(DEFAULT)$(YELLOW_BU)"philosophers_bonus .h files"$(DEFAULT)$(CYAN)
			@norminette -R CheckDefine $(INC_DIR)/*.h

re:			fclean all

.PHONY:		all clean fclean re bonus
