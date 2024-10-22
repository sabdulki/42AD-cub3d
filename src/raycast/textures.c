/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:35 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 19:35:31 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	load_texture(t_data *data, t_sprite_list *sprite, int index)
{
	data->textures[index].img = mlx_xpm_file_to_image(data->mlx,
			sprite->texture_path, &data->textures[index].width,
			&data->textures[index].height);
	if (!data->textures[index].img)
	{
		printf("Error loading texture %s\n", sprite->texture_path);
		exit(1);
	}
	data->textures[index].data = (int *)mlx_get_data_addr(
			data->textures[index].img, &data->textures[index].bpp,
			&data->textures[index].size_line,
			&data->textures[index].endian);
}

void	load_textures(t_data *data)
{
	t_sprite_list	*sprite;
	int				index;

	sprite = data->cube->list;
	while (sprite)
	{
		index = -1;
		if (sprite->sprite_name == NO)
			index = 0;
		else if (sprite->sprite_name == SO)
			index = 1;
		else if (sprite->sprite_name == WE)
			index = 2;
		else if (sprite->sprite_name == EA)
			index = 3;
		if (index >= 0)
			load_texture(data, sprite, index);
		sprite = sprite->next;
	}
}

void	extract_color(int *color_var, int *color_array)
{
	*color_var = (0 << 24) | ((color_array[0] & 0xFF) << 16)
		| ((color_array[1] & 0xFF) << 8) | (color_array[2] & 0xFF);
}

void	extract_floor_ceiling_colors(t_data *data)
{
	t_sprite_list	*sprite;

	sprite = data->cube->list;
	while (sprite)
	{
		if (sprite->sprite_name == F)
			extract_color(&data->floor_color, sprite->color);
		else if (sprite->sprite_name == C)
			extract_color(&data->ceiling_color, sprite->color);
		sprite = sprite->next;
	}
}
