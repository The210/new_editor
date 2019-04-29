/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:23:30 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/29 02:45:57 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	dot_product(t_coord a, t_coord b)
{
	return (a.x * b.x + a.y * b.y);
}

int	vector_cross_product(t_wall a, t_wall b)
{
	t_coord a_to_middle;
	t_coord middle_to_b;

	a_to_middle.x = a.end.x - a.start.x;
	a_to_middle.y = a.end.y - a.start.y;
	middle_to_b.x = b.end.x - b.start.x;
	middle_to_b.y = b.end.y - b.start.y;

	return(a_to_middle.x * middle_to_b.y - middle_to_b.x * a_to_middle.y);
}

int	get_point_distance(t_coord a, t_coord b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

int	point_in_segment(t_map map, t_coord point_in_line, int edge_index)
{
	double distance_to_start;
	double distance_to_end;
	double segment_distance;

	distance_to_start = get_point_distance(point_in_line, map.vertex[map.edges[edge_index].x]);
	distance_to_end = get_point_distance(point_in_line, map.vertex[map.edges[edge_index].y]);
	segment_distance = get_point_distance(map.vertex[map.edges[edge_index].x], map.vertex[map.edges[edge_index].y]);
	if (distance_to_start < segment_distance && distance_to_end < segment_distance)
		return (1);
	return (0);
}

int min (int a, int b)
{
	return (a > b ? b : a);
}

int	max(int a, int b)
{
	return (a > b ? a : b);
}

int	better_get_ln_dist(t_map map, t_coord mouse_pos, int edge_index)
{
	t_wall line;
	int line_length_sq;
	double t;
	int distance;
	t_coord to_point;
	t_coord to_end;
	t_coord projection;

	line = get_line_coordinates(map, edge_index);
	to_point.x = mouse_pos.x - line.start.x;
	to_point.y = mouse_pos.y - line.start.y;
	to_end.x = line.end.x - line.start.x;
	to_end.y = line.end.y - line.start.y;

	line_length_sq = pow(line.end.x - line.start.x, 2) + pow(line.end.y - line.start.y, 2);
	
	t = max(0, min(1, dot_product(to_point, to_end) / line_length_sq));
	projection.x = line.start.x + t * (to_end.x);
	projection.y = line.start.y + t * (to_end.y);
	return (get_point_distance(projection, mouse_pos));
}

int get_line_distance(t_map map, t_coord world_pos, int edge_index)
{
	t_wall line;
	int distance;

	line = get_line_coordinates(map, edge_index);
	distance = (abs((line.end.y - line.start.y) * (world_pos.x) - (line.end.x - line.start.x) * (world_pos.y) + (line.end.x * line.start.y) - (line.end.y * line.start.x)) / (sqrt(pow(line.end.y - line.start.y, 2) + pow(line.end.x - line.start.x, 2))));
	return(distance);
}

int line_is_close(t_map map, t_coord world_pos, int i)
{
	int distance;
	int min_distance;
	int closest_edge;

	min_distance = 25;
	while (++i < map.edges_length)
	{
		distance = get_line_distance(map, world_pos, i);
		if (distance < min_distance)
		{
			min_distance = distance;
			closest_edge = i;
			if (min_distance <= 10)
				return (i);
		}
	}
	return (min_distance <= 10 ? closest_edge : -1);
}

t_coord	get_closest_point_on_line(t_map map, t_coord world_pos, int edge_index)
{
	t_wall	line;
	t_coord start_to_point;
	t_coord	line_vector;
	t_coord result;
	double t;
	double stp_dot_ste;
	double squared_line_distance;

	line = get_line_coordinates(map, edge_index);
	start_to_point.x = world_pos.x - line.start.x;
	start_to_point.y = world_pos.y - line.start.y;
	line_vector.x = line.end.x - line.start.x;
	line_vector.y = line.end.y - line.start.y;

	squared_line_distance = pow(line_vector.x, 2) + pow(line_vector.y, 2);
	stp_dot_ste = start_to_point.x * line_vector.x + start_to_point.y * line_vector.y;

	t = stp_dot_ste / squared_line_distance;

	result.x = (int)(line.start.x + line_vector.x * t);
	result.y = (int)(line.start.y + line_vector.y * t);
	return (result);
}
