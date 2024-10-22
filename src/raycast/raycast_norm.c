/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:16 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 21:47:55 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	close_win(t_data *data)
{
	clean_all(data);
	exit(0);
	return (0);
}

int	raycast(t_cub *cube)
{
	t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1024, 512, "Raycaster");
	data.img = mlx_new_image(data.mlx, 1024, 512);
	data.addr = (int *)mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	data.cube = cube;
	extract_floor_ceiling_colors(&data);
	data.map_width = data.cube->map->width;
	data.map_height = data.cube->map->height;
	data.key_w = 0;
	data.key_a = 0;
	data.key_s = 0;
	data.key_d = 0;
	parse_map_ray(&data);
	load_textures(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, update_frame, &data);
	mlx_hook(data.win, 17, 1L << 0, close_win, &data);
	mlx_loop(data.mlx);
	return (0);
}
