/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_man.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:59:46 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/21 22:00:55 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline unsigned int	sample_color(int n)
{
	const unsigned int	palette[] = {0x0, 0x000000FF, 0x0000FF00, 0x00FF0000};

	return (palette[ n % (sizeof(palette) / sizeof(int)) ] );
}

static inline t_cx		scale(double x, double y)
{
	const double	w = WIN_RESX > WIN_RESY ? WIN_RESX : WIN_RESY;
	t_cx	c;

	c.x = (x / w - 0.5L) * 2.0L;
	c.y = (y / w - 0.5L) * 2.0L;
	return (c);
}

static inline int		mandelbrot(int x0, int y0)
{
	t_cx	p0 = scale ((double)(x0), (double)(y0));
	double	x;
	double	y;
	double	x2;
	double	y2;
	int		n;

	x = p0.x;
	y = p0.y;
	x2 = 0.0L;
	y2 = 0.0L;
	n = -1;
	while (++n < MAX_DEPTH && x2 + y2 <= 4.0L)
	{
		y = 2 * x * y + p0.y;
		x = x2 - y2 + p0.x;
		x2 = x * x;
		y2 = y * y;
	}
	return (sample_color(n));
}

void	draw_fractal(t_img *img)
{
	for (int x = 0; x < WIN_RESX; x ++)
		for (int y = 0; y < WIN_RESY; y ++)
			set_pixel (img, x, y, mandelbrot(x, y));
}
