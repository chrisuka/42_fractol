/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:41:16 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/17 17:12:14 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keysym_macos.h"

void	app_close(t_vars *v, int code)
{
	if (v->mlxo)
		mlx_destroy_window(v->mlxo, v->mlx_win);
	v->mlxo = NULL;
	v->mlx_win = NULL;
	exit(code);
}

int	on_keydown(int key, void *vars)
{
	t_vars	*v;

	key = 0;
	v = (t_vars *)(vars);
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
	const uint64_t	bgcolor = (BG_COLOR | BG_COLOR << 32);
	t_vars			*v;

	v = (t_vars *)(vars);
	ft_bset64 (v->img.addr, bgcolor, (WIN_RESX * WIN_RESY) * v->img.bpp);
	mlx_put_image_to_window (v->mlxo, v->mlx_win, v->img.o, 0, 0);
	v->frame ++;
	return (0);
}
