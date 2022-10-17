/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:59:31 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/17 19:03:30 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int	inside_frame(int x, int y)
{
	return (x >= 0 && x < WIN_RESX
		&& y >= 0 && y < WIN_RESY);
}

void	set_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	if (!inside_frame(x, y))
		return ;
	px = img->addr + (y * img->width + x * img->bpp);
	*(unsigned int *)(px) = color;
}
