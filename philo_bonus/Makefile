# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 20:34:46 by nmikuka           #+#    #+#              #
#    Updated: 2025/09/13 12:17:03 by nmikuka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_DIR := obj

# Compiler and flags
CC := @cc
CFLAGS := -Wall -Wextra -Werror

# Library name
NAME := philo_bonus

# Source and object files
SRC_FILES := main.c run.c philos_logic.c actions.c semaphores.c \
			utils_ft.c utils_time.c
OBJ_FILES := $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@  -lpthread
	@echo "Philosophers are ready to die!"

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re