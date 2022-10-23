/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_man.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:59:46 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/23 20:18:32 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline unsigned int	sample_color(int n)
{
	const unsigned int	palette[] = {0x0, 0x000000FF, 0x0000FF00, 0x00FF0000};

	return (palette[n % (sizeof(palette) / sizeof(int))]);
}

static inline t_cx	scale(int x, int y, t_vrect view)
{
	const double	w = ft_min(WIN_RESX, WIN_RESY);

	return ((t_cx){
		.x = ((double)(x / w) - 0.5L) * 2.0L * view.zoom /*- 1.5L */+ view.x,
		.y = ((double)(y / w) - 0.5L) * 2.0L * view.zoom + view.y});
}

/* Return a sample indicating whether point c in the complex plane
 * falls inside the Mandelbrot Set, namely how many iterations it took
 *
 * Escape time algorithm: z2 n(c) = z2 + c
 * z = iterating complex function, using its own xy as input
 * z2 = z squared
 * c = complex constant, gets added to z every iteration
*/
static inline int	mandelbrot(t_cx c)
{
	t_cx	z;
	t_cx	z2;
	t_cx	old;
	int		period;
	int		n;

	z = (t_cx){0.0L, 0.0L};
	z2 = (t_cx){0.0L, 0.0L};
	period = 0;
	n = -1;
	while (++n < MAX_DEPTH && z2.x + z2.y <= 4.0L)
	{
		z.y = 2 * z.x * z.y + c.y;
		z.x = z2.x - z2.y + c.x;
		z2.x = (z.x * z.x);
		z2.y = (z.y * z.y);
		if (z2.x == old.x && z2.y == old.y)
			return (sample_color(0));
		period ++;
		if (period > PERIOD)
		{
			old = z2;
			period = 0;
		}
	}
	return (sample_color(n));
}

void	draw_fractal(t_img *img, t_vrect view)
{
	int	x;
	int	y;
	int	n;

	n = -1;
	y = -1;
	while (++y < WIN_RESY)
	{
		x = -1;
		while (++x < WIN_RESX)
			buf_pixel (img, ++n, mandelbrot(scale(x, y, view)));
	}
}
