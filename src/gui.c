/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:47:58 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/03 17:16:14 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline char	*get_str(void)
{
	return (
		"[ESC]:quit "
		"[R]eset "
		"[D]ebug mode" " | "
		"[<^v>]:move" " | "
		"zoom [I]n/[O]ut" " | "
		"[SPC]:cycle fractal"
	);
}

void	put_gui_static(t_vars *v, t_rect b)
{
	const unsigned int	bgcolor = 0x00242424;
	const unsigned int	fgcolor = 0x00FFFFFF;
	const unsigned int	pad = 0;

	draw_rect (&v->img, b, bgcolor);
	mlx_string_put (v->mlxo, v->mlx_win,
		b.x + pad, b.y + pad, fgcolor, get_str());
}
