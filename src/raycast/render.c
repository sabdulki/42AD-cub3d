/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:31 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 19:35:16 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	select_texture(t_ray_vars *vars)
{
	if (vars->side == 0)
	{
		if (vars->ray_dir_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (vars->ray_dir_y > 0)
			return (0);
		else
			return (1);
	}
}

float	get_wall_x(t_ray_vars *vars, t_data *data)
{
	float	wall_x;
	float	pos_x;
	float	pos_y;

	pos_x = data->px / TEX_WIDTH;
	pos_y = data->py / TEX_HEIGHT;
	if (vars->side == 0)
		wall_x = pos_y + vars->perp_wall_dist * vars->ray_dir_y;
	else
		wall_x = pos_x + vars->perp_wall_dist * vars->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	calculate_line_vars(int h, t_ray_vars *vars, t_draw_vars *dv)
{
	dv->line_height = (int)(h / vars->perp_wall_dist);
	dv->draw_start = -dv->line_height / 2 + h / 2;
	if (dv->draw_start < 0)
		dv->draw_start = 0;
	dv->draw_end = dv->line_height / 2 + h / 2;
	if (dv->draw_end >= h)
		dv->draw_end = h - 1;
}

void	draw_vertical_line(t_data *data, int x, int h, t_ray_vars *vars)
{
	t_draw_vars	dv;

	calculate_line_vars(h, vars, &dv);
	dv.tex_num = select_texture(vars);
	dv.wall_x = get_wall_x(vars, data);
	dv.tex_x = (int)(dv.wall_x * (float)(TEX_WIDTH));
	if (vars->side == 0 && vars->ray_dir_x > 0)
		dv.tex_x = TEX_WIDTH - dv.tex_x - 1;
	if (vars->side == 1 && vars->ray_dir_y < 0)
		dv.tex_x = TEX_WIDTH - dv.tex_x - 1;
	draw_textured_line(data, x, &dv, h);
}

void	draw_textured_line(t_data *data, int x, t_draw_vars *dv, int h)
{
	t_tex_vars	vars;

	vars.h = h;
	vars.y = dv->draw_start;
	while (vars.y < dv->draw_end)
	{
		vars.d = vars.y * 256 - vars.h * 128 + dv->line_height * 128;
		vars.tex_y = ((vars.d * TEX_HEIGHT) / dv->line_height) / 256;
		if (vars.tex_y < 0)
			vars.tex_y = 0;
		if (vars.tex_y >= TEX_HEIGHT)
			vars.tex_y = TEX_HEIGHT - 1;
		vars.color = data->textures[dv->tex_num]
			.data[TEX_HEIGHT * vars.tex_y + dv->tex_x];
		my_mlx_pixel_put(data, (t_point){x, vars.y}, vars.color);
		vars.y++;
	}
}
