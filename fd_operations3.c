/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_operations3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 09:16:37 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/04 09:17:01 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	write_player(t_map map, int fd)
{
	ft_putstr_fd("player ", fd);
	ft_putnbr_fd(map.player.pos.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(map.player.pos.y, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(map.player.sector_num, fd);
	ft_putstr_fd(" z", fd);
	ft_putchar_fd('\n', fd);
}

void	write_sprites_globales(t_map map, int fd)
{
	int i;

	i = -1;
	while (++i < map.sprite_g_len)
	{
		ft_putstr_fd("object ", fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.g_sprite[i].pos.x, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.g_sprite[i].pos.y, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(map.g_sprite[i].sector_num, fd);
		ft_putstr_fd(" z", fd);
		ft_putchar_fd('\n', fd);
	}
}
