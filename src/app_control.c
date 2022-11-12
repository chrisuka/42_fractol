/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:41:16 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/12 02:00:20 by ikarjala         ###   ########.fr       */
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
