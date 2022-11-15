/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:29:01 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/16 00:05:46 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline t_cx	mouse_scale(int x, int y, t_vrect view)
{
	const double	w = ft_min(WIN_RESX, WIN_RESY) * 0.5L;
	const double	amp = 0.01L;

	return ((t_cx){
		.x = (double)(x - w) * amp * view.zoom + view.x,
		.y = (double)(y - w) * amp * view.zoom + view.y});
}

int	on_mousemove(int x, int y, void *vars)
{
	t_vars	*v;

	v = (t_vars *)(vars);
	if (v->lock_cursor)
		return (0);
	v->view.mouse_complex = mouse_scale (x, y, v->view);
	v->dirty = 1;
	return (0);
}

int	on_mousedown(int key, int x, int y, void *vars)
{
	t_vars	*v;

	v = (t_vars *)(vars);
	v->view.zoom *= 1 + key_axis (key, M_SCROLL_U, M_SCROLL_D) * ZOOM_STEP;
	if (v->view.zoom > 2.0L || v->view.zoom <= 0.0L)
		v->view.zoom = 2.0L;
	v->lock_cursor |= (key == M_BUTTON_L);
	v->lock_cursor &= (key != M_BUTTON_R);
	
	v->view.x = mouse_scale (x, y, v->view).x;
	v->view.y = mouse_scale (x, y, v->view).y;

	v->dirty = 1;
	return (0);
}

int	on_keydown(int key, void *vars)
{
	t_vars	*v;

	v = (t_vars *)(vars);
	v->view.x += key_axis (key, ARROW_RIGHT, ARROW_LEFT) * PAN_STEP * v->view.zoom;
	v->view.y -= key_axis (key, ARROW_UP, ARROW_DOWN) * PAN_STEP * v->view.zoom;
	v->view.zoom *= 1 - key_axis (key, KB_I, KB_O) * ZOOM_STEP;
	if (v->view.zoom > 2.0L || v->view.zoom <= 0.0L)
		v->view.zoom = 2.0L;
	if (key == KB_R)
		v->view = (t_vrect){.x = 0.0L, .y = 0.0L,
			.zoom = 1.0L, .mouse_complex = (t_cx){0.0L, 0.0L}};
	v->dirty = 1;
	if (key == KB_ESC)
	{
		v->dirty = 0;
		return (0);
	}
	return (0);
}

int	on_keyup(int key, void *vars)
{
	t_vars	*v;

	v = (t_vars *)(vars);
	if (key == KB_SPC)
	{
		v->fractal_type = (v->fractal_type + 1) % 4;
		v->dirty = 1;
	}
	if (key == KB_ESC)
		app_close (v, XC_EXIT);
	return (0);
}

int	on_render(void *vars)
{
	//const t_rect	screen = (t_rect){0, 0, WIN_RESX, WIN_RESY};
	const t_rect	screen = (t_rect){0, GUI_CELL_H, WIN_RESX, WIN_RESY - GUI_CELL_H};
	t_vars			*v;

	v = (t_vars *)(vars);
	if (!v->dirty)
		return (0);
	v->dirty = 0;
	if (v->view.zoom >= 0.5L)
		draw_fractal_simple (v, screen);
	else
		draw_fractal (v, 0, screen);
	render_colors (&v->img, screen);

	mlx_put_image_to_window (v->mlxo, v->mlx_win, v->img.o, 0, 0);

	put_gui_static (v, (t_rect){0, 0, WIN_RESX, GUI_CELL_H});
	return (0);
}
