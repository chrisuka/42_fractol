/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 02:04:07 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/12 02:06:42 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Return a sample indicating whether point c in the complex plane
 * falls inside the Mandelbrot Set, namely how many iterations it took
 *
 * Escape time algorithm: z2 n(c) = z2 + c
 * z = iterating complex function, using its own xy as input
 * z2 = z squared
 * c = complex constant, gets added to z every iteration
*/
int	mandelbrot(t_cx z, t_cx c)
{
	t_cx	z2;
	t_cx	old;
	int		period;
	int		n;

	z2 = (t_cx){z.x * z.x, z.y * z.y};
	period = 0;
	n = -1;
	while (++n < MAX_DEPTH && z2.x + z2.y <= 4.0L)
	{
		z.y = 2 * z.x * z.y + c.y;
		z.x = z2.x - z2.y + c.x;
		z2.x = (z.x * z.x);
		z2.y = (z.y * z.y);
		// WARN: old is uninitialized!!
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

// TODO: remember to make this back into inline!
