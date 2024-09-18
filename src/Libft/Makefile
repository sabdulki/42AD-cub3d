# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 10:45:42 by vlomakin          #+#    #+#              #
#    Updated: 2024/09/18 12:52:22 by sabdulki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = --debug -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# separate folder for .o files
# OBJS_DIR = obj
# OBJS := $(addprefix $(OBJS_DIR)/, $(notdir $(OBJS)))

SRC = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_striteri.c \

SRC_B = 	ft_lstnew.c \
	  		ft_lstsize.c \
			ft_lstadd_front.c \
	  		ft_lstlast.c \
	  		ft_lstadd_back.c \
	  		ft_lstdelone.c \
	  		ft_lstclear.c \
	  		ft_lstiter.c \
			ft_lstmap.c \

OBJ =	$(SRC:.c=.o)

OBJ_B =	$(SRC_B:.c=.o)

# create the specified folder and move .o objects there
# $(OBJS_DIR):
# 	mkdir -p $(OBJS_DIR)

# $(OBJS_DIR)/%.o: ./src/%.c | $(OBJS_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

# create the executable
$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

all: $(NAME)

bonus: $(OBJ) $(OBJ_B)
	@$(AR) $(NAME) $(OBJ) $(OBJ_B)

clean:
	@$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	@$(RM) $(NAME) $(OBJ) $(OBJ_B)

re: fclean all

.PHONY: bonus all clean fclean re