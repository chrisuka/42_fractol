/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:55:03 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/03 17:38:18 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline int	print_usage(void)
{
	const char	msg[] = "usage:  " BIN_NAME " <"
		CBGOLD "julia | mandelbrot | tricorn | ship" CNIL ">\n";

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
		.max_samples = 40,
		.lock_cursor = 0,
		.fractal_type = -1,
		.debug = 0,
		.dirty = 1
	};
	v.mlx_win = mlx_new_window(v.mlxo, WIN_RESX, WIN_RESY, wname);
	v.img.o = mlx_new_image(v.mlxo, WIN_RESX, WIN_RESY);
	v.img.addr = mlx_get_data_addr(v.img.o,
			&v.img.bpp, &v.img.width, &v.img.endian);
	v.img.bpp /= __CHAR_BIT__;
	return (v);
}

static int	parse_arg(char *arg)
{
	const char	*ops[] = {"julia", "mandelbrot", "tricorn", "ship"};
	int			n;

	n = -1;
	while (++n < (int)(sizeof(ops) / sizeof(ops[0])))
	{
		if (ft_strequ (ops[n], arg))
			return (n);
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	t_vars	v;
	int		fractal_type;

	if (argc != 2)
		return (print_usage());
	fractal_type = parse_arg(argv[1]);
	if (fractal_type == -1)
		return (print_usage());
	v = instantiate_mlx(WIN_TITLE);
	v.fractal_type = fractal_type;
	add_hooks (&v);
	mlx_loop (v.mlxo);
	return (XC_EXIT);
}
