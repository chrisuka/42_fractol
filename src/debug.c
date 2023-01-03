/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:02:39 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/03 13:18:05 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "debug.h"

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

/* Debug mode version of get_sample.
 * In addition to reading a pixel's value, it checks its state
 * set in the pixel's alpha channel. The renderer later colors the pixel
 * a different color according to said state.
 *
 * This helps us visually determine where we have offset errors in the
 * box checking algorithm.
*/
int	debug_get_sample(t_img *img, int x, int y)
{
	const char		emsg[] = CRED "pixel overflow!" CNIL "\n";
	unsigned int	*pxi;

	pxi = ((unsigned int *)(img->addr)) + y * WIN_RESX + x;
	if (x >= WIN_RESX || y >= WIN_RESY)
		write (2, emsg, sizeof(emsg) - sizeof(char));
	if ((*pxi & PX_RMASK) == PX_BRUTE)
		;
	else if ((*pxi & PX_RMASK) != PX_GOOD)
		*pxi |= PX_BAD;
	return (*pxi);
}

/* Debug mode version of sample_fractal.
 * Sample the pixel (x,y) as a point in a fractal set specified by vars
 * and mark it's alpha as PX_BRUTE
 * (meaning this point was evaluated during the brute-force method).
 *
 * Intended to be called only by the brute-force algorithm.
*/
int	debug_sample_fractal(t_vars *v, int x, int y)
{
	int			n;

	if (v->fractal_type == julia_mc)
		n = julia (v->fractal_type,
			scale(x, y, v->view),
			v->view.mouse_complex);
	else
		n = julia (v->fractal_type,
			(t_cx){0.0L, 0.0L},
			scale(x, y, v->view));
	set_pixel (&v->img, x, y, (unsigned int)(n | PX_BRUTE));
	return (n);
}

