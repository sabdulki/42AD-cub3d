/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:26:55 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/23 18:03:10 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include "../mlx/mlx.h" 
# include "./Libft/libft.h" 
# include "./get_next_line/get_next_line.h" 
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_default
{
	int type;
}	t_default;

typedef struct s_sprite_list
{
	int type;
	int sprite_name;
	char *texture_path;
	int *color; //size = 3;
	int head;
	struct s_sprite_list	*next;
	
}		t_sprite_list;

typedef struct s_file
{
	int type;
	char *str;
	struct s_file	*next;
}	t_file;


typedef enum s_node
{
	MY_FILE = 1,
	SPRITE = 2,
	MAP = 3, 
	// 0 - default, none
}	t_node;

typedef enum s_sprites
{
	NO = 1,
	SO = 2,
	WE = 3, 
	EA = 4,
	F = 5,
	C = 6
	// 0 - default, none
}	t_sprites;

/* parsing */
int parsing(char *map_path);
int format(char *map_path);
int check_file(char *map_path);
// t_sprite_list *file_content(char *file_path);
t_sprite_list *file_content(t_file *file);
t_file *overwrite_file(char *file_path);

/* list */
t_sprite_list *init_def_node(void);
void	add_node_to_list(t_sprite_list *node, t_sprite_list **head);
t_file *init_def_str(void);
void	add_node_to_file(t_file *node, t_file **head);


/* utils */
void print_file_strct(t_file *file);

/* utils with forbidden stuff */
void print_sprite_list(t_sprite_list *head);
char *sprite_to_string(t_sprites sprite);


#endif