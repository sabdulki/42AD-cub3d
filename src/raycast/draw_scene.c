/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:41:41 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 20:14:05 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	draw_single_cell(t_data *data, t_cell_params *params)
{
	int		color;
	char	cell;
	t_rect	rect;

	cell = data->cube->map->map[params->y][params->x];
	if (cell == '1')
		color = 0xFFFFFF;
	else if (cell == ' ')
		return ;
	else
		color = 0x000000;
	rect.x = params->offset.x + params->x * params->scale;
	rect.y = params->offset.y + params->y * params->scale;
	rect.width = params->scale - 1;
	rect.height = params->scale - 1;
	draw_rectangle(data, rect, color);
}

void	draw_map_cells(t_data *data, int scale, t_point offset)
{
	int				x;
	int				y;
	t_cell_params	params;

	params.scale = scale;
	params.offset = offset;
	y = 0;
	while (y < data->cube->map->height)
	{
		params.y = y;
		x = 0;
		while (x < data->cube->map->width)
		{
			params.x = x;
			draw_single_cell(data, &params);
			x++;
		}
		y++;
	}
}

void	draw_player_on_map(t_data *data, t_point offset, int scale)
{
	t_player_map_vars	vars;

	vars.player_map_x = offset.x
		+ (int)(data->px / TEX_WIDTH * scale);
	vars.player_map_y = offset.y
		+ (int)(data->py / TEX_HEIGHT * scale);
	draw_rectangle(data, (t_rect){
		vars.player_map_x - 2, vars.player_map_y - 2, 4, 4}, 0xFF0000);
	vars.line_length = 5;
	vars.line_x = vars.player_map_x + data->pdx * vars.line_length;
	vars.line_y = vars.player_map_y + data->pdy * vars.line_length;
	draw_line(data, (t_point){vars.player_map_x, vars.player_map_y},
		(t_point){vars.line_x, vars.line_y}, 0xFF0000);
}

void	draw_map_2d(t_data *data)
{
	int		map_scale;
	t_point	offset;

	map_scale = 8;
	offset.x = 10;
	offset.y = 512 - (data->cube->map->height * map_scale) - 10;
	draw_map_cells(data, map_scale, offset);
	draw_player_on_map(data, offset, map_scale);
}
