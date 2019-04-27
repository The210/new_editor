/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:24:41 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/28 01:05:46 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	clean_and_exit(t_wind wind)
{
	//TO DO: clear for leaks, close fd's etc
	SDL_DestroyWindow(wind.window);
	SDL_Quit();
	exit(1);
}

void	exit_on_error(void)
{
	ft_putendl("There was an error starting the program");
	exit(1);
	//TO DO: close fd's, manage leaks, etc.
}

int		main(int argc, char **argv)
{
	t_map map;
	t_wind wind;
	t_coord mouse_pos;

	if (argc != 2)
		return (0);

	//map = read_values(argv[1]); if there'se a map.
	map = initialize_values(); //new map set-up.
	wind = init_wind(wind);
	while(1)
	{
		while (SDL_PollEvent(&wind.event))
		{
			if (wind.event.type == SDL_MOUSEMOTION)
			{
				mouse_pos.x = wind.event.motion.x;
				mouse_pos.y = wind.event.motion.y;
			}
			map = check_key_press(wind, map, mouse_pos);
			map = check_mouse_events(wind, map, mouse_pos);
			draw_window(map, wind);
		}
	}
}
