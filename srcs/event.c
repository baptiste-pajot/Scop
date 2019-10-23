/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 16:40:59 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 18:14:16 by bpajot      ###    #+. /#+    ###.fr     */
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

static void	keyboard_translation(int keycode, t_gl *gl)
{
	if (keycode == KEY_RIGHT)
		gl->center.cam_offset_x += KEY_OFFSET_TR * gl->center.max_size;
	else if (keycode == KEY_LEFT)
		gl->center.cam_offset_x -= KEY_OFFSET_TR * gl->center.max_size;
	else if (keycode == KEY_UP)
		gl->center.cam_offset_y += KEY_OFFSET_TR * gl->center.max_size;
	else if (keycode == KEY_DOWN)
		gl->center.cam_offset_y -= KEY_OFFSET_TR * gl->center.max_size;
	else if (keycode == KEY_PAGE_UP)
		gl->center.cam_offset_z += KEY_OFFSET_TR * gl->center.max_size;
	else if (keycode == KEY_PAGE_DOWN)
		gl->center.cam_offset_z -= KEY_OFFSET_TR * gl->center.max_size;
}

static void	keyboard_rotation(int keycode, t_gl *gl)
{
	if (keycode == KEY_8)
		gl->center.cam_rot_x += KEY_OFFSET_ROT;
	else if (keycode == KEY_2)
		gl->center.cam_rot_x -= KEY_OFFSET_ROT;
	else if (keycode == KEY_4)
		gl->center.cam_rot_y += KEY_OFFSET_ROT;
	else if (keycode == KEY_6)
		gl->center.cam_rot_y -= KEY_OFFSET_ROT;
	else if (keycode == KEY_7)
		gl->center.cam_rot_z += KEY_OFFSET_ROT;
	else if (keycode == KEY_9)
		gl->center.cam_rot_z -= KEY_OFFSET_ROT;
}

/*
** ┌───────────────────────┐
** │ Keyboard Function     │
** └───────────────────────┘
** Close Graphic Window when you press Esc or Q letter
*/

int			keyboard_funct(int keycode, t_gl *gl)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		red_cross_funct(NULL);
	keyboard_translation(keycode, gl);
	keyboard_rotation(keycode, gl);
	//dprintf(1, "keycode = %d\n", keycode);
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
		before_time = cur_time;
		old_angle = angle;
	}
	return (0);
}
