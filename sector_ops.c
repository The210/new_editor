/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:24:46 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/29 02:59:11 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_map		displace_edges(t_map map, int sector_to_change, int edge_index)
{
	int i;

	i = map.sector[sector_to_change].edges_length + 1;
	while (--i > edge_index + 1)
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

t_map		create_new_vertexes(t_map map, int edge_to_extrude_index, t_coord extrude_vector)
{
	t_wall	edge_to_extrude;
	t_coord	new_vertex;

	edge_to_extrude = get_line_coordinates(map, edge_to_extrude_index);
	new_vertex.x = edge_to_extrude.start.x + extrude_vector.x;
	new_vertex.y = edge_to_extrude.start.y + extrude_vector.y;
	map.vertex = place_vertex(new_vertex, map.vertex, map.vertex_length);
	map.vertex_length++;
	new_vertex.x = edge_to_extrude.end.x + extrude_vector.x;
	new_vertex.y = edge_to_extrude.end.y + extrude_vector.y;
	map.vertex = place_vertex(new_vertex, map.vertex, map.vertex_length);
	map.vertex_length++;
	return (map);
}

t_map		connect_new_edges(t_map map, int edge_to_extrude_index)
{
	t_coord vertex_to_connect;

	vertex_to_connect.x = map.edges[edge_to_extrude_index].x;
	vertex_to_connect.y = map.vertex_length - 2;
	map.edges = create_edge(vertex_to_connect, map.edges, map.edges_length);
	map.edges_length++;
	vertex_to_connect.x = map.vertex_length - 2;
	vertex_to_connect.y = map.vertex_length - 1;
	map.edges = create_edge(vertex_to_connect, map.edges, map.edges_length);
	map.edges_length++;
	vertex_to_connect.x = map.vertex_length - 1;
	vertex_to_connect.y = map.edges[edge_to_extrude_index].y;
	map.edges = create_edge(vertex_to_connect, map.edges, map.edges_length);
	map.edges_length++;
	return (map);
}

t_map		create_new_sector(t_map map, int edge_to_extrude)
{
	int i;
	int j;

	map.sector[map.sector_length].num = map.sector_length;
	map.sector[map.sector_length].edges_length = 4;
	map.sector[map.sector_length].ceil_height = 40;
	map.sector[map.sector_length].floor_height = 20;
	if ((map.sector[map.sector_length].edges = (int*)malloc(sizeof(t_coord) * (250))) == NULL)
		exit_on_error();
	i = map.edges_length - 4;
	j = 0;
	while (++i < map.edges_length)
		map.sector[map.sector_length].edges[j++] = i;
	map.sector[map.sector_length].edges[j] = edge_to_extrude;
	map.sector_length++;
	return (map);
}

t_map		extrude_sector(t_map map, int edge_to_extrude, t_coord extrude_start, t_coord extrude_end)
{
	t_coord extrude_vector;

	extrude_vector.x = extrude_end.x - extrude_start.x;
	extrude_vector.y = extrude_end.y - extrude_start.y;
	map = create_new_vertexes(map, edge_to_extrude, extrude_vector);
	map = connect_new_edges(map, edge_to_extrude);
	map = create_new_sector(map, edge_to_extrude); //prolly need otherstuff
	return (map);
}

int			select_edge_to_extrude(t_map map, t_coord mouse_pos)
{
	int i;
	int	min_dist_allowed;
	int	current_dist;
	int min_dist_found;
	t_coord closest_point;
	int	edge_index;

	i = -1;
	min_dist_allowed = 10;
	min_dist_found = 11;
	while (++i < map.edges_length)
	{
		closest_point = get_closest_point_on_line(map, mouse_pos, i);
		if (point_in_segment(map, closest_point, i))
			current_dist = get_point_distance(closest_point, mouse_pos);
		else
			continue;
		//current_dist = better_get_ln_dist(map, mouse_pos, i);
		if (current_dist < min_dist_found)
		{
			min_dist_found = current_dist;
			edge_index = i;
		}
	}
	return (min_dist_found <= min_dist_allowed ? edge_index : -1);
}
