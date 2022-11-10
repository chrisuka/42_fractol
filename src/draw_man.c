/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_man.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:59:46 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/10 02:09:17 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

# define DEBUG 1

/* Return a position representing the
 * screen-space coordinates in the complex plane
 *
 * in practise, remap x/y to -1.0 -> 1.0,
 * then scale with the viewport and a constant to fit it for fractal sampling
 */
static inline t_cx	scale(int x, int y, t_vrect view)
{
	const double	w = (double)ft_min(WIN_RESX, WIN_RESY) * 0.5L;
	const double	amp = 0.01L;

	return ((t_cx){
		.x = (double)(x - w) * amp * view.zoom + view.x,
		.y = (double)(y - w) * amp * view.zoom + view.y});
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

#if 0
static inline void	bset(void *b, uint64_t quad, size_t len)
{
	uint64_t		*quadp;
	unsigned int	uint;

	if (len % sizeof(quad) != 0 && len % sizeof(uint) != 0)
		ft_putendl ("ayo?!");
	uint = (unsigned int)(quad & 0xFFFFFFFF);
	while (len % sizeof(quad) != 0)
	{
		len -= sizeof(uint);
		((unsigned int *)(b))[len] = uint;
	}
	quadp = (uint64_t *)(b);
	while (len)
	{
		len -= sizeof(quad);
		*quadp = quad;
		quadp ++;
	}
}
#endif

static void	draw_rect(t_img *img, t_rect b, unsigned int color)
{
#if 0
	const uint64_t	lcolor = ((uint64_t)(color) | (uint64_t)(color) << 32);
	const int		rowsize = b.w * img->bpp;
	const int		ey = b.y + b.h - 1;
	unsigned int	*pxi;

	//pxi = (((unsigned int *)(img->addr)) + b.y * WIN_RESX + b.x);
	pxi = (unsigned int *)(img->addr);
	pxi += b.y * WIN_RESX + b.x;
	while (b.y <= ey)
	{
		bset (pxi, lcolor, (size_t)(rowsize));
		pxi += WIN_RESX;
		b.y ++;
	}
#else
	for (int x = b.x; x < (b.x + b.w); x ++)
		for (int y = b.y; y < (b.y + b.h); y ++)
			set_pixel (img, x, y, color);
#endif
}

#if DEBUG
static int	sample_fractal_2	(t_vars *v, int x, int y)
{
	int n = mandelbrot(
		scale(x, y, v->view),
		v->view.mouse_complex);
	set_pixel (&v->img, x, y, (unsigned int)(n | 0x02000000));
	return (n);
}
#endif

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
# if DEBUG
	set_pixel (&v->img, x, y, (unsigned int)(n | 0x01000000));
# else
	set_pixel (&v->img, x, y, (unsigned int)(n));
# endif
	return (n);
}

int	get_sample(t_img *img, int x, int y)
{
	unsigned int	*pxi;

	pxi = (unsigned int *)(img->addr);
	pxi += y * WIN_RESX + x;
# if DEBUG
	if (x >= WIN_RESX || y >= WIN_RESY)
		ft_putendl(CRED "pixel overflow!" CNIL);
	// when we lookup a sample, if it's not marked as evaled, mark it as bad
	if ((*pxi & 0xFF000000) == 0x02000000); // ignore 0x02 (brute-forced pixel)
	else if ((*pxi & 0xFF000000) != 0x01000000)
		*pxi |= 0xFF000000;
# endif
	return (*pxi);
}

static void	sample_border(t_vars *v, t_rect b)
{
	const int	ex = b.x + b.w - 1;
	const int	ey = b.y + b.h - 1;
	const int	thin = (b.w == 1);
	const int	flat = (b.h == 1);
	int			n;
	
	n = b.x - 1;
	while (++n <= ex)
	{
		sample_fractal (v, n, b.y);
		if (!flat)
			sample_fractal (v, n, ey);
	}
	n = b.y;
	while (++n < ey)
	{
		sample_fractal (v, b.x, n);
		if (!thin)
			sample_fractal (v, ex, n);
	}
}

static inline int	compare_bounds_eq(t_img *img, t_rect b, int base)
{
	const int	ex = b.x + b.w - 1;
	const int	ey = b.y + b.h - 1;
	int			n;

	n = b.x;
	while (++n <= ex)
	{
		if ((base != get_sample (img, n, b.y))
		||  (base != get_sample (img, n, ey)))
			return (0);
	}
	n = b.y;
	while (++n < ey)
	{
		if ((base != get_sample (img, b.x, n))
		||  (base != get_sample (img,  ex, n)))
			return (0);
	}
	return (1);
}

/* Brute-force method for evaluating a fractal estimate on each pixel within b
 */
void	draw_fractal_simple(t_vars *v, t_rect b)
{
	const int	ex = b.x + b.w - 1;
	const int	ey = b.y + b.h - 1;
	int			x;
	int			y;
	//int			n;

	//n = b.y * WIN_RESX + b.x - 1;
	y = b.y - 1;
	while (++y <= ey)
	{
		x = b.x - 1;
		while (++x <= ex)
		{
#if 0
			buf_pixel (&v->img, ++n, sample_color(mandelbrot(
				(t_cx){0.0L, 0.0L},
				scale (b.x, b.y, v->view)
			)));	
		n += WIN_RESX - b.w;
#else
	# if DEBUG
			sample_fractal_2 (v, x, y);
	# else
			sample_fractal (v, x, y);
	# endif
#endif
		}
	}
}

# if 1
// TODO: replace raw initializations with this

/* Return a copy of rect b with all sides inset (pushed inward) by px pixels
*/
static inline t_rect	r_inset(t_rect b, const int px)
{
	return ((t_rect){
		.x = b.x + px,
		.y = b.y + px,
		.w = b.w - px * 2,
		.h = b.h - px * 2,
	});
}
# endif

/* Mariani-Silver algorithm (DIN approach)
 * Only sample the border pixels of rect b. If all samples are the same,
 * simply fill the box with that sample. Otherwise, split the box
 * and recursively scan the halves.
 *
 * Recursion sides A and B should both use the same dividing line
 * which saves us further processing time.
 *
 * To prevent stack overflow, there is a depth limit after which we
 * use simple xy iteration to sample the remaining area.
 * 
 * All new sample areas are inset so we never calculate the same pixel twice.
*/
void	draw_fractal(t_vars *v, int depth, t_rect b)
{
	const int	split_v = (depth % 2 == 0);
	const int	w_odd = (b.w % 2 == 1);
	const int	h_odd = (b.h % 2 == 1);
	int			base_n;

	if (depth == 0)
		sample_border (v, b);
	base_n = get_sample (&v->img, b.x, b.y);

	if (compare_bounds_eq (&v->img, b, base_n))
		return (draw_rect(&v->img, r_inset (b, 1), (unsigned int)(base_n)));

	if (depth >= SUBDIV_DEPTH || b.w <= SUBD_RES || b.h <= SUBD_RES)
		return (draw_fractal_simple (v, r_inset (b, 1)));

	b.w >>= split_v;
	b.h >>= !split_v;
	if (split_v)
		sample_border (v, (t_rect){
			b.x + b.w,
			b.y + 1,
			1, b.h - 2});
	else
		sample_border (v, (t_rect){
			b.x + 1,
			b.y + b.h,
			b.w - 2, 1});

	draw_fractal (v, depth + 1, (t_rect){
		b.x, b.y,
		b.w + split_v, b.h + !split_v});

	draw_fractal (v, depth + 1, (t_rect){
		b.x + (b.w * split_v),
		b.y + (b.h * !split_v), b.w + (w_odd && split_v), b.h + (h_odd && !split_v)});
}
