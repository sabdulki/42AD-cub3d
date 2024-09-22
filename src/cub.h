/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:26:55 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/20 16:24:29 by sabdulki         ###   ########.fr       */
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

typedef enum s_sprites
{
	NO = 0,
	SO = 1,
	WE = 2, 
	EA = 3,
	F = 4,
	C = 5
}	t_sprites;

typedef struct s_sprite_list
{
	int sprite_name;
	char *texture_path;
	int *color; //size = 3;
	int head;
	t_sprite_list	*next;
	
}		t_sprite_list;

/* parsing */
int parsing(char *map_path);
int format(char *map_path);
int check_file(char *map_path);
int file_content(char *map_path);


#endif