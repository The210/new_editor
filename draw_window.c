/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 20:54:26 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/26 21:10:16 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void draw_square(t_wind wind, t_coord vertex, int square_size)
{
	int i;
	int j;
	t_coord pixel;
	
	pixel.x = vertex.x - (square_size / 2);
	pixel.y = vertex.y - (square_size / 2);
	
	i = -1;
	while (++i < square_size)
	{
		j = -1;
		pixel.x = vertex.x - (square_size / 2);
		while (++j < square_size)
		{
			if (pixel.x >= 0 && pixel.y >= 0 && pixel.x < SCREEN_WIDTH && pixel.x++ < SCREE_HEIGHT)
				put_pixel32(wind.screen, pixel.x, pixel.y, 0xffffff);
		}
		pixel.y++;
	}
}

void draw_edges(t_map map, t_wind wind)
{
	int i;
	t_line line;
	t_wall line;

	line.color = 0xffffff;
	i = -1;
	while (++i < map.edges.length)
	{
		line = get_line_coordinates(map, i);
		ft_draw_line(wind, line.start, line.end, line);
	}
}

void draw_vertex(t_map map, t_wind wind)
{
	int i;

	i = -1;
	while (++i < map.vertex.length)
		draw_square(wind, map.vertex[i]);
}

void draw_window(t_map map, t_wind wind)
{
	//TO DO SdlFillRect
	draw_vertex(map, wind);
	draw_edges(map, wind);
}
