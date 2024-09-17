# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 17:27:03 by sabdulki          #+#    #+#              #
#    Updated: 2024/09/17 20:15:30 by sabdulki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_S = main.cpp

SRCS = $(SRCS_S) 
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

NAME = cub3d

OS = $(shell uname)

ifeq ($(OS), Linux)
    CFLAGS += -I/usr/include -Imlx_linux -O3
    LDFLAGS += -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

else ifeq ($(OS), Darwin)
    CFLAGS += -Imlx -I./mlx_mac
    LDFLAGS += -L./mlx_mac -lmlx -framework OpenGL -framework AppKit -ldl -lpthread
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re