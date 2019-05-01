/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:45:57 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/01 00:33:02 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		in_sector(t_map map, t_coord point)
{
	t_coord	infinite;
	t_wall	sector_edge;
	int		i;
	int		j;
	int		intersection_count;

	infinite.y = point.y;
	infinite.x = 200000;
	i = -1;
	while (++i < map.sector_length - 1)
	{
		j = -1;
		intersection_count = 0;
		while (++j < map.sector[i].edges_length)
		{
			sector_edge = get_line_coordinates(map, map.sector[i].edges[j]);
			if (line_intersects(point, infinite, sector_edge.start, sector_edge.end))
				intersection_count++;
		}
		if (intersection_count == 1)
			return (i);
	}
	return (-1);
}

int		in_sector_full(t_map map, t_coord point)
{
	t_coord	infinite;
	t_wall	sector_edge;
	int		i;
	int		j;
	int		intersection_count;

	infinite.y = point.y;
	infinite.x = 200000;
	i = -1;
	while (++i < map.sector_length)
	{
		j = -1;
		intersection_count = 0;
		while (++j < map.sector[i].edges_length)
		{
			sector_edge = get_line_coordinates(map, map.sector[i].edges[j]);
			if (line_intersects(point, infinite, sector_edge.start, sector_edge.end))
				intersection_count++;
		}
		if (intersection_count == 1)
			return (i);
	}
	return (-1);
}
