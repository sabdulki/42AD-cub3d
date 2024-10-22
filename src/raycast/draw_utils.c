/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:41:48 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 20:06:43 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	my_mlx_pixel_put(t_data *data, t_point point, int color)
{
	if (point.x >= 0 && point.x < 1024 && point.y >= 0 && point.y < 512)
		data->addr[point.y * (data->line_length / 4) + point.x] = color;
}

void	draw_rectangle(t_data *data, t_rect rect, int color)
{
	int	i;
	int	j;

	j = rect.y;
	while (j < rect.y + rect.height)
	{
		i = rect.x;
		while (i < rect.x + rect.width)
		{
			my_mlx_pixel_put(data, (t_point){i, j}, color);
			i++;
		}
		j++;
	}
}

static void	init_line_vars(t_point p0, t_point p1, t_line_vars *vars)
{
	vars->dx = abs(p1.x - p0.x);
	vars->dy = -abs(p1.y - p0.y);
	if (p0.x < p1.x)
		vars->sx = 1;
	else
		vars->sx = -1;
	if (p0.y < p1.y)
		vars->sy = 1;
	else
		vars->sy = -1;
	vars->err = vars->dx + vars->dy;
}

void	draw_line(t_data *data, t_point p0, t_point p1, int color)
{
	t_line_vars	vars;

	init_line_vars(p0, p1, &vars);
	while (1)
	{
		my_mlx_pixel_put(data, p0, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		vars.e2 = 2 * vars.err;
		if (vars.e2 >= vars.dy)
		{
			vars.err += vars.dy;
			p0.x += vars.sx;
		}
		if (vars.e2 <= vars.dx)
		{
			vars.err += vars.dx;
			p0.y += vars.sy;
		}
	}
}

int	no_collision(t_data *data, float x, float y)
{
	int		mx;
	int		my;
	char	cell;

	mx = (int)(x) / TEX_WIDTH;
	my = (int)(y) / TEX_HEIGHT;
	if (mx >= 0 && mx < data->cube->map->width
		&& my >= 0 && my < data->cube->map->height)
	{
		cell = data->cube->map->map[my][mx];
		if (cell == '0' || cell == 'N' || cell == 'S'
			|| cell == 'E' || cell == 'W')
			return (1);
	}
	return (0);
}
