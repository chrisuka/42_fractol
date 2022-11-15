/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_util.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarjala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:27:26 by ikarjala          #+#    #+#             */
/*   Updated: 2022/11/16 00:35:56 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_UTIL_H
# define GRAPHICS_UTIL_H

# ifndef CLI_COLORS
#  define CLI_COLORS
#  define CNIL		"\033[0;0m"
#  define CRED		"\033[0;31m"
#  define CGREEN	"\033[0;32m"
#  define CGOLD		"\033[0;33m"

#  define CBRED		"\033[1;31m"
#  define CBGREEN	"\033[1;32m"
#  define CBGOLD	"\033[1;33m"
# endif

enum	e_gui_anchor {
	anchor_cent = 0,
	anchor_topl = 1,
	anchor_topr = 2,
	anchor_botr = 3,
	anchor_botl = 4
};

/* GUI TEXT
*/

# define GUI_CELL_W		10
# define GUI_CELL_H		25

#endif
