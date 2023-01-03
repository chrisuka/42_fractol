/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keysym_macos.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:28:03 by ikarjala          #+#    #+#             */
/*   Updated: 2023/01/03 13:32:29 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYSYM_MACOS_H
# define KEYSYM_MACOS_H

# define M_BUTTON_L		1
# define M_BUTTON_R		2
# define M_BUTTON_M		3
# define M_SCROLL_U		4
# define M_SCROLL_D		5
# define M_SCROLL_L		6
# define M_SCROLL_R		7

# define ARROW_LEFT		123
# define ARROW_RIGHT	124
# define ARROW_DOWN		125
# define ARROW_UP		126

# define KB_D		2
# define KB_R		15
# define KB_O		31
# define KB_U		32
# define KB_I		34

# define KB_SPC		49
# define KB_ESC		53

# define KB_NUM_PLUS	69
# define KB_NUM_MINUS	78
# define KB_NUM			82
# define KB_NUM_1		83
# define KB_NUM_2		84
# define KB_NUM_3		85
# define KB_NUM_4		86
# define KB_NUM_5		87
# define KB_NUM_6		88
# define KB_NUM_7		89
# define KB_NUM_8		91
# define KB_NUM_9		92

/*/ EVENTS  /////////*/

# define XKMASK_KB	1L

enum {
	ON_KEYDOWN		= 2,
	ON_KEYUP		= 3,
	ON_MOUSEDOWN	= 4,
	ON_MOUSEUP		= 5,
	ON_MOUSEMOVE	= 6,
	ON_EXPOSE		= 12,
	ON_DESTROY		= 17
};

#endif
