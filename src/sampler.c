/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:09:17 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/12 21:19:09 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int	get_sample(t_img *img, int x, int y)
{
	unsigned int	*pxi;

	pxi = ((unsigned int *)(img->addr)) + y * WIN_RESX + x;
# if DEBUG
	if (x >= WIN_RESX || y >= WIN_RESY)
		ft_putendl (CRED "pixel overflow!" CNIL);
	// when we lookup a sample, if it's not marked as evaled, mark it as bad
	if ((*pxi & 0xFF000000) == 0x02000000); // ignore 0x02 (brute-forced pixel)
	else if ((*pxi & 0xFF000000) != 0x01000000)
		*pxi |= 0xFF000000;
# endif
	return (*pxi);
}

#if DEBUG
int	sample_fractal_2	(t_vars *v, int x, int y)
{
	int n = mandelbrot(
		scale(x, y, v->view),
		v->view.mouse_complex);
	set_pixel (&v->img, x, y, (unsigned int)(n | 0x02000000));
	return (n);
}
#endif

int	sample_fractal(t_vars *v, int x, int y)
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

void	sample_border(t_vars *v, t_rect b)
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

