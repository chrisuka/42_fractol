/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:59:31 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/23 00:43:39 by ikarjala         ###   ########.fr       */
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
