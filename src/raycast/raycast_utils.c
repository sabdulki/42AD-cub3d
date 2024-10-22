/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:21 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 19:50:13 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	initialize_ray_vars(t_ray_vars *vars, int x, int w, t_data *data)
{
	vars->camera_x = 2 * x / (float)w - 1;
	vars->ray_dir_x = data->pdx + data->plane_x * vars->camera_x;
	vars->ray_dir_y = data->pdy + data->plane_y * vars->camera_x;
	vars->map_x = (int)(data->px / TEX_WIDTH);
	vars->map_y = (int)(data->py / TEX_HEIGHT);
	vars->delta_dist_x = fabs(1 / vars->ray_dir_x);
	vars->delta_dist_y = fabs(1 / vars->ray_dir_y);
}

void	calculate_step_sidedist(t_ray_vars *vars, t_data *data)
{
	float	pos_x;
	float	pos_y;

	pos_x = data->px / TEX_WIDTH;
	pos_y = data->py / TEX_HEIGHT;
	if (vars->ray_dir_x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (pos_x - vars->map_x) * vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - pos_x) * vars->delta_dist_x;
	}
	if (vars->ray_dir_y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (pos_y - vars->map_y) * vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - pos_y) * vars->delta_dist_y;
	}
}

void	perform_dda(t_ray_vars *vars, t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			vars->side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			vars->side = 1;
		}
		if (vars->map_x >= 0 && vars->map_x < data->cube->map->width
			&& vars->map_y >= 0 && vars->map_y < data->cube->map->height
			&& data->cube->map->map[vars->map_y][vars->map_x] == '1')
			hit = 1;
	}
}

void	calculate_wall_vars(t_ray_vars *vars, t_data *data)
{
	float	pos_x;
	float	pos_y;

	pos_x = data->px / TEX_WIDTH;
	pos_y = data->py / TEX_HEIGHT;
	if (vars->side == 0)
		vars->perp_wall_dist = (vars->map_x - pos_x
				+ (1 - vars->step_x) / 2) / vars->ray_dir_x;
	else
		vars->perp_wall_dist = (vars->map_y - pos_y
				+ (1 - vars->step_y) / 2) / vars->ray_dir_y;
}
