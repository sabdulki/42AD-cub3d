/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdulki <sabdulki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:27:00 by sabdulki          #+#    #+#             */
/*   Updated: 2024/09/17 20:38:43 by sabdulki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int ac, char **av)
{
	char	*map_path;

	map_path = av[1];
	/*
	PARSING
	1) check if the file exists and the format is name.cub (open());
	2) read the file with gnl
	So I should have 6 sprites at all.
		TEXTURES (2.1)
			2.1.1) check if lines contain NO, SO, EA, WE (the order doesn't matter)
			2.1.2) check the access for path to texture for wall
		COLORS (2.2)
			2.2.1) check if 2 lines contain F(floor) and C(ceiling) (the order doesn't matter)
			2.2.2) check if the colors are valid:
				number > 0 && < 256
				separated by comma
				only 3 numbers after F or C
		MAP (2.3)
		2.3.1)
		
		
	
	*/
}