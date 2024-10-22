/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:24 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 19:36:13 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	cast_single_ray(t_data *data, int x, int w, int h)
{
	t_ray_vars	vars;

	initialize_ray_vars(&vars, x, w, data);
	calculate_step_sidedist(&vars, data);
	perform_dda(&vars, data);
	calculate_wall_vars(&vars, data);
	draw_vertical_line(data, x, h, &vars);
}

void	draw_rays_2d(t_data *data)
{
	int	x;
	int	w;
	int	h;

	w = 1024;
	h = 512;
	x = 0;
	while (x < w)
	{
		cast_single_ray(data, x, w, h);
		x++;
	}
}
