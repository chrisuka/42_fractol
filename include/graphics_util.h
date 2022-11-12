/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_util.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:27:26 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/12 21:09:31 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_UTIL_H
# define GRAPHICS_UTIL_H

# ifndef CLI_COLORS
#  define CLI_COLORS
#  define CYELLOW	"\033[0;33m"
#  define CGREEN	"\033[0;32m"
#  define CRED		"\033[0;31m"
#  define CYELLOWB	"\033[1;33m"
#  define CGREENB	"\033[1;32m"
#  define CREDB		"\033[1;31m"
#  define CNIL		"\033[0;0m"
# endif

# define GUI_ANCHOR_CENTER	0
# define GUI_ANCHOR_TOP_L	1
# define GUI_ANCHOR_TOP_R	2
# define GUI_ANCHOR_BOT_R	3
# define GUI_ANCHOR_BOT_L	4

# define GUI_CELL_W		10
# define GUI_CELL_H		25

#endif
