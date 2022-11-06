/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:19:08 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/06 21:21:17 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

# define DEBUG 1

static inline unsigned int	sample_color(int n)
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

void	render_colors(t_img *img, t_rect b)
{
	const int	ex = b.x + b.w;
	const int	ey = b.y + b.h;
	int	x;
	int	y;

	int	n = 0; //DEBUG

	x = b.x - 1;
	while (++x < ex)
	{
		y = b.y - 1;
		while (++y < ey)
		{
#if 0
			buf_pixel (img, ++n, sample_color(
				get_sample (img, x, y)));
			n += WIN_RESX;
#else
#  if DEBUG
			n = get_sample (img, x, y);
			if ((n & 0xFF000000) == 0xFF000000)
				set_pixel (img, x, y, 0x00FF0000);
			else if ((n & 0xFF000000) == 0x02000000)
				set_pixel (img, x, y,
					sample_color (n) * 0.8L);
			else
#  endif
			set_pixel (img, x, y,
				sample_color(
				//get_sample (img, x, y)
				n
				)
			);
#endif
		}
	}
	//clear_alpha (img, WIN_RESX * WIN_RESY);
}

