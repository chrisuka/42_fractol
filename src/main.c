/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:55:03 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/17 22:27:41 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keysym_macos.h"

static inline int		print_usage(void)
{
	const char	msg[] = "usage:  " BIN_NAME " mandelbrot|julia|sierpinski\n";

	write (1, msg, sizeof(msg) - 1);
	return (XC_ERROR);
}

static inline t_vars	initialize_vars(void)
{
	t_vars	v;

	v.mlxo = NULL;
	v.mlx_win = NULL;
	v.img = (t_img){0};
	v.frame = 0;
	return (v);
}

static inline t_vars	instantiate_mlx(char *wname)
{
	t_vars	v;

	v = initialize_vars();
	v.mlxo = mlx_init();
	v.mlx_win = mlx_new_window(v.mlxo, WIN_RESX, WIN_RESY, wname);
	v.img.o = mlx_new_image(v.mlxo, WIN_RESX, WIN_RESY);
	v.img.addr = mlx_get_data_addr(v.img.o,
			&v.img.bpp, &v.img.width, &v.img.endian);
	v.img.bpp /= __CHAR_BIT__;
	return (v);
}

static inline void		add_hooks(t_vars *v)
{
	mlx_hook (v->mlx_win, ON_MOUSEMOVE, 0, &on_mousemove, v);
	mlx_hook (v->mlx_win, ON_KEYUP, 0, &on_keyup, v);
	mlx_loop_hook (v->mlxo, &on_render, v);
}

int	main(int argc, char **argv)
{
	t_vars	v;

	argv = NULL;
	if (argc != 2)
		return (print_usage());
	v = instantiate_mlx(WIN_TITLE);
	add_hooks (&v);
	mlx_loop (v.mlxo);
	return (XC_EXIT);
}
