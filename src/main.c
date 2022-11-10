/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:55:03 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/09 23:14:36 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int	print_usage(void)
{
	const char	msg[] = "usage:  " BIN_NAME " mandelbrot|julia|burningship\n";

	write (1, msg, sizeof(msg) - 1);
	return (XC_ERROR);
}

static inline void	add_hooks(t_vars *v)
{
	mlx_hook (v->mlx_win, ON_MOUSEMOVE, 0, &on_mousemove, v);
	mlx_hook (v->mlx_win, ON_MOUSEDOWN, 0, &on_mousedown, v);
	mlx_hook (v->mlx_win, ON_KEYDOWN, 0, &on_keydown, v);
	mlx_hook (v->mlx_win, ON_KEYUP, 0, &on_keyup, v);
	mlx_loop_hook (v->mlxo, &on_render, v);
}

static inline t_vars	instantiate_mlx(char *wname)
{
	t_vars	v;

	v = (t_vars){
		.mlxo = mlx_init(),
		.img = (t_img){.o = NULL, .addr = NULL},
		.view = (t_vrect){.x = 0.0L, .y = 0.0L, .zoom = 1.0L,
		.mouse_complex = (t_cx){0.0L, 0.0L}},
		.lock_cursor = 0,
		.dirty = 1
	};
	v.mlx_win = mlx_new_window(v.mlxo, WIN_RESX, WIN_RESY, wname);
	v.img.o = mlx_new_image(v.mlxo, WIN_RESX, WIN_RESY);
	v.img.addr = mlx_get_data_addr(v.img.o,
			&v.img.bpp, &v.img.width, &v.img.endian);
	v.img.bpp /= __CHAR_BIT__;
	return (v);
}

# define DEBUG 0
#if DEBUG
#include <stdio.h>
int	test(void)
{
	return (0);
}
#endif
int	main(int argc, char **argv)
{
	t_vars	v;

#if DEBUG
	test ();
#endif
	argv = NULL;
	if (argc != 2)
		return (print_usage());
	v = instantiate_mlx(WIN_TITLE);
	add_hooks (&v);
	mlx_loop (v.mlxo);
	return (XC_EXIT);
}
