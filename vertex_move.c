/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:07:05 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/28 00:59:43 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		select_vertex_to_move(t_map map, t_coord mouse_pos)
{
	int i;
	int min_distance_found;
	int min_distance_allowed;
	int current_distance;
	int	vertex_index;

	min_distance_allowed = 10;
	min_distance_found = 11;
	i = -1;
	while(++i < map.vertex_length)
	{
		if ((current_distance = get_point_distance(mouse_pos, map.vertex[i])) < min_distance_found)
		{
			min_distance_found = current_distance;
			vertex_index = i;
		}	
	}
	return(min_distance_found < min_distance_allowed ? vertex_index : -1);
}


t_map	translate_vertex(t_map map, int vertex_to_mv_index, t_coord new_vertex_pos)
{
	//Add check taking vertex_pos here to confirm convexity and check for intersections.
	map.vertex[vertex_to_mv_index] = new_vertex_pos;
	return (map);
}
