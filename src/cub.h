/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:26:55 by sabdulki          #+#    #+#             */
/*   Updated: 2024/10/22 21:47:10 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

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

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define NC "\033[0m"

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		*player_position;
	char	player_direction;
}	t_map;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_sprite_list
{
	int						type;
	int						sprite_name;
	char					*texture_path;
	int						*color;
	int						head;
	struct s_sprite_list	*next;
}	t_sprite_list;

typedef struct s_cub
{
	t_sprite_list	*list;
	t_map			*map;
}	t_cub;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
	int			key_w;
    int			key_a;
    int			key_s;
    int			key_d;
    int			key_left;
    int			key_right;
	t_cub		*cube;
	t_texture	textures[4];
	int			map_width;
	int			map_height;
	float		plane_x;
	float		plane_y;
	int			floor_color;
	int			ceiling_color;
}	t_data;

typedef enum e_sprites
{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4,
	F = 5,
	C = 6
}	t_sprites;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rect;

typedef struct s_line_vars
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}	t_line_vars;

typedef struct s_cell_params
{
	int		x;
	int		y;
	int		scale;
	t_point	offset;
}	t_cell_params;
typedef struct s_player_map_vars
{
	int	player_map_x;
	int	player_map_y;
	int	line_length;
	int	line_x;
	int	line_y;
}	t_player_map_vars;

typedef struct s_ray_vars
{
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray_vars;

typedef struct s_draw_vars
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	float	wall_x;
	int		tex_x;
}	t_draw_vars;

typedef struct s_tex_vars
{
	int	y;
	int	d;
	int	tex_y;
	int	color;
	int	h;
}	t_tex_vars;

typedef struct s_file
{
	int				type;
	char			*str;
	int				txtr_end;
	int				map_start;
	int				map_end;
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

/* parsing */
t_cub			*parsing(char *map_path);
int				format(char *map_path);
int				check_file(char *map_path);
t_cub			*file_content(t_file *file);
t_file			*overwrite_file(char *file_path);
t_sprite_list	*fill_sprites(t_file *file);

/* map parsing */
t_map			*do_map(t_file *file);
int				map_top_bottom(t_file *file);
int				map_end(t_file *supposed_end);
t_file			*get_start(t_file *file);
t_file			*get_end(t_file *file);
int				invalid_char(int c);
int				nsew(int c);
int				get_nbr_value(t_map *map_strct, int y, int x);
int				check_neighbours(t_map *map, int y, int x);
char			**allocate_2d_map(int height, int width);

/* color */
int				is_color(char *spr_value);
int				*do_color(char *spr_value);

/* list */
t_cub			*init_cub(void);
t_map			*init_def_map(void);
t_file			*init_def_str(void);
t_sprite_list	*init_def_node(void);
void			add_node_to_list(t_sprite_list *node, t_sprite_list **head);
void			add_node_to_file(t_file *node, t_file **head);

/* free */
void			free_cub(t_cub *cub);
void			free_map(t_map *map);
void			free_file_list(t_file *head);
void			free_sprite_list(t_sprite_list *head);
void			free_cub(t_cub *cub);

/* utils */
void			p_error(char *str);
int				is_delimiter(char c);
int				safe_strncmp(char *s1, char *s2);
void			print_file_strct(t_file *file);
int				which_name(char *sprite_name);
int				empty(char *str);
int				tabs(char *str);
int				double_sprites(t_sprite_list *node, t_sprite_list *head);
int				all_sprites_found(t_sprite_list *head);
int				calculate_height(t_file *start);
int				calculate_width(t_file *start);
char			**allocate_2d_map(int height, int width);
int				print_map(t_map *map);
int				where_map(t_file *file);

/* utils with forbidden stuff like switch and for()*/
void			print_sprite_list(t_sprite_list *head);
char			*sprite_to_string(t_sprites sprite);

float			deg_to_rad(float a);
float			fix_ang(float a);
float			get_angle_from_direction(char dir);

//static void	draw_single_cell(t_data *data, t_cell_params *params);
void			my_mlx_pixel_put(t_data *data, t_point point, int color);
void			draw_rectangle(t_data *data, t_rect rect, int color);
void			draw_line(t_data *data, t_point p0, t_point p1, int color);
int				no_collision(t_data *data, float x, float y);

void			update_player(t_data *data);
void			load_textures(t_data *data);
void			draw_scene(t_data *data);

int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				update_frame(t_data *data);

void			extract_floor_ceiling_colors(t_data *data);
void			parse_map_ray(t_data *data);
int				raycast(t_cub *cube);

void			draw_rays_2d(t_data *data);
void			cast_single_ray(t_data *data, int x, int w, int h);

float			deg_to_rad(float a);
float			fix_ang(float a);
float			get_angle_from_direction(char dir);
int				no_collision(t_data *data, float x, float y);

void			update_player(t_data *data);
void			load_textures(t_data *data);
void			draw_map_2d(t_data *data);
void			draw_map_2d_ray(t_data *data, t_map *map);
void			draw_player_on_map(t_data *data, t_point offset, int scale);
void			draw_scene(t_data *data);

int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				update_frame(t_data *data);

void			extract_floor_ceiling_colors(t_data *data);
void			parse_map_ray(t_data *data);
int				raycast(t_cub *cube);

void			draw_rays_2d(t_data *data);
void			cast_single_ray(t_data *data, int x, int w, int h);

void			initialize_ray_vars(t_ray_vars *vars, int x, int w,
					t_data *data);
void			calculate_step_sidedist(t_ray_vars *vars, t_data *data);
void			perform_dda(t_ray_vars *vars, t_data *data);
void			calculate_wall_vars(t_ray_vars *vars, t_data *data);
void			draw_vertical_line(t_data *data, int x, int h,
					t_ray_vars *vars);
int				select_texture(t_ray_vars *vars);
float			get_wall_x(t_ray_vars *vars, t_data *data);
void			calculate_line_vars(int h, t_ray_vars *vars, t_draw_vars *dv);
void			draw_textured_line(t_data *data, int x, t_draw_vars *dv, int h);
void			update_rotation(t_data *data, float rot_speed);
void			update_movement(t_data *data, float move_speed);
void			clean_all(t_data *data);

#endif