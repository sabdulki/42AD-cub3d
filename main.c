/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruslannartdinov <ruslannartdinov@student.4 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:27:00 by sabdulki          #+#    #+#             */
/*   Updated: 2024/10/21 05:21:22 by ruslannartdinov  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/cub.h"

int main(int ac, char **av)
{
	char *file_path;
	t_cub *cub;
	if (ac == 3) // means it's debug mode
	{
		printf("debug mode activated\n");
		if (!av[2])
			return (p_error("invalid aruments"), 1);
		file_path = av[2];
	}
	else //normal
	{
		printf("NON debug mode activated\n");\
		if (ac != 2 || !av[1])
			return (p_error("invalid aruments"), 1);
		file_path = av[1];
	}
	cub = parsing(file_path);
	if (!cub)
		return (printf("Error\n"), 1);

	raycast(cub);
	free_cub(cub);
	printf(GREEN "successful!\n" NC);
	return (0);
}
