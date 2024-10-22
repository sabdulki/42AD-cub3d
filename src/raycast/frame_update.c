/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:41:26 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 18:43:06 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	update_frame(t_data *data)
{
	update_player(data);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, 1024, 512);
	data->addr = (int *)mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
