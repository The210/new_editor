/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:33:46 by dhorvill          #+#    #+#             */
/*   Updated: 2019/04/26 21:23:10 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "SDL.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000


typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef	struct	s_line
{
	float		dx;
	int			sx;
	float		dy;
	int			sy;
	float		m;
	float		pb;
	int			intm;
	int			intb;
	int			color;
	t_coord		offset;
}				t_line;

typedef struct	s_wind
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	SDL_Surface	*used;
	SDL_Event	event;
}				t_wind;

typedef struct	s_sector
{
	int			num;
	double		ceil_height;
	double		floor_height;
	t_coord		*edges;
}				t_sector;

typedef struct	s_map
{
	t_coord		*vertex;
	t_coord		*edges;
	t_sector	*sector;
	int			vertex_length;
	int			edges_length;
	int			sector_length;
}				t_map;

int		ft_draw_line(t_wind wind, t_coord point, t_coord next_point, t_line line);
t_map	create_edge(t_coord vertex_indexes, t_coord *edges); // Check this out!
t_map	divide_line(t_map map, int edge_index);
int		get_line_distance(t_map map, t_coord world_pos, int edge_index);
int		line_is_close(t_map map, t_coord world_pos);
t_coord get_closest_point_on_line(t_map map, t_coord world_pos, int edge_index);
void	draw_window(t_map map, t_wind wind);
void	write_vertexes(t_map map, int fd);
t_wind	init_wind(t_wind wind);
