/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:27:00 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/19 16:39:46 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/cub.h"

int main(int ac, char **av)
{
	// if (ac != 2 || !av[1])
	// if (ac != 3 || !av[1]) //DEBUG
	if (ac == 3) // means it's debug mode
	{
		printf("debug mode activated\n");
		if (!av[2])
			return (perror("invalid aruments"), 1);
		parsing(av[2]);
	}
	else //normal
	{
		printf("NON debug mode activated\n");\
		if (ac != 2 || !av[1])
			return (perror("invalid aruments"), 1);
		parsing(av[1]);
	}

	return (0);
}