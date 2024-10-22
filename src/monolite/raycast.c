#include "../cub.h" // Include MinilibX header
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

// Define key codes (adjust according to your system)
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_ESC 53
typedef struct s_texture
{
	void *img;
	int *data;
	int width;
	int height;
	int bpp;
	int size_line;
	int endian;
} t_texture;

typedef struct s_data
{
	void *mlx;
	void *win;
	void *img;
	int *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	float px, py, pdx, pdy, pa;
	int key_w, key_a, key_s, key_d;
	t_cub *cube;
	t_texture textures[4]; // 0: NO, 1: SO, 2: WE, 3: EA
	int map_width;
	int map_height;
	float planeX;
	float planeY;
	int floor_color;
	int ceiling_color;
} t_data;

// Utility functions
float degToRad(float a) { return a * M_PI / 180.0; }
float FixAng(float a)
{
	if (a > 359)
	{
		a -= 360;
	}
	if (a < 0)
	{
		a += 360;
	}
	return a;
}

float get_angle_from_direction(char dir)
{
	if (dir == 'N')
		return 90;
	else if (dir == 'S')
		return 270;
	else if (dir == 'E')
		return 0;
	else if (dir == 'W')
		return 180;
	else
		return 0; // Default to east
}

// Drawing functions
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < 1024 && y >= 0 && y < 512)
	{
		data->addr[y * (data->line_length / 4) + x] = color;
	}
}

void draw_rectangle(t_data *data, int x, int y, int width, int height, int color)
{
	int i, j;
	for (j = y; j < y + height; j++)
	{
		for (i = x; i < x + width; i++)
		{
			my_mlx_pixel_put(data, i, j, color);
		}
	}
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int dx, dy, steps, i;
	float x_inc, y_inc, x, y;

	dx = x1 - x0;
	dy = y1 - y0;

	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	if (steps == 0)
	{
		my_mlx_pixel_put(data, x0, y0, color);
		return;
	}

	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;

	x = x0;
	y = y0;
	for (i = 0; i <= steps; i++)
	{
		my_mlx_pixel_put(data, x, y, color);
		x += x_inc;
		y += y_inc;
	}
}

int no_collision(t_data *data, float x, float y)
{
	int mx = (int)(x) / TEX_WIDTH;
	int my = (int)(y) / TEX_HEIGHT;
	if (mx >= 0 && mx < data->cube->map->width && my >= 0 && my < data->cube->map->height)
	{
		char cell = data->cube->map->map[my][mx];
		if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			return 1;
	}
	return 0;
}

void update_player(t_data *data)
{
	float move_speed = 0.1; // Adjusted for map units
	float rot_speed = 3.0;

	if (data->key_a)
	{
		data->pa += rot_speed;
		data->pa = FixAng(data->pa);
		data->pdx = cos(degToRad(data->pa));
		data->pdy = -sin(degToRad(data->pa));
		data->planeX = -data->pdy * 0.66;
		data->planeY = data->pdx * 0.66;
	}
	if (data->key_d)
	{
		data->pa -= rot_speed;
		data->pa = FixAng(data->pa);
		data->pdx = cos(degToRad(data->pa));
		data->pdy = -sin(degToRad(data->pa));
		data->planeX = -data->pdy * 0.66;
		data->planeY = data->pdx * 0.66;
	}
	if (data->key_w)
	{
		float new_px = data->px + data->pdx * move_speed * TEX_WIDTH;
		float new_py = data->py + data->pdy * move_speed * TEX_HEIGHT;
		if (no_collision(data, new_px, data->py))
			data->px = new_px;
		if (no_collision(data, data->px, new_py))
			data->py = new_py;
	}
	if (data->key_s)
	{
		float new_px = data->px - data->pdx * move_speed * TEX_WIDTH;
		float new_py = data->py - data->pdy * move_speed * TEX_HEIGHT;
		if (no_collision(data, new_px, data->py))
			data->px = new_px;
		if (no_collision(data, data->px, new_py))
			data->py = new_py;
	}
}

void load_textures(t_data *data)
{
	// Assuming that the texture paths are stored in the sprite list
	t_sprite_list *sprite = data->cube->list;
	while (sprite)
	{
		int index = -1;
		if (sprite->sprite_name == NO)
			index = 0;
		else if (sprite->sprite_name == SO)
			index = 1;
		else if (sprite->sprite_name == WE)
			index = 2;
		else if (sprite->sprite_name == EA)
			index = 3;

		if (index >= 0)
		{
			data->textures[index].img = mlx_xpm_file_to_image(data->mlx, sprite->texture_path,
															  &data->textures[index].width, &data->textures[index].height);
			if (!data->textures[index].img)
			{
				printf("Error loading texture %s\n", sprite->texture_path);
				exit(1);
			}
			data->textures[index].data = (int *)mlx_get_data_addr(data->textures[index].img,
																  &data->textures[index].bpp, &data->textures[index].size_line, &data->textures[index].endian);
		}
		sprite = sprite->next;
	}
}

// Function to draw the map as an overlay in the lower-left corner
void drawMap2D(t_data *data)
{
	int x, y;
	int map_scale = 8;													 // Scale down the map
	int map_offset_x = 10;												 // Offset from the left edge
	int map_offset_y = 512 - (data->cube->map->height * map_scale) - 10; // Offset from bottom edge

	for (y = 0; y < data->cube->map->height; y++)
	{
		for (x = 0; x < data->cube->map->width; x++)
		{
			int color;
			char cell = data->cube->map->map[y][x];
			if (cell == '1')
				color = 0xFFFFFF; // White for walls
			else if (cell == ' ')
				continue; // Skip drawing for spaces
			else
				color = 0x000000; // Black for empty space

			draw_rectangle(data,
						   map_offset_x + x * map_scale,
						   map_offset_y + y * map_scale,
						   map_scale - 1,
						   map_scale - 1,
						   color);
		}
	}

	// Draw player on the map
	int player_map_x = map_offset_x + (int)(data->px / TEX_WIDTH * map_scale);
	int player_map_y = map_offset_y + (int)(data->py / TEX_HEIGHT * map_scale);
	draw_rectangle(data, player_map_x - 2, player_map_y - 2, 4, 4, 0xFF0000);

	// Draw player direction line on the map
	int line_length = 5;
	int line_x = player_map_x + data->pdx * line_length;
	int line_y = player_map_y + data->pdy * line_length;
	draw_line(data, player_map_x, player_map_y, line_x, line_y, 0xFF0000);
}

void draw_walls(t_data *data, int x, int lineHeight, int drawStart, int drawEnd, int texNum, float wallX, int side)
{
	int texX = (int)(wallX * (float)(TEX_WIDTH));
	if (side == 0 && data->pdx > 0)
		texX = TEX_WIDTH - texX - 1;
	if (side == 1 && data->pdy < 0)
		texX = TEX_WIDTH - texX - 1;
	for (int y = drawStart; y < drawEnd; y++)
	{
		int d = y * 256 - 512 * 128 + lineHeight * 128;
		int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
		int color = data->textures[texNum].data[TEX_HEIGHT * texY + texX];
		my_mlx_pixel_put(data, x, y, color);
	}
}

void drawRays2D(t_data *data)
{
	int w = 1024;
	int h = 512;
	float posX = data->px / TEX_WIDTH;
	float posY = data->py / TEX_HEIGHT;
	for (int x = 0; x < w; x++)
	{
		float cameraX = 2 * x / (float)w - 1; // x-coordinate in camera space
		float rayDirX = data->pdx + data->planeX * cameraX;
		float rayDirY = data->pdy + data->planeY * cameraX;

		int mapX = (int)(posX);
		int mapY = (int)(posY);

		float sideDistX;
		float sideDistY;

		float deltaDistX = fabs(1 / rayDirX);
		float deltaDistY = fabs(1 / rayDirY);
		float perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (mapX >= 0 && mapX < data->cube->map->width && mapY >= 0 && mapY < data->cube->map->height &&
				data->cube->map->map[mapY][mapX] == '1')
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(h / perpWallDist);

		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		// Choose texture based on wall orientation (inverted as per your specification)
		int texNum = -1;
		if (side == 0)
		{
			if (stepX > 0)
				texNum = 2; // WE texture (inverted, so we use EA)
			else
				texNum = 3; // EA texture (inverted, so we use WE)
		}
		else
		{
			if (stepY > 0)
				texNum = 0; // NO texture (inverted, so we use SO)
			else
				texNum = 1; // SO texture (inverted, so we use NO)
		}

		float wallX;
		if (side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (float)(TEX_WIDTH));
		if (side == 0 && rayDirX > 0)
			texX = TEX_WIDTH - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = TEX_WIDTH - texX - 1;
			
		// Draw the wall
		for (int y = drawStart; y < drawEnd; y++)
		{
			int d = y * 256 - h * 128 + lineHeight * 128;
			int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
			if (texY < 0)
				texY = 0;
			if (texY >= TEX_HEIGHT)
				texY = TEX_HEIGHT - 1;
			int color = data->textures[texNum].data[TEX_HEIGHT * texY + texX];
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}

void draw_scene(t_data *data)
{
    int w = 1024;
    int h = 512;
    for(int y = 0; y < h / 2; y++)
    {
        for(int x = 0; x < w; x++)
        {
            my_mlx_pixel_put(data, x, y, data->floor_color);
        }
    }

    for(int y = h / 2; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            my_mlx_pixel_put(data, x, y, data->ceiling_color);
        }
    }
    drawRays2D(data);

    // Draw the map overlay
    drawMap2D(data);
}

int key_press(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_w = 1;
	if (keycode == KEY_A)
		data->key_a = 1;
	if (keycode == KEY_S)
		data->key_s = 1;
	if (keycode == KEY_D)
		data->key_d = 1;
	if (keycode == KEY_ESC)
		exit(0);
	return 0;
}

int key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_w = 0;
	if (keycode == KEY_A)
		data->key_a = 0;
	if (keycode == KEY_S)
		data->key_s = 0;
	if (keycode == KEY_D)
		data->key_d = 0;
	return 0;
}

int update_frame(t_data *data)
{
	// Update player position
	update_player(data);

	// Clear image
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, 1024, 512);
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);

	// Draw scene
	draw_scene(data);

	// Put image to window
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

	return 0;
}

void extract_floor_ceiling_colors(t_data *data)
{
    t_sprite_list *sprite = data->cube->list;
    while (sprite)
    {
        if (sprite->sprite_name == F)
        {
			printf("F: %d, %d, %d\n", sprite->color[0],sprite->color[1],sprite->color[2]);
            data->floor_color = (0 << 24) | (sprite->color[0] << 16) | (sprite->color[1] << 8) | sprite->color[2];
			printf("Created color: %d\n", data->floor_color);
        }
        else if (sprite->sprite_name == C)
        {
			printf("C: %d, %d, %d\n", sprite->color[0],sprite->color[1],sprite->color[2]);
            data->ceiling_color = (0 << 24) | (sprite->color[0] << 16) | (sprite->color[1] << 8) | sprite->color[2];
			printf("Created color: %d\n", data->ceiling_color);
        }
        sprite = sprite->next;
    }
}
//void extract_floor_ceiling_colors(t_data *data)
//{
//	t_sprite_list *sprite = data->cube->list;
//	while (sprite)
//	{
//		if (sprite->sprite_name == F)
//		{
//			// Combine RGB values into a single integer
//			data->floor_color = (sprite->color[0] << 16) | (sprite->color[1] << 8) | sprite->color[2];
//		}
//		else if (sprite->sprite_name == C)
//		{
//			// Combine RGB values into a single integer
//			data->ceiling_color = (sprite->color[0] << 16) | (sprite->color[1] << 8) | sprite->color[2];
//		}
//		sprite = sprite->next;
//	}
//}

#include "../cub.h"

static void	process_map_cell(t_data *data, int x, int y, int *found_player)
{
	char	c;

	c = data->cube->map->map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*found_player)
		{
			printf("Error: Multiple player positions in map\n");
			exit(1);
		}
		set_player_position(data, x, y, c);
		*found_player = 1;
	}
}

void	parse_map_ray(t_data *data)
{
	int	x;
	int	y;
	int	found_player;

	found_player = 0;
	y = 0;
	while (y < data->cube->map->height)
	{
		x = 0;
		while (x < data->cube->map->width)
		{
			process_map_cell(data, x, y, &found_player);
			x++;
		}
		y++;
	}
	if (!found_player)
	{
		printf("Error: Player position not found in map\n");
		exit(1);
	}
}

int raycast(t_cub *cube)
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1024, 512, "Raycaster");
	data.img = mlx_new_image(data.mlx, 1024, 512);
	data.addr = (int *)mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.cube = cube;
	extract_floor_ceiling_colors(&data);

	data.map_width = data.cube->map->width;
	data.map_height = data.cube->map->height;

	// Initialize key states
	data.key_w = 0;
	data.key_a = 0;
	data.key_s = 0;
	data.key_d = 0;

	parse_map_ray(&data);
	load_textures(&data);

	// Set up event hooks
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, update_frame, &data);

	mlx_loop(data.mlx);

	return 0;
}