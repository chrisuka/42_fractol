/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:41:16 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/12 21:58:27 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	app_close(t_vars *v, int code)
{
	if (v->mlxo)
		mlx_destroy_window(v->mlxo, v->mlx_win);
	v->mlxo = NULL;
	v->mlx_win = NULL;
	exit(code);
}

int	key_axis(int key, const int pval, const int nval)
{
	if (key == pval)
		return (1);
	if (key == nval)
		return (-1);
	return (0);
}

#if 0
double	*choose_fractal(int index);
{
	const double	(*zf)(t_cx, t_cx)[] = {
		&z_mandelbrot,
		&z_tricorn,
		&z_burning_ship
	};

	return (&zf[index % sizeof(zf) / sizeof(zf[0])]);
}
#endif
