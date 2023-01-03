/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:47:58 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/03 18:07:58 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_gui_bg(t_vars *v, t_rect b)
{
	const unsigned int	color = 0x00242424;

	draw_rect (&v->img, b, color);
}

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

void	put_gui_static_text(t_vars *v, t_rect b)
{
	const unsigned int	color = 0x00FFFFFF;
	const unsigned int	pad = 0;

	mlx_string_put (v->mlxo, v->mlx_win,
		b.x + pad, b.y + pad, color, get_str());
}
