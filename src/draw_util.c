/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:27:27 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/03 16:27:39 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	px = img->addr + (y * img->width + x * img->bpp);
	*(unsigned int *)(px) = color;
}

void	buf_pixel(t_img *img, int n, unsigned int color)
{
	((unsigned int *)(img->addr))[n] = color;
}

void	draw_rect(t_img *img, t_rect b, unsigned int color)
{
	const int		ex = b.x + b.w - 1;
	const int		ey = b.y + b.h - 1;
	unsigned int	*pxi;
	int				x;

	pxi = ((unsigned int *)(img->addr)) + b.y * WIN_RESX + b.x;
	while (b.y <= ey)
	{
		x = b.x;
		while (x++ <= ex)
			*(pxi++) = color;
		pxi += WIN_RESX - b.w;
		b.y ++;
	}
}
