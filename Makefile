# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 16:11:01 by zrebhi            #+#    #+#              #
#    Updated: 2023/04/20 19:56:02 by zrebhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		   :=   philo

INC            :=   philo.h
INC_DIR        :=   includes/

HEADERS        := $(addprefix $(INC_DIR), $(INC))

SRC_DIR        :=   sources/
SRC            :=   utils/ft_atoi.c utils/ft_putstr_fd.c utils/ft_get_time.c \
					utils/ft_calloc.c \
					main.c initialization.c philosophers.c forks.c\

OBJ_DIR        :=    build/
OBJ            :=    $(SRC:%.c=$(OBJ_DIR)%.o)

# Compiler options
CC            :=    cc
CC_FLAGS      :=    -Wextra -Werror -Wall -pthread #-oFast -g -fsanitize=address

all: $(NAME)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "compiling: $<"
	@$(CC) $(CC_FLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJ) $(INC_DIR)/$(INC) Makefile
	@$(CC) $(CC_FLAGS) $(OBJ) -lreadline -o $@
	@echo "> philo Done! <"

# clean commands
clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "remove $(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
