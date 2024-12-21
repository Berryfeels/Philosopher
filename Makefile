# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 15:58:42 by stdi-pum          #+#    #+#              #
#    Updated: 2024/12/21 17:13:19 by stdi-pum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = philo

# Compiler
CC      = gcc
CFLAGS  = -g -O0 -o -Werror -Wextra -Wall -lpthread #-fsanitize=thread
# Includes
INC         =   -I./include/ \


# Source directories
SRC_PATH    = src/

# search for .c files in subfolders
SRC = $(shell find $(SRC_PATH) -type f -name "*.c")
#$(shell find $(SRC_PATH) -type f -name "*.c")

# Object directories
OBJ_PATH = src/obj/

# sets the folders for .o files mimiking the src path
OBJS = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

# Create the object directories if they don't exist
$(OBJ_PATH):
	@echo "Creating object directories..."
	@mkdir -p $(OBJ_PATH)
	
# Create .o files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@echo "Compiling $< to $@"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Build executable
$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	@echo "Cogito ergo sum. Sed est verum quod cogito?"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Clean object files
clean:
	@echo "Removing .o object files..."
	$(RM) $(OBJS)

# Clean everything including executables
fclean: clean
	@echo "Removing executables and libraries..."
	$(RM) $(NAME)
	@rm -rf $(OBJ_PATH)

# Rules
all: $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all re clean fcleanc