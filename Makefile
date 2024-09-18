# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 17:27:03 by sabdulki          #+#    #+#              #
#    Updated: 2024/09/18 17:42:34 by sabdulki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_GNL =	./src/get_next_line/get_next_line.c \
			./src/get_next_line/get_next_line_utils.c

SRC_P = 	./src/parsing/parsing.c \
			./src/parsing/file_content.c \
			./src/parsing/check_file.c 
			
SRCS_S =	./src/main.c

SRCS = $(SRCS_S) $(SRC_GNL) $(SRC_P)
OBJS = $(SRCS:.c=.o)

# separate folder for .o files
# OBJS_DIR = obj
# OBJS := $(addprefix $(OBJS_DIR)/, $(notdir $(OBJS)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address --debug 

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
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

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