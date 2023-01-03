/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:19:08 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/03 18:34:31 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline unsigned int	eval_color(int n)
{
	return ((unsigned int)
		(n * 5 | (n * 10) << 8 | (n * 20) << 16)
		& ~PX_RMASK);
}

static inline unsigned int	debug_eval_color(int n)
{
	const int	meta = n & (int)PX_RMASK;

	if (meta == (int)PX_BAD)
		return (0x00FF0000);
	else if (meta == (int)PX_BRUTE)
		return (eval_color (n) >> 1);
	return (eval_color (n));
}

void	render_colors(t_img *img, t_rect b, int debug)
{
	unsigned int	(*f)(int);
	const int		ex = b.x + b.w;
	const int		ey = b.y + b.h;
	int				x;
	int				y;

	if (debug)
		f = &debug_eval_color;
	else
		f = &eval_color;
	y = b.y - 1;
	while (++y < ey)
	{
		x = b.x - 1;
		while (++x < ex)
		{
			set_pixel (img, x, y, f (
					get_sample (img, x, y))
				);
		}
	}
}
