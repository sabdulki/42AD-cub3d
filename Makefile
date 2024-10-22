# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 17:27:03 by sabdulki          #+#    #+#              #
#    Updated: 2024/10/22 18:23:30 by sabdulki         ###   ########.fr        #
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

SRC_RAYCAST = ./src/raycast/raycast.c

SRC = $(SRCS_S) $(SRC_GNL) $(SRC_P) $(SRC_U) $(SRC_RAYCAST)
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
CC = cc
NAME = cub3d
MAKE_MLX = cd mlx && make
MAKE_LIBFT = cd ./src/Libft && make
LIBFT_A = ./src/Libft/libft.a
all : $(NAME)

$(NAME) : $(OBJ)
	$(MAKE_MLX)
	$(MAKE_LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
clean:
	rm -f $(OBJ)
	$(MAKE) clean -C mlx
	$(MAKE) -C src/Libft clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C src/Libft fclean

re:	fclean all

.PHONY: all clean fclean re