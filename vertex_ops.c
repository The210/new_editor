#include "doom.h"

t_vlist place_vertex(t_coord new_vertex_pos, t_vlist vertex)
{
  t_vlist new_vlist;
  int i;

  if (vertex.length > 0)
  {
    new_vlist.coords = (t_coord*)malloc(sizeof(t_coord) * (vertex.length + 11));
    i = -1;
    while (++i < vertex.length)
      new_vlist.coords[i] = vertex.coords[i];
    new_vlist.length = vertex.length + 1;
    new_vlist.coords[new_vlist.length - 1].x = new_vertex_pos.x;
    new_vlist.coords[new_vlist.length - 1].y = new_vertex_pos.y;
    free(&vertex.coords);
    free(&vertex.length);
    free(&vertex);
  }
  else
  {
    new_vlist.coords = (t_coord*)malloc(sizeof(t_coord) * 10);
    new_vlist.length = 1;
    new_vlist.coords[0].x = new_vertex_pos.x;
    new_vlist.coords[0].y = new_vertex_pos.y;
  }
  return(new_vlist);
}

t_wall get_line_coordinates(t_map map, int i)
{
  t_wall line;

  line.start.x = map.vertex[map.edge[i].start].x;
  line.start.y = map.vertex[map.edge[i].start].y;
  line.end.x = map.vertex[map.edge[i].end].x;
  line.end.y = map.vertex[map.edge[i].end].y;
  return(line);
}

t_map create_mid_vertex(t_map map, int edge_index, t_coord point_on_line)
{
  map.vertex = place_vertex(point_on_line, new_vertex_pos);

}

t_map create_mid_line_vertex(t_map map, t_coord world_pos)
{
  int edge_index;
  t_coord point_on_line;

  if((edge_index = line_is_close) != -1)
  {
    point_on_line = get_closest_point_on_line(map, world_pos, edge_index);
    map = create_mid_vertex(map, edge_index, point_on_line)
  }
}
