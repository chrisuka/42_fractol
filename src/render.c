/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:19:08 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/14 21:03:51 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline unsigned int	eval_color(int n)
{
#if 0
	const unsigned int	palette[] = {0x0, 0x000000FF, 0x0000FF00, 0x00FF0000};

	return (palette[n % (sizeof(palette) / sizeof(int))]);
#else
		return (
# if 0
			(n * 5 | (n * 10) << 8 | (n * 20) << 16)
# else
			(n * 5 | (n * 10) << 8 | (n * 20) << 16)
# endif
			& 0x00FFFFFF);
#endif
}

#if 0
static inline void	clear_alpha(t_img *img, size_t buf_size)
{
	const unsigned int	mask = (0xFF000000);
	unsigned int		*px;

	px = (unsigned int *)(img->addr);
	while (buf_size--)
		img->addr[buf_size] &= ~mask;
}
#endif

#if 0
static inline unsigned int	cmul(unsigned int color, double f)
{
	return (
			((unsigned int)(color * f) & 0x00FF0000) |
			((unsigned int)(color * f) & 0x0000FF00) |
			((unsigned int)(color * f) & 0x000000FF)
			);
}
#endif

void	render_colors(t_img *img, t_rect b)
{
	const int	ex = b.x + b.w;
	const int	ey = b.y + b.h;
	int	x;
	int	y;
	int	n = b.y * WIN_RESX + b.x; //DEBUG

	y = b.y - 1;
	while (++y < ey)
	{
		x = b.x - 1;
		while (++x < ex)
		{
#if 0
			buf_pixel (img, n, eval_color (
				((unsigned int *)(img->addr))[n]
				//get_sample (img, x, y)
			));
			++n;
#else
			n = get_sample (img, x, y);
#  if DEBUG
			if ((n & 0xFF000000) == 0xFF000000)
				set_pixel (img, x, y, 0x00FF0000);
			else if ((n & 0xFF000000) == 0x02000000)
				set_pixel (img, x, y,
					eval_color (n) >> 1
				);
			else
#  endif
			set_pixel (img, x, y,
				eval_color (
				//get_sample (img, x, y)
				n
				)
			);
#endif
		}
		n += WIN_RESX - b.w;
	}
	//clear_alpha (img, WIN_RESX * WIN_RESY);
}

