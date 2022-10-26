/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_man.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:59:46 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/26 18:19:22 by ikarjala         ###   ########.fr       */
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
	const double	w = ft_min(WIN_RESX, WIN_RESY) * 0.5L;

	return ((t_cx){
		.x = (double)(x - w) * 0.01L * view.zoom + view.x,
		.y = (double)(y - w) * 0.01L * view.zoom + view.y});
}

/* Return a sample indicating whether point c in the complex plane
 * falls inside the Mandelbrot Set, namely how many iterations it took
 *
 * Escape time algorithm: z2 n(c) = z2 + c
 * z = iterating complex function, using its own xy as input
 * z2 = z squared
 * c = complex constant, gets added to z every iteration
*/
static inline int	mandelbrot(t_cx z, t_cx c)
{
	t_cx	z2;
	t_cx	old;
	int		period;
	int		n;

	//z = (t_cx){0.0L, 0.0L};
	z2 = (t_cx){z.x * z.x, z.y * z.y};
	period = 0;
	n = -1;
	while (++n < MAX_DEPTH && z2.x + z2.y <= 4.0L)
	{
		z.y = 2 * z.x * z.y + c.y;
		z.x = z2.x - z2.y + c.x;
		z2.x = (z.x * z.x);
		z2.y = (z.y * z.y);
		if (z2.x == old.x && z2.y == old.y)
			return (MAX_DEPTH);
		period ++;
		if (period > PERIOD)
		{
			old = z2;
			period = 0;
		}
	}
	return (n);
}

#if 1
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
#if 1
			buf_pixel (img, ++n, sample_color(mandelbrot(
				scale(x, y, view),
				view.mouse_complex)));
#else
			buf_pixel (img, ++n, mandelbrot(
				(t_cx){0.0L, 0.0L},
				scale(x, y, view)));
#endif
	}
}
#else
static inline t_rect	r_split(t_rect b, int is_vertical)
{
	if (is_vertical)
		return ((t_rect){
		.x = b.x + b.w * !b.side,
		.y = b.y,
		.w = b.w >> 1,
		.h = b.h,
		.base_n = b.base_n});
	else
		return ((t_rect){
		.x = b.x,
		.y = b.y + b.h * !b.side,
		.w = b.w,
		.h = b.h >> 1,
		.base_n = b.base_n});
}

static void	draw_rect(t_img *img, t_rect b, unsigned int color)
{
#if 0
	const uint64_t	dcolor = ((uint64_t)(color) | (uint64_t)(color) << 32);
	unsigned int	*pxi;

	pxi = (unsigned int *)(img->addr + b.y * WIN_RESX + b.x);
	while (b.y < b.h)
	{
		ft_bset64 (pxi, dcolor, b.w);
		pxi += WIN_RESX - b.w;
		b.y ++;
	}
#else
	for (int x = 0; x < b.w; x ++)
		for (int y = 0; y < b.h; y ++)
			set_pixel (img, b.x + x, b.y + y, color);
#endif
}

void	draw_fractal_simple(t_vars *v, t_rect b)
{
	//int	n;

	//n = b.y * WIN_RESX + b.x - 1;
	b.y = -1;
	while (++b.y < WIN_RESY)
	{
		b.x = -1;
		while (++b.x < WIN_RESX)
#if 0
			buf_pixel (&v->img, ++n, sample_color(mandelbrot(
				(t_cx){0.0L, 0.0L},
				scale (b.x, b.y, v->view)
			)));	
		n += WIN_RESX - b.w;
#else
			set_pixel (&v->img, b.x, b.y, sample_color(mandelbrot(
				scale(b.x, b.y, v->view),
				v->view.mouse_complex
			)));
#endif
	}
}

static int	sample_fractal(t_vars *v, int x, int y)
{
	int	n;

#if 0
	n = mandelbrot(
		(t_cx){0.0L, 0.0L},
		scale(x, y, v->view));
#else
	n = mandelbrot(
		scale(x, y, v->view),
		v->view.mouse_complex);
#endif
	set_pixel (&v->img, x, y, sample_color(n));
	return (n);
}

/* Mariani-Silver algorithm
 * Only sample the border pixels of the screen. If all samples are the same,
 * Simply fill the box with that color. Otherwise, subdivide the screen into
 * 4 smaller rects, and recursively scan the subdivisions.
 *
 * Depending on the corner of the subdivision, we can also reuse some of
 * the borders calculated earlier.
 *
 * To prevent stack overflow, there is a depth limit after which we
 * use simple xy iteration to sample the remaining area.
*/
void	draw_fractal(t_vars *v, int depth, t_rect b, int mask)
//void	draw_fractal(t_vars *v, int base_sample, int depth, t_rect b)
{
	int	sample_diff;
	int	n;

	if (depth >= SUBDIV_DEPTH || b.w <= SUBD_RES || b.h <= SUBD_RES)
		return (draw_fractal_simple (v, b));
	if (b.base_n < 0)
		b.base_n = sample_fractal (v, b.x + (b.w >> 1), b.y + (b.h >> 1));

	/*
	ft_putstr("depth: ");
	ft_putnbr(depth);
	ft_putendl("");*/

	sample_diff = 0;
	n = b.x - 1;
	if ( CURRENT SUBDIVISION IS VERTICAL)
	{
	while (++n < b.x + b.w)
		sample_diff |= (b.side == 0 && b.base_n != sample_fractal(v, n, 0))
					| (b.side == 1 && b.base_n != sample_fractal (v, n, b.h - 1));
	}
	else
	{
	n = b.y - 1;
	while (++n < b.y + b.h)
		sample_diff |= ((mask & 1) == 0 && b.base_n != sample_fractal(v, 0,       n))
					| ((mask & 4) == 0 && b.base_n != sample_fractal (v, b.w - 1, n));
	}
	if (!sample_diff)
	{
		ft_putendl("no diff");
		return (draw_rect(&v->img, b, sample_color(b.base_n)));
	}
	draw_fractal (v, depth + 1, r_split(b, 1), b.side);
	draw_fractal (v, depth + 1, r_split(b, 0), b.side);
}
#endif
