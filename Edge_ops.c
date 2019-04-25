#include "doom.h"

t_map create_edge(t_coord vertex_indexes, t_edlist edges)
{
  t_edlist new_edlist;
  int i;

  if (edges.length > 0)
  {
    new_edlist.coords = (t_coord*)malloc(sizeof(t_coord) * (edges.length + 11));
    i = -1;
    while (++i < edges.length)
      new_edlist.coords[i] = edges.coords[i];
    new_edlist.length = edges.length + 1;
    new_edlist.coords[new_edlist.length - 1].x = vertex_indexes.x;
    new_edlist.coords[new_edlist.length - 1].y = vertex_indexes.y;
    free(&edges.coords);
    free(&edges.length);
    free(&edges);
  }
  else
  {
    new_edlist.coords = (t_coord*)malloc(sizeof(t_coord) * 10);
    new_edlist.length = 1;
    new_edlist.coords[0].x = vertex_indexes.x;
    new_edlist.coords[0].y = vertex_indexes.y;
  }
  return(new_edlist);
}

t_map divide_line(t_map map, int edge_index)
{
  t_coord tmp;
  tmp.x = map.vertex.length - 1;
  tmp.y = map.edge[edge_index].coords.y;
  map.edge[edge_index].coords.y = tmp.x;

  map.edge = create_edge(tmp, map.edge);
  return (map);
}
