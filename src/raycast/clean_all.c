/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:54:13 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 21:55:39 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	cleanup_texture(t_data *data, t_texture *texture)
{
	if (texture->img)
	{
		mlx_destroy_image(data->mlx, texture->img);
		texture->img = NULL;
	}
	if (texture->data)
	{
		texture->data = NULL;
	}
}

void	clean_all(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < 4)
		cleanup_texture(data, &data->textures[i]);
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		free(data->mlx);
		data->mlx = NULL;
	}
	if (data->cube)
	{
		free_cub(data->cube);
		data->cube = NULL;
	}
}
