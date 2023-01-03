/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:37:15 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/03 18:07:12 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "graphics_util.h"
# include "keysym_macos.h"
# include "debug.h"

# define BIN_NAME	"fractol"
# define WIN_TITLE	"Fract'ol"
# define WIN_RESX	1024
# define WIN_RESY	1024

# define PAN_STEP	0.25L
# define ZOOM_STEP	0.25L

# define MAX_DEPTH		200
# define PERIOD			20
# define SUBDIV_DEPTH	16
# define SUBD_RES		4

# define XC_EXIT	0
# define XC_ERROR	1

typedef struct s_tuple {
	int	x;
	int	y;
}	t_tuple;

typedef struct s_complex
{
	double	x;
	double	y;
}	t_cx;

typedef struct s_viewport {
	double	x;
	double	y;
	double	zoom;
	t_cx	mouse_complex;
}	t_vrect;

typedef struct s_rectangle_bounds {
	int	x;
	int	y;
	int	w;
	int	h;
}	t_rect;

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

	int		fractal_type;
	int		max_samples;
	int		lock_cursor : 1;
	int		dirty : 1;
	int		debug : 1;
}	t_vars;

enum	e_fractals {
	julia_mc = 0,
	mandelbrot = 1,
	tricorn = 2,
	burning_ship = 3
};

/*/ App Control //====================================/*/

void	app_close(t_vars *v, int code);
int		key_axis(int key, const int pval, const int nval);
t_cx	mouse_scale(int x, int y, t_vrect view);

/*/ Events //=========================================/*/

int		on_keydown(int key, void *vars);
int		on_keyup(int key, void *vars);
int		on_mousedown(int key, int x, int y, void *vars);
int		on_mousemove(int x, int y, void *vars);
int		on_render(void *vars);

/*/ Draw Utilities //=================================/*/

void	set_pixel(t_img *img, int x, int y, unsigned int color);
void	buf_pixel(t_img *img, int n, unsigned int color);
void	draw_rect(t_img *img, t_rect b, unsigned int color);

/*/ Draw Manager //===================================/*/

void	draw_fractal_simple(t_vars *v, t_rect b);
void	draw_fractal(t_vars *v, int depth, t_rect b);

/*/ Sampler //========================================/*/

void	sample_border(t_vars *v, t_rect b);
int		sample_fractal(t_vars *v, int x, int y);
int		get_sample(t_img *img, int x, int y);

/*/ Render //=========================================/*/

void	render_colors(t_img *img, t_rect b, int debug);

/*/ Fractals //=======================================/*/

int		julia(int zf_index, t_cx z, t_cx c);

/*/ GUI //============================================/*/

void	put_gui_bg(t_vars *v, t_rect b);
void	put_gui_static_text(t_vars *v, t_rect b);

/*/ Debug //==========================================/*/

int		debug_get_sample(t_img *img, int x, int y);
int		debug_sample_fractal(t_vars *v, int x, int y);

#endif
