/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 16:40:59 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 16:46:17 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

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
}

static void	keyboard_paint(int keycode, t_gl *gl)
{
	if (keycode == KEY_NUM)
	{
		gl->paint_prev = gl->paint;
		gl->paint = chaton;
		gl->ratio = 0;
	}
	else if (keycode == KEY_SLASH)
	{
		gl->paint_prev = gl->paint;
		gl->paint = poney;
		gl->ratio = 0;
	}
	else if (keycode == KEY_CROSS)
	{
		gl->paint_prev = gl->paint;
		gl->paint = licorne;
		gl->ratio = 0;
	}
	else if (keycode == KEY_MINUS)
	{
		gl->paint_prev = gl->paint;
		gl->paint = color;
		gl->ratio = 0;
	}
}

/*
** ┌───────────────────────┐
** │ Keyboard Function     │
** └───────────────────────┘
*/

int			keyboard_funct(int keycode, t_gl *gl)
{
	if (keycode == 53)
		exit(0);
	keyboard_translation(keycode, gl);
	keyboard_rotation(keycode, gl);
	keyboard_paint(keycode, gl);
	return (0);
}

int			refresh_funct(t_gl *gl)
{
	clock_t			cur_time;
	static clock_t	before_time = 0.0;

	gl->center.rad_angle += M_PI_4 / 100;
	display(gl);
	mlx_opengl_swap_buffers(gl->win);
	if (gl->ratio < 1.0)
		gl->ratio += 0.01;
	cur_time = clock();
	if (cur_time - before_time > CLOCKS_PER_SEC)
	{
		dprintf(1, "FPS : %.0f\n", (gl->center.rad_angle -
			gl->center.old_angle) / M_PI_4 * 100);
		before_time = cur_time;
		gl->center.old_angle = gl->center.rad_angle;
	}
	return (0);
}
