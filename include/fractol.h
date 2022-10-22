/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:37:15 by ikarjala          #+#    #+#             */
/*   Updated: 2022/10/22 17:15:35 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "graphics_util.h"

# define BIN_NAME	"fractol"
# define WIN_TITLE	"Fract'ol"
# define WIN_RESX	1080
# define WIN_RESY	640

# define MAX_DEPTH	200

# define XC_EXIT	0
# define XC_ERROR	1

# define ECONTINUE	0
# define EEXIT		1
# define EINTERNAL	3

typedef struct s_complex
{
	double	x;
	double	y;
}	t_cx;

typedef struct s_viewport {
	double	x;
	double	y;
	double	zoom;
}	t_vrect;

typedef struct s_img_data {
	void	*o;
	char	*addr;
	int		bpp;
	int		width;
	int		endian;
}	t_img;

typedef struct s_vars_data_container {
	void	*mlxo;
	void	*mlx_win;
	t_img	img;
	t_vrect	view;
}	t_vars;

/*/ App Control ////////*/

void	app_close(t_vars *v, int code);
int		on_keydown(int key, void *vars);
int		on_keyup(int keycode, void *vars);
int		on_mousemove(int x, int y, t_vars *v);
int		on_render(void *vars);

/*/ Draw Utilities /////*/

void	set_pixel(t_img *img, int x, int y, unsigned int color);

/*/ Draw Manager ///////*/

void	draw_fractal(t_img *img, t_vrect view);

/*/ GUI ////////////////*/

/*/ Error //////////////*/

int		perr_badmap(char *fname);
int		perr_internal(void);

#endif
