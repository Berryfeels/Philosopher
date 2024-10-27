# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 15:58:42 by stdi-pum          #+#    #+#              #
#    Updated: 2024/10/22 18:37:39 by stdi-pum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = philo

# Compiler
CC      = cc
CFLAGS  = -g -Werror -Wextra -Wall -fsanitize=address
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
#OBJS = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

# Rule to create object directories
$(OBJ_PATH):
	@echo "Creating object directories..."
	@mkdir -p	$(OBJ_PATH)

# Object files
OBJS = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))


# Rules
all: $(NAME)

# Create .o files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@mkdir -p $(dir $@)
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
	$(RM)  $(OBJS)

# Clean everything including executables
fclean: clean
	@echo "Removing executables and libraries..."
	$(RM) $(NAME)
	@rm -rf $(OBJ_PATH)

# Rebuild everything
re: fclean all

.PHONY: all re clean fcleanc