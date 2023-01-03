/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:09:17 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/03 18:35:33 by ikarjala         ###   ########.fr       */
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
	const double	w = (double)(ft_min(WIN_RESX, WIN_RESY) * 0.5L);
	const double	amp = (double)(0.01L);

	return ((t_cx){
		.x = (double)(x - w) *amp * view.zoom + view.x,
		.y = (double)(y - w) *amp * view.zoom + view.y});
}

int	get_sample(t_img *img, int x, int y)
{
	const unsigned int	*pxi;

	pxi = ((unsigned int *)(img->addr)) + y * WIN_RESX + x;
	return ((int)(*pxi));
}

int	sample_fractal(t_vars *v, int x, int y)
{
	int	n;

	if (v->fractal_type == julia_mc)
		n = julia (v->fractal_type,
				scale (x, y, v->view),
				v->view.mouse_complex);
	else
		n = julia (v->fractal_type,
				(t_cx){0.0L, 0.0L},
				scale (x, y, v->view));
	if (v->debug)
		set_pixel (&v->img, x, y, (unsigned int)(n | PX_GOOD));
	else
		set_pixel (&v->img, x, y, (unsigned int)(n));
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
