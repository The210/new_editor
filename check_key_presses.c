/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_presses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:23:21 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/28 00:21:17 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_map	check_key_up(t_wind wind, t_map map, t_coord mouse_pos)
{
	if (wind.event.key.keysym.sym == SDLK_ESCAPE)
		clean_and_exit(wind);
	else if (wind.event.key.keysym.sym == SDLK_v)
		map = create_mid_line_vertex(map, mouse_pos);
	return (map);
}

t_map	check_key_press(t_wind wind, t_map map, t_coord mouse_pos)
{
	if (wind.event.type == SDL_KEYUP)
		map = check_key_up(wind, map, mouse_pos);	
	return (map);
}
