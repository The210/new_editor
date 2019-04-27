/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_vertex_to_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:24:55 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/27 20:24:56 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void write_start_coordinate(t_coord pos, int fd)
{
  ft_putstr_fd("vertex ", fd);
  ft_putnbr_fd(pos.y, fd);
  ft_putchar_fd(' ', fd);
  ft_putnbr_fd(pos.x, fd);
  ft_putchar_fd(' ', fd);
}

void write_x_coordinate(int x, int fd)
{
  ft_putnbr_fd(x, fd);
  ft_putchar_fd(' ', fd);
}

void write_vertexes(t_map map, int fd)
{
  t_coord pos_to_write;
  int i;
  int j;

  i = -1;
  while (++i < map.vertex_length)
  {
    pos_to_write = map.vertex[i];
    if (pos_to_write.y == -5908)
      continue;
    write_start_coordinate(pos_to_write, fd);
    map.vertex[i].y = -5908;
    j = -1;
    while(++j < map.vertex_length)
    {
      if (map.vertex->y == pos_to_write.y)
      {
        map.vertex->y = -5908;
        write_x_coordinate(map.vertex->x, fd);
      }
    }
    ft_putchar_fd('\n', fd);
  }
}
