/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:41 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 19:50:23 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	update_rotation(t_data *data, float rot_speed)
{
	if (data->key_a)
	{
		data->pa += rot_speed;
		data->pa = fix_ang(data->pa);
		data->pdx = cos(deg_to_rad(data->pa));
		data->pdy = -sin(deg_to_rad(data->pa));
		data->plane_x = -data->pdy * 0.66;
		data->plane_y = data->pdx * 0.66;
	}
	if (data->key_d)
	{
		data->pa -= rot_speed;
		data->pa = fix_ang(data->pa);
		data->pdx = cos(deg_to_rad(data->pa));
		data->pdy = -sin(deg_to_rad(data->pa));
		data->plane_x = -data->pdy * 0.66;
		data->plane_y = data->pdx * 0.66;
	}
}

void	update_movement(t_data *data, float move_speed)
{
	float	new_px;
	float	new_py;

	if (data->key_w)
	{
		new_px = data->px + data->pdx * move_speed * TEX_WIDTH;
		new_py = data->py + data->pdy * move_speed * TEX_HEIGHT;
		if (no_collision(data, new_px, data->py))
			data->px = new_px;
		if (no_collision(data, data->px, new_py))
			data->py = new_py;
	}
	if (data->key_s)
	{
		new_px = data->px - data->pdx * move_speed * TEX_WIDTH;
		new_py = data->py - data->pdy * move_speed * TEX_HEIGHT;
		if (no_collision(data, new_px, data->py))
			data->px = new_px;
		if (no_collision(data, data->px, new_py))
			data->py = new_py;
	}
}

void	update_player(t_data *data)
{
	float	move_speed;
	float	rot_speed;

	move_speed = 0.1;
	rot_speed = 3.0;
	update_rotation(data, rot_speed);
	update_movement(data, move_speed);
}

int	key_press(int keycode, t_data *data)
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
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_w = 0;
	if (keycode == KEY_A)
		data->key_a = 0;
	if (keycode == KEY_S)
		data->key_s = 0;
	if (keycode == KEY_D)
		data->key_d = 0;
	return (0);
}
