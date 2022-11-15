/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_man.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:59:46 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/15 23:07:20 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

static inline int	border_equ(t_img *img, t_rect b, int base)
{
	const int	ex = b.x + b.w - 1;
	const int	ey = b.y + b.h - 1;
	int			n;

	n = b.x;
	while (++n <= ex)
	{
		if ((base != get_sample (img, n, b.y))
			|| (base != get_sample (img, n, ey)))
			return (0);
	}
	n = b.y;
	while (++n < ey)
	{
		if ((base != get_sample (img, b.x, n))
			|| (base != get_sample (img, ex, n)))
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
	//int		n;

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
#else
	# if DEBUG
			sample_fractal_2 (v, x, y);
	# else
			sample_fractal (v, x, y);
	# endif
#endif
		}
		//n += WIN_RESX - b.w;
	}
}

/* Return the bounds of a horizontal or vertical division line for rect b.
*/
static inline t_rect	r_splitter(t_rect b, const int vertical)
{
	if (vertical)
		return ((t_rect){
			b.x + b.w,
			b.y + 1,
			1,
			b.h - 2
		});
	return ((t_rect){
		b.x + 1,
		b.y + b.h,
		b.w - 2,
		1
	});
}

/* Mariani-Silver algorithm (DIN approach)
 * Only sample the border pixels of rect b. If all samples are the same,
 * simply fill the box with that sample. Otherwise, split the box
 * and recursively scan the halves.
 *
 * Recursion sides A and B should both use the same dividing line and borders
 * which saves us further processing time.
 *
 * To prevent stack overflow, there is a depth limit after which we
 * use simple xy iteration to sample the remaining area.
 * 
 * All new sample areas are inset so we never calculate the same pixel twice.
*/
void	draw_fractal(t_vars *v, int depth, t_rect b)
{
	const int	*o_px = ((int *)(v->img.addr)) + b.y * WIN_RESX + b.x;
	const int	split_v = (depth % 2 == 0);
	const int	w_odd = (b.w % 2 == 1);
	const int	h_odd = (b.h % 2 == 1);

	if (depth == 0)
		sample_border (v, b);
	if (border_equ (&v->img, b, *o_px))
		return (draw_rect (&v->img, r_inset (b, 1), *o_px));
	if (depth >= SUBDIV_DEPTH || (b.w <= SUBD_RES && b.h <= SUBD_RES))
		return (draw_fractal_simple (v, r_inset (b, 1)));
	b.w >>= split_v;
	b.h >>= !split_v;
	sample_border (v, r_splitter (b, split_v));

	draw_fractal (v, depth + 1, (t_rect){
		b.x, b.y, b.w + split_v, b.h + !split_v});

	draw_fractal (v, depth + 1, (t_rect){
		b.x + (b.w * split_v), b.y + (b.h * !split_v),
		b.w + (w_odd && split_v), b.h + (h_odd && !split_v)});
}
