# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 17:27:03 by sabdulki          #+#    #+#              #
#    Updated: 2024/10/01 13:40:03 by sabdulki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_GNL =	./src/get_next_line/get_next_line.c \
			./src/get_next_line/get_next_line_utils.c

SRC_P = 	./src/parsing/parsing.c \
			./src/parsing/fill_sprites.c \
			./src/parsing/check_file.c \
			./src/parsing/list.c \
			./src/parsing/map.c \
			./src/parsing/map_edges.c \
			./src/parsing/nbrs_check.c \
			./src/parsing/init_lists.c \
			./src/parsing/free_lists.c
			
			

SRC_U = 	./src/utils/utils_message.c \
			./src/utils/utils.c \
			./src/utils/utils_color.c \
			./src/utils/utils_map.c

SRCS_S =	./main.c 

SRCS = $(SRCS_S) $(SRC_GNL) $(SRC_P) $(SRC_U)
OBJS = $(SRCS:.c=.o)

# separate folder for .o files
# OBJS_DIR = obj
# OBJS := $(addprefix $(OBJS_DIR)/, $(notdir $(OBJS)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 --debug 
# -fsanitize=address

LIBFT_CREATE = cd ./src/Libft && make  # Add this line to indicate the library path and name
LIBFT_A = src/Libft/libft.a
# special compilation for macOs or Linux OS
OS = $(shell uname)

ifeq ($(OS), Linux)
	CFLAGS += -I/usr/include -Imlx_linux -O3
	LDFLAGS += -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

else ifeq ($(OS), Darwin)
	CFLAGS += -Imlx -I./mlx_mac
	LDFLAGS += -L./mlx_mac -lmlx -framework OpenGL -framework AppKit -ldl -lpthread
endif

# Variables for colored output
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m  # No Color

# create the specified folder and move .o objects there
# $(OBJS_DIR):
# 	mkdir -p $(OBJS_DIR)

# $(OBJS_DIR)/%.o: ./src/%.c | $(OBJS_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@


# create the executable cub3d
$(NAME): $(OBJS)
# cd ./src/Libft && make
# $(LIBFT_CREATE)
	$(MAKE) -C src/Libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)
	@if [ $$? -eq 0 ]; then \
		echo -e "$(GREEN)Build successful!$(NC)"; \
	else \
		echo -e "$(RED)Build failed!$(NC)"; \
	fi

all: $(NAME)

clean :
	rm -f $(OBJS)
	$(MAKE) -C src/Libft clean
# cd ./src/Libft && make clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C src/Libft fclean
# cd ./src/Libft && make fclean

re : fclean all

.PHONY : all clean fclean re