# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 20:34:46 by nmikuka           #+#    #+#              #
#    Updated: 2025/09/12 20:32:07 by nmikuka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_DIR := obj

# Compiler and flags
CC := @cc
CFLAGS := -Wall -Wextra -Werror  -g -O0 -pthread

# Library name
NAME := philo

# Source and object files
SRC_FILES := main.c init.c run.c take_forks.c death_monitor.c philos_logic.c \
			cleanup.c utils_safe.c utils_ft.c utils_time.c
OBJ_FILES := $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@  -lpthread
	@$(MAKE) print_random_art

print_random_art:
	@bash -c '\
		choice=$$((RANDOM % 3)); \
		if [ $$choice -eq 0 ]; then \
			$(MAKE) print_spaghetti_bowl; \
		elif [ $$choice -eq 1 ]; then \
			$(MAKE) print_brain; \
		else \
			$(MAKE) print_death; \
		fi'

print_spaghetti_bowl:
	@echo "                ██      ██      ██"
	@echo "                  ██    ██        ██"
	@echo "                    ██  ██          ██"
	@echo "                    ██    ██        ██"
	@echo "                  ██        ██    ██"
	@echo "                            ██  ██"
	@echo "                          ██"
	@echo ""
	@echo "        ██████        ████████████"
	@echo "      ██      ██    ██            ██"
	@echo "    ██    ████  ████    ████████    ██              ████"
	@echo "  ██    ██    ████    ██        ██    ██████      ██    ██"
	@echo "  ██  ██  ██████    ██    ████    ██    ██  ██  ██        ██"
	@echo "██  ██  ██  ██    ██    ██    ██    ██    ██  ██          ██"
	@echo "████████████████████████████████████████████████████    ██"
	@echo "  ██████████████████████████████████████      ████    ██"
	@echo "  ██████████████████████████████████████      ████  ██"
	@echo "    ██████████████████████████████████      ████    ██"
	@echo "      ██████████████████████████████    ██████        ██"
	@echo "        ██████████████████████████  ████████"
	@echo "            ████████████████████████████"
	@echo "\n           Philosophers are ready to eat!"
	

print_brain:
	@echo "              ████████     ████████   ████████"
	@echo "          ████        █████        ███        ████"
	@echo "      ██████      ████      ████    ██      ██    ████"
	@echo "      ██  ████    ██            ██          ██  ██  ████"
	@echo "    ██          ██████        ████   ███████  ██      ██"
	@echo "    ██        ████  ██████    ██              ██  ██████"
	@echo "  ██          ██        ██                      ██      ██"
	@echo "  ██  ██    ████          ██    ██    ██████████        ██"
	@echo "██    ████  ████      ██        ████████   ██    ████  ████"
	@echo "██      ██████  ████  ████                       ██      ██"
	@echo "████      ██            ██              ██       ██    ████"
	@echo "██        ██        ██████    ████      ██         ██  ██"
	@echo "██  ██    ██        ██          ████    ████       █████"
	@echo "██  ████████      ████          ████      ████   ████"
	@echo "██        ██              ████████          ████████"
	@echo "████    ██████  ██████        ██  ████████████  ██"
	@echo "  ████      ██████          ██████          ██    ██"
	@echo "      ████    ██      ██████                  ██    ██"
	@echo "        ████████████████                        ██████"
	@echo "\n           Philosophers are ready to think!"

print_death:
	@echo "                ████████████████████████"
	@echo "          ██████                        ████"
	@echo "        ██                                  ██"
	@echo "      ██                                    ██"
	@echo "    ██                                        ██"
	@echo "  ██                                          ██"
	@echo "██    ██████            ████████              ██"
	@echo "██  ██████████        ████████████            ██"
	@echo "██  ██████████        ████████████            ██"
	@echo "██  ██████████        ████████████            ██"
	@echo "██  ██████████        ████████████            ██"
	@echo "██    ██████            ████████              ██"
	@echo "██                                            ██"
	@echo "  ██          ██  ██                        ██  "
	@echo "  ██          ██  ██                        ██  "
	@echo "    ██                      ██            ██"
	@echo "    ██                      ████        ██"
	@echo "    ██                      ██  ████████"
	@echo "    ██    ██    ██    ██    ██"
	@echo "    ██    ██    ██    ██    ██"
	@echo "      ████  ████  ████  ████"
	@echo "\n           Philosophers are ready to die!"


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