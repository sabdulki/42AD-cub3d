/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:26:55 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/24 21:05:55 by sabdulki         ###   ########.fr       */
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

typedef struct s_cub
{
	struct s_sprite_list *list;
	char **map;
} t_cub;

// typedef struct s_default
// {
// 	int type;
// }	t_default;

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
	struct s_file	*prev;
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
t_cub *parsing(char *map_path);
int format(char *map_path);
int check_file(char *map_path);
t_cub *file_content(t_file *file);
t_file *overwrite_file(char *file_path);

/* color */
int is_color(char *spr_value);
int *do_color(char *spr_value);

/* list */
t_cub *init_cub();
t_file *init_def_str(void);
t_sprite_list *init_def_node(void);
void	add_node_to_list(t_sprite_list *node, t_sprite_list **head);
void	add_node_to_file(t_file *node, t_file **head);
void free_file_list(t_file *head);
void free_sprite_list(t_sprite_list *head);
void free_cub(t_cub *cub);

/* utils */
void p_error(char *str);
int	is_delimiter(char c);
int safe_strncmp(char *s1, char *s2);
void print_file_strct(t_file *file);
int which_name(char *sprite_name);
int empty(char *str);
int double_sprites(t_sprite_list *node, t_sprite_list *head);
int all_sprites_found(t_sprite_list *head);

/* utils with forbidden stuff like switch and for()*/
void print_sprite_list(t_sprite_list *head);
char *sprite_to_string(t_sprites sprite);

#endif