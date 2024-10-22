/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:26:34 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 20:26:38 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	fill_background(t_data *data, int w, int h)
{
	int	x;
	int	y;

	y = 0;
	while (y < h / 2)
	{
		x = 0;
		while (x < w)
		{
			my_mlx_pixel_put(data, (t_point){x, y}, data->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			my_mlx_pixel_put(data, (t_point){x, y}, data->floor_color);
			x++;
		}
		y++;
	}
}

void	draw_scene(t_data *data)
{
	int	w;
	int	h;

	w = 1024;
	h = 512;
	fill_background(data, w, h);
	draw_rays_2d(data);
	draw_map_2d(data);
}
