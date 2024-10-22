/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:53:54 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 21:54:07 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	rotate_player(t_data *data, float angle)
{
	data->pa += angle;
	data->pa = fix_ang(data->pa);
	data->pdx = cos(deg_to_rad(data->pa));
	data->pdy = -sin(deg_to_rad(data->pa));
	data->plane_x = -data->pdy * 0.66;
	data->plane_y = data->pdx * 0.66;
}

void	update_rotation(t_data *data, float rot_speed)
{
	if (data->key_left)
		rotate_player(data, rot_speed);
	if (data->key_right)
		rotate_player(data, -rot_speed);
}

static void	move_player(t_data *data, float move_speed,
				float dir_x, float dir_y)
{
	float	new_px;
	float	new_py;

	new_px = data->px + dir_x * move_speed * TEX_WIDTH;
	new_py = data->py + dir_y * move_speed * TEX_HEIGHT;
	if (no_collision(data, new_px, data->py))
		data->px = new_px;
	if (no_collision(data, data->px, new_py))
		data->py = new_py;
}

void	update_movement(t_data *data, float move_speed)
{
	if (data->key_w)
		move_player(data, move_speed, data->pdx, data->pdy);
	if (data->key_s)
		move_player(data, -move_speed, data->pdx, data->pdy);
	if (data->key_a)
		move_player(data, move_speed, data->pdy, -data->pdx);
	if (data->key_d)
		move_player(data, -move_speed, data->pdy, -data->pdx);
}
