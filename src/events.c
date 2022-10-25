/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:29:01 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/25 23:17:46 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_mousemove(int x, int y, void *vars)
{
	t_vars	*v;

	v = (t_vars *)(vars);
	if (v->lock_cursor)
		return (0);
	v->view.cx_input = (t_cx){
		.x = (double)(x),
		.y = (double)(y)};
	v->dirty = 1;
	return (0);
}

int	on_mousedown(int key, int x, int y, void *vars)
{
	t_vars	*v;

	x = 0;
	y = 0;
	v = (t_vars *)(vars);
	v->view.zoom *= 1 + ((key == MOUSE_SCROLL_UP) - (key == MOUSE_SCROLL_DOWN)) * ZOOM_STEP;
	if (v->view.zoom > 2.0L || v->view.zoom <= 0.0L)
		v->view.zoom = 2.0L;
	if (key == MOUSE_BUTTON_LEFT)
	{
		v->lock_cursor = 1;
		/*
		v->view.x += (double)(v->view.cx_input.x - x);
		v->view.y += (double)(v->view.cx_input.y - y);
		*/
	}
	v->lock_cursor &= (key != MOUSE_BUTTON_RIGHT);
	v->dirty = 1;
	return (0);
}

int	on_keydown(int key, void *vars)
{
	t_vars	*v;

	if (key == KB_ESC)
		return (0);
	v = (t_vars *)(vars);
	v->view.x += ((key == ARROW_RIGHT) - (key == ARROW_LEFT)) * PAN_STEP * v->view.zoom;
	v->view.y -= ((key == ARROW_UP) - (key == ARROW_DOWN)) * PAN_STEP * v->view.zoom;
	v->view.zoom *= 1 + ((key == KB_O) - (key == KB_I)) * ZOOM_STEP;
	if (v->view.zoom > 2.0L || v->view.zoom <= 0.0L)
		v->view.zoom = 2.0L;
	v->dirty = 1;
	return (0);
}

int	on_keyup(int key, void *vars)
{
	t_vars	*v;

	v = (t_vars *)(vars);
	if (key == KB_ESC)
		app_close (v, XC_EXIT);
	return (0);
}

int	on_render(void *vars)
{
	//const int		hw = WIN_RESX >> 1;
	//const int		hh = WIN_RESY >> 1;
	t_vars			*v;

	v = (t_vars *)(vars);
	if (!v->dirty)
		return (0);
	v->dirty = 0;
	/*draw_fractal (v, -1, 0, (t_rect){0,  0,  hw, hh}, 0);
	draw_fractal (v, -1, 0, (t_rect){0,  hh, hw, hh}, 0);
	draw_fractal (v, -1, 0, (t_rect){hw, hh, hw, hh}, 0);
	draw_fractal (v, -1, 0, (t_rect){hw, 0,  hw, hh}, 0);*/
	draw_fractal (v, -1, 8, (t_rect){0, 0, WIN_RESX, WIN_RESY}, 0);
	//draw_fractal (&v->img, v->view);
	mlx_put_image_to_window (v->mlxo, v->mlx_win, v->img.o, 0, 0);
	return (0);
}
