/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 16:40:59 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 16:41:01 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌───────────────────────┐
** │ Red Cross Function    │
** └───────────────────────┘
** Close Graphic Window when you click on the Red Cross on the top-left corner
*/

int			red_cross_funct(void *pt)
{
	pt = NULL;
	exit(0);
}

/*
** ┌───────────────────────┐
** │ Keyboard Function     │
** └───────────────────────┘
** Close Graphic Window when you press Esc or Q letter
*/

int			keyboard_funct(int keycode, void *pt)
{
	if (keycode == 53 || keycode == 12)
		red_cross_funct(pt);
	return (0);
}

int			refresh_funct(t_gl *gl)
{
	static float	angle = 0.0;
	angle += M_PI_4 / 200;
	display(gl, angle);
	mlx_opengl_swap_buffers(gl->win);
	return (0);
}