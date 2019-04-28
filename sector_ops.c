/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:24:46 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/28 04:04:14 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_map		displace_edges(t_map map, int sector_to_change, int edge_index)
{
	int i;

	i = map.sector[sector_to_change].edges_length + 1;
	while (--i > edge_index)
		map.sector[sector_to_change].edges[i] = map.sector[sector_to_change].edges[i - 1];
	return (map);
}

t_map		create_edge_on_sector(t_map map, int sector_to_change, int edge_index)
{
	//To do in case sector has 150 edges re malloc.
	map = displace_edges(map, sector_to_change, edge_index);
	map.sector[sector_to_change].edges[edge_index + 1] = map.edges_length - 1;
	map.sector[sector_to_change].edges_length += 1;
	return (map);
}

int			sector_contains_edge(t_sector sector, int altered_edge)
{
	int i;

	i = -1;
	while(++i < sector.edges_length)
	{
		if (sector.edges[i] == altered_edge)
			return (i);
	}
	return (-1);
}

t_map		add_edge_to_sector(t_map map, int altered_edge)
{
	int i;
	int	edge_index;

	i = -1;
	while (++i < map.sector_length)
	{
		if ((edge_index = (sector_contains_edge(map.sector[i], altered_edge))) != -1)
			map = create_edge_on_sector(map, i, edge_index);
	}
	return (map);
}

int			extrude_sector_start(t_map map, t_coord world_pos)
{
  return ((line_is_close(map, world_pos)) != -1);
}

//Possible trouble with intersecting lines depending on orientation.
t_map		extrude_sector_result(t_map map, t_coord world_pos, int edge_index, t_wall new_vertex_vectors)
{
  t_coord new_vertex1;
  t_coord new_vertex2;
  t_coord to_connect;

  new_vertex1.x = world_pos.x + new_vertex_vectors.start.x;
  new_vertex1.y = world_pos.y + new_vertex_vectors.start.y;
  new_vertex2.x = world_pos.x + new_vertex_vectors.end.x;
  new_vertex2.y = world_pos.y + new_vertex_vectors.end.y;

  map.vertex = place_vertex(new_vertex1, map.vertex, map.vertex_length);
  map.vertex = place_vertex(new_vertex2, map.vertex, map.vertex_length);
  to_connect.x = map.vertex_length - 1;
  to_connect.y = map.vertex_length - 2;
  map.edges = create_edge(to_connect, map.edges, map.edges_length);
  to_connect.x = map.edges[edge_index].x;
  to_connect.y = map.vertex_length - 1;
  map.edges = create_edge(to_connect, map.edges, map.edges_length);
  to_connect.x = map.edges[edge_index].y;
  to_connect.y = map.vertex_length - 2;
  map.edges = create_edge(to_connect, map.edges, map.edges_length);
  return (map);
}
