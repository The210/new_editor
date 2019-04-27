/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_button_events.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 00:29:48 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/28 01:22:21 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_mouse_press(t_wind wind, t_map map, t_coord mouse_pos)
{
	int vertex_index;

	vertex_index = select_vertex_to_move(map, mouse_pos);
	return (vertex_index);
}

t_map	check_mouse_release(t_wind wind, t_map map, t_coord mouse_pos, int vertex_index)
{
	if (vertex_index != -1)
		map = translate_vertex(map, vertex_index, mouse_pos);
	return (map);
}

t_map	check_mouse_events(t_wind wind, t_map map, t_coord mouse_pos)
{
	static int vertex_index;

	if (wind.event.type == SDL_MOUSEBUTTONDOWN)
		vertex_index = check_mouse_press(wind, map, mouse_pos);
	if (wind.event.type == SDL_MOUSEBUTTONUP)
		map = check_mouse_release(wind, map, mouse_pos, vertex_index);
	return (map);
}
