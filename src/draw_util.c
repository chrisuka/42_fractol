/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:59:31 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/09 21:50:39 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline int	inside_frame(int x, int y)
{
	return (x >= 0 && x < WIN_RESX
		&& y >= 0 && y < WIN_RESY);
}

void	set_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	if (!inside_frame(x, y))
		return ;
	px = img->addr + (y * img->width + x * img->bpp);
	*(unsigned int *)(px) = color;
}

/* Draw a colored line specified by ln using the DDA
 * (Digital Differential Analyzer) algorithm:
 * determine the number of steps as the larger of delta x and delta y
 *
 * dx / steps and dy / steps will be the axis' respective increment values
 * each step, increment xy and round to int to find the next pixel
*/
void	draw_line(t_img *img, t_line ln)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	int		steps;

	if (!inside_frame(ln.x0, ln.y0) && !inside_frame(ln.x1, ln.y1))
		return ;
	dx = (double)(ln.x1 - ln.x0);
	dy = (double)(ln.y1 - ln.y0);
	steps = (int)(fmax(fabs(dx), fabs(dy)));
	dx /= steps;
	dy /= steps;
	x = (double)(ln.x0);
	y = (double)(ln.y0);
	while (steps-- >= 0)
	{
		set_pixel (img, (int)(x), (int)(y), MAP_COLOR);
		x += dx;
		y += dy;
	}
}

/* Draw a colored rect from origin x0,y0 with size x1,y1
 * offset by the direction specified by the anchor index:
 * 0:center, 1:topleft, 2:topright, 3:bottomright, 4:bottomleft
*/
void	draw_rect(t_img *img, t_rect r, int anchor, unsigned int color)
{
	const int	offsets[][2] = {{-1, -1}, {0, 0}, {-2, 0}, {-2, -2}, {0, -2}};
	int			xn;
	int			yn;

	r.x0 += offsets[anchor][0] * (r.x1 / 2);
	r.y0 += offsets[anchor][1] * (r.y1 / 2);
	if (!inside_frame(r.x0, r.y0))
		return ;
	xn = 0;
	while (xn <= r.x1)
	{
		yn = 0;
		while (yn <= r.y1)
			set_pixel (img, r.x0 + xn, r.y0 + yn++, color);
		xn ++;
	}
}
