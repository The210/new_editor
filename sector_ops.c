#include "doom.h"

t_map extrude_sector_start(t_map map, t_coord world_pos)
{
  return (line_is_close(map, world_pos)) != -1);
}

//Possible trouble with intersecting lines depending on orientation.
t_map extrude_sector_result(t_map map, t_coord world_pos, int edge_index, t_line new_vertex_vectors)
{
  t_coord new_verterx1;
  t_coord new_vertex2;
  t_coord to_connect;

  new_vertex1.coords.x = world_pos.x + new_vertex_vectors.start.x;
  new_vertex1.coords.y = world_pos.y + new_vertex_vectors.start.y;
  new_vertex2.coords.x = world_pos.x + new_vertex_vectors.end.x;
  new_vertex2.coords.y = world_pos.y + new_vertex_vectors.end.y;

  map.vertex = place_vertex(new_vertex1, map.vertex);
  map.vertex = place_vertex(new_vertex2, map.vertex);
  to_connect.x = map.vertex.length - 1;
  to_connect.y = map.vertex.length - 2;
  map.edge = create_edge(to_connect, map.edge);
  to_connect.x = map.edge[edge_index].x;
  to_connect.y = map.vertex.length - 1;
  map.edge = create_edge(to_connect, map.edge);
  to_connect.x = map.edge[edge_index].y;
  to_connect.y = map.vertex.length - 2;
  map.edge = create_edge(to_connect, map.edge);
  return (map);
}
