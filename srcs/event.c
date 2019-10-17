/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 16:40:59 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 17:17:30 by bpajot      ###    #+. /#+    ###.fr     */
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
	static float	old_angle = 0.0;
	clock_t			cur_time;
	static clock_t	before_time = 0.0;

	angle += M_PI_4 / 100;
	display(gl, angle);
	mlx_opengl_swap_buffers(gl->win);
	cur_time = clock();
	if (cur_time - before_time > CLOCKS_PER_SEC)
	{
		dprintf(1, "FPS : %.0f\n", (angle - old_angle) / M_PI_4 * 100);
		dprintf(1, "time1 : %lu\ntime2 : %lu\n", before_time, cur_time);
		dprintf(1, "CLOCKS_PER_SECOND : %d\n", CLOCKS_PER_SEC);
		before_time = cur_time;
		old_angle = angle;
	}
	return (0);
}
