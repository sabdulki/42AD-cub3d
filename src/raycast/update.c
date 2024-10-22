/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:41 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 21:23:03 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	else if (keycode == KEY_A)
		data->key_a = 1;
	else if (keycode == KEY_S)
		data->key_s = 1;
	else if (keycode == KEY_D)
		data->key_d = 1;
	else if (keycode == KEY_LEFT)
	{
		data->key_left = 1;
		data->key_right = 0;
	}
	else if (keycode == KEY_RIGHT)
	{
		data->key_right = 1;
		data->key_left = 0;
	}
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_w = 0;
	else if (keycode == KEY_A)
		data->key_a = 0;
	else if (keycode == KEY_S)
		data->key_s = 0;
	else if (keycode == KEY_D)
		data->key_d = 0;
	else if (keycode == KEY_LEFT)
		data->key_left = 0;
	else if (keycode == KEY_RIGHT)
		data->key_right = 0;
	return (0);
}
