/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:42:45 by ruslannartdinov   #+#    #+#             */
/*   Updated: 2024/10/22 19:35:46 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

float	fix_ang(float a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

float	get_angle_from_direction(char dir)
{
	if (dir == 'N')
		return (90);
	else if (dir == 'S')
		return (270);
	else if (dir == 'E')
		return (0);
	else if (dir == 'W')
		return (180);
	else
		return (0);
}
