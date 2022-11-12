/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 19:47:58 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/12 21:08:53 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline char	*get_str(void)
{
	#define DELIM " | "
	//const char	del[] = "//";

	return ("[ESC]:quit" DELIM
			"[R]eset" DELIM
			"[<^v>]:move" DELIM
			"zoom [I]n/[O]ut"
			);
}

void	put_gui_static(t_vars *v, t_rect b)
{
	const unsigned int	bgcolor = 0x00242424;
	const unsigned int	fgcolor = 0x00FFFFFF;
	const unsigned int	pad = 0;

	draw_rect (&v->img, b, bgcolor);
	mlx_string_put (v->mlxo, v->mlx_win, b.x + pad, b.y + pad, fgcolor, get_str());
}
