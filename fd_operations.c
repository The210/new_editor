/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 05:08:57 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/01 06:01:24 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	write_vertex(t_map map, int fd)
{
	int i;
	int j;

	while (++i < map.vertex_length)
	{
		ft_putstr_fd("vertex ", fd);
		ft_putnbr_fd(map.vertex[i].y, fd);
		ft_putchar_fd(" ", fd);
		ft_putnbr_fd(map.vertex[i].x, fd);
		j = i;
		while (++j < map.vertex_length)
		{
			if(map.vertex[i].y == map.vertex[j].y)
			{
				ft_putchar_fd(" ", fd);
				ft_putnbr_fd(map.vertex[j].x);
			}
		}
		ft_putchar_fd("\n");
	}
}

void	write_edges(t_map map, int i, int fd)
{

}

void	write_sectors(t_map map, int fd)
{
	int i;

	i = -1;
	while (++i < map.sector_length)
	{
		ft_putstr_fd("sector ");
		ft_putchar_fd(" ", fd);
		ft_putnbr_fd(map.sector[i].floor_height, fd);
		ft_putchar_fd(" ", fd);
		ft_putnbr_fd(map.sector[i].ceil_height, fd);
		ft_putchar_fd(" ", fd);
		write_edges(map, i, fd);
	}
}

void	write_player(t_map map, int fd)
{
	ft_putstr_fd("player ");
	ft_putnbr_fd(map.player.pos.x, fd);
	ft_putchar_fd(" ", fd);
	ft_putnbr_fd(map.player.pos.y, fd);
	ft_putchar_fd(" ", fd);
	ft_putnbr_fd(map.player.angle, fd);
	ft_putchar_fd(" ", fd);
	ft_putnbr_fd(map.player.sector_num, fd);
	ft_puchar_fd("\n", fd);
}

void	write_sprites_globales(t_map map, int fd)
{
	int i;

	i = -1;
	while (++i < map.sprite_g_len)
	{
		ft_putstr_fd("sprite ");
		ft_putnbr(map.g_sprite[i].pos.x);
		ft_putchar_fd(" ", fd);
		ft_putnbr_fd(map.g_sprite[i].pos.y);
		ft_putchar_fd(" ", fd);
		ft_putnbr_fd(map.g_sprite[i].sector_num, fd);
		ft_putchar_fd("\n", fd);
	}
}

void	write_fd(t_map map, int fd)
{
	write_vertex(map, fd);
	write_sectors(map, fd);
	write_player(map, fd);
	write_sprites_globales(map, fd);
}
