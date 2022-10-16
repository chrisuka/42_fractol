/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:55:03 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/16 20:56:35 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keysym_macos.h"

static inline int	print_usage(void)
{
	const char	msg[] = "usage:  " BIN_NAME " mandelbrot|julia|custom\n";

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

static inline t_vars	instantiate_mlx(const char *wname)
{
	t_vars	v;

	v = initialize_vars();
	v.mlxo = mlx_init();
	v.img.o = mlx_new_image(v.mlxo, WIN_RESX, WIN_RESY, wname);
	v.img.addr = mlx_get_data_addr(v.img.o,
			&v.img.bpp, &v.img.width, &v.img.endian);
	v.img.bpp /= __CHAR_BIT__;
	mlx_hook(v.mlx_win, ON_KEYDOWN, XKMASK_KB, &on_keydown, &v);
	mlx_key_hook (v.mlx_win, &on_keyup, &v);
	mlx_loop_hook (v.mlxo, &on_render, &v);
	return (v);
}

int	main(int argc, char **argv)
{
	t_vars	v;

	if (argc != 2)
		return (print_usage());
	v = instantiate_mlx("Fract'ol");
	mlx_loop (v.mlxo);
	return (XC_EXIT);
}
