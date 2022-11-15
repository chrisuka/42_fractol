/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:59:31 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/15 23:28:52 by ikarjala         ###   ########.fr       */
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
#if 0
	const uint64_t	lcolor = ((uint64_t)(color) | (uint64_t)(color) << 32);
	const int		rowsize = b.w * img->bpp;
	const int		ey = b.y + b.h - 1;
	unsigned int	*pxi;

#if 0
	pxi = (((unsigned int *)(img->addr)) + b.y * WIN_RESX + b.x);
#else
	pxi = (unsigned int *)(img->addr);
	pxi += b.y * WIN_RESX + b.x;
#endif
	while (b.y <= ey)
	{
		ft_bset64 (pxi, lcolor, (size_t)(rowsize));
		pxi += WIN_RESX;
		b.y ++;
	}
#else
	for (int x = b.x; x < (b.x + b.w); x ++)
		for (int y = b.y; y < (b.y + b.h); y ++)
			set_pixel (img, x, y, color);
#endif
}

