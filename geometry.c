/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:23:30 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/28 00:17:38 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int get_line_distance(t_map map, t_coord world_pos, int edge_index)
{
	t_wall line;
	int distance;

	line = get_line_coordinates(map, edge_index);
	distance = (abs((line.end.y - line.start.y) * (world_pos.x) - (line.end.x - line.start.x) * (world_pos.y) + (line.end.x * line.start.y) - (line.end.y * line.start.x)) / (sqrt(pow(line.end.y - line.start.y, 2) + pow(line.end.x - line.start.x, 2))));
	return(distance);
}

int	get_point_distance(t_coord a, t_coord b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

int line_is_close(t_map map, t_coord world_pos)
{
	int distance;
	int min_distance;
	int i;
	int closest_edge;

	i = -1;
	min_distance = 25;
	while(++i < map.edges_length)
	{
		distance = get_line_distance(map, world_pos, i);
		if (distance < min_distance)
		{
			min_distance = distance;
			closest_edge = i;
		}
	}
	return (min_distance <= 10 ? closest_edge : -1);
}

/*t_coord get_closest_point_on_line(t_map map, t_coord world_pos, int edge_index)
{
	t_wall line;
	t_coord distance_to_start;
	t_coord line_coords_length;
	t_coord point_on_line;
	double scalar;
	int line_length;

	line = get_line_coordinates(map, edge_index);
	distance_to_start.x = line.start.x - world_pos.x;
	distance_to_start.y = line.start.y - world_pos.y;
	line_coords_length.x = line.end.x - line.start.x;
	line_coords_length.y = line.end.y - line.start.x;
	scalar = (distance_to_start.x * line_coords_length.x) + (distance_to_start.y * line_coords_length.y);
	line_length = sqrt(line_coords_length.x + line_coords_length.y);
	point_on_line.x = line.start.x - ((int)(((scalar) / (pow(line_length, 2))) * line_coords_length.x));
	point_on_line.y = line.start.y - ((int)(((scalar) / (pow(line_length, 2))) * line_coords_length.y));
	return(point_on_line);
}*/

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
