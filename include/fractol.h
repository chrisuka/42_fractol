/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:37:15 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/12 02:05:07 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "graphics_util.h"
# include "keysym_macos.h"

# define DEBUG 1//DEBUG

# define BIN_NAME	"fractol"
# define WIN_TITLE	"Fract'ol"
# define WIN_RESX	640
# define WIN_RESY	640

# define PAN_STEP	0.25L
# define ZOOM_STEP	0.25L

# define MAX_DEPTH		40 // MAX ITERATIONS PER COMPLEX FUNCTION
# define PERIOD			20 // INTERVAL TO CHECK PERIODICITY
# define SUBDIV_DEPTH	16 // MAX DEPTH TO RECURSE SUBDIVSIONS
# define SUBD_RES		4 // IF SUBDIVISION RESOLUTION LESS THAN THIS, GOTO SIMPLE

# define XC_EXIT	0
# define XC_ERROR	1

# define ECONTINUE	0
# define EEXIT		1
# define EINTERNAL	2

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

	int		lock_cursor : 1;
	int		dirty : 1;
	//int		debug : 1;
}	t_vars;

/*/ App Control ////////*/

void	app_close(t_vars *v, int code);
int		key_axis(int key, const int pval, const int nval);

/*/ Events /////////////*/

int		on_keydown(int key, void *vars);
int		on_keyup(int key, void *vars);
int		on_mousedown(int key, int x, int y, void *vars);
int		on_mousemove(int x, int y, void *vars);
int		on_render(void *vars);

/*/ Draw Utilities /////*/

void	set_pixel(t_img *img, int x, int y, unsigned int color);
void	buf_pixel(t_img *img, int n, unsigned int color);
void	draw_rect(t_img *img, t_rect b, unsigned int color);

/*/ Draw Manager ///////*/

void	draw_fractal_simple(t_vars *v, t_rect b);
void	draw_fractal(t_vars *v, int depth, t_rect b);

/*/ Sampler ////////////*/

void	sample_border(t_vars *v, t_rect b);
int		sample_fractal(t_vars *v, int x, int y);
int		sample_fractal_2(t_vars *v, int x, int y);
int		get_sample(t_img *img, int x, int y);

/*/ Render /////////////*/

void	render_colors(t_img *img, t_rect b);

/*/ Fractals ///////////*/

int	mandelbrot(t_cx z, t_cx c);

#endif
