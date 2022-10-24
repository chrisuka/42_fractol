/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_man.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:59:46 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/25 00:37:50 by ikarjala         ###   ########.fr       */
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
#if 0
	const double	w = ft_min(WIN_RESX, WIN_RESY);
	return ((t_cx){
		.x = ((double)(x / w) - 0.5L) * 2.0L * view.zoom - 0.75L + view.x,
		.y = ((double)(y / w) - 0.5L) * 2.0L * view.zoom + view.y});
#else
	const double	w = ft_min(WIN_RESX, WIN_RESY) * 0.5L;

	return ((t_cx){
		.x = (double)(x - w) * 0.01L * view.zoom + view.x,
		.y = (double)(y - w) * 0.01L * view.zoom + view.y});
#endif
}

/* Return a sample indicating whether point c in the complex plane
 * falls inside the Mandelbrot Set, namely how many iterations it took
 *
 * Escape time algorithm: z2 n(c) = z2 + c
 * z = iterating complex function, using its own xy as input
 * z2 = z squared
 * c = complex constant, gets added to z every iteration
*/
static inline int	mandelbrot(t_cx c, t_cx z)
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

#if 0
static t_cx	mouse_scale(t_cx in)
{
# if 1
	in.x = (in.x - WIN_RESX * 0.5L) * 0.01L;
	in.y = (in.y - WIN_RESY * 0.5L) * 0.01L;
# else
	const double	w = ft_min(WIN_RESX, WIN_RESY);

	in.x = ((double)(in.x / w) - 0.5L) * 2.0L;
	in.y = ((double)(in.y / w) - 0.5L) * 2.0L;
# endif
	return (in);
}
#endif

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
			buf_pixel (img, ++n, mandelbrot(
				scale(view.cx_input.x, view.cx_input.y, view),
				scale(x, y, view)));
			//buf_pixel (img, ++n, mandelbrot(scale(x, y, view), (t_cx){0.0L, 0.0L}));
	}
}
#else
static inline t_rect	r_add(t_rect b, int x, int y)
{
	return ((t_rect){
		.x = b.x + x,
		.y = b.y + y,
		.w = b.w,
		.h = b.h});
}

static void	draw_rect(t_img *img, t_rect b, unsigned int color)
{
	t_uint64	fc;
	int			y;

	fc = (t_uint64)(color | color << 32);
	pxi = addr + y * WIN_RESX + (b.x + 1) * img->bpp;
	y = -1;
	while (++y < b.h)
	{
		ft_bset64 (pxi, fc, w);
		pxi += WIN_RESX - w;
	}
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
void	draw_fractal(t_img *img, t_vrect view, t_rect b, int depth)
{
	int	x;
	int	y;
	int	res;
	int	fst;
	int	sample_diff = 0;

	if (depth >= SUBDIV_DEPTH || b.w < SUBD_RES || b.h < SUBD_RES)
		return (draw_fractal_simple(b));
	fst = sample_fractal (0, 0);
	x = b.x - 1;
	while (++x < b.w)
	{
		res = sample_fractal (x, 0);
		res = sample_fractal (x, b.h - 1);
		sample_diff |= (res != fst);
	}
	y = b.y - 1;
	while (++y < b.h)
	{
		res = sample_fractal (0,       y);
		res = sample_fractal (b.w - 1, y);
	}
	if (!sample_diff)
		return (draw_rect(img, b, res));
		// b.xy + 1 -> b.wh - 1

	b.w >>= 1;
	b.h >>= 1;
	draw_fractal (img, view, r_add(b, 0, 0));
	draw_fractal (img, view, r_add(b, b.w, 0));
	draw_fractal (img, view, r_add(b, 0, b.h));
	draw_fractal (img, view, r_add(b, b.w, b.h));
}
#endif
