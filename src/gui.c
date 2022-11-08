/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:47:58 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/07 22:51:50 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline char	*get_str(void)
{
	return ("[R]eset  "
			"[<^v>]:move  "
			"zoom [I]n/[O]ut | MOUSE SCROLL [^v]  "
			"MOUSE BUTTON [1/2]:freeze/unfreeze julia set"
			);
}

void	put_gui_static(t_vars *v, t_rect b)
{
	const unsigned int	bgcolor = 0x00242424;
	const unsigned int	fgcolor = 0x00AAFFAA;
	const int			pad = 1;

	draw_rect (&v->img, b, bgcolor);
	mlx_string_put (v->mlxo, &v->img, b.x + pad, b.y + pad, fgcolor, get_str());
}
