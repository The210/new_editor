/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:24:46 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/27 20:24:47 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int extrude_sector_start(t_map map, t_coord world_pos)
{
  return ((line_is_close(map, world_pos)) != -1);
}

//Possible trouble with intersecting lines depending on orientation.
t_map extrude_sector_result(t_map map, t_coord world_pos, int edge_index, t_wall new_vertex_vectors)
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
