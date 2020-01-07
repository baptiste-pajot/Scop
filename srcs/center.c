/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   center.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 11:38:12 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 14:18:07 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌─────────────────┐
** │ Calculate Ratio │
** └─────────────────┘
** Get the max delta size from the 3 axes x, y, z
** Offset the z camera according to that result in order
** to have all the object visible in the window during the
** automatic rotation
*/

static void		calculate_ratio(t_gl *gl)
{
	int		i;
	GLfloat	diff;

	gl->center.max_size = 0.0;
	i = -1;
	while (++i < 3)
	{
		diff = gl->center.max[i] - gl->center.min[i];
		if (gl->center.max_size < diff)
			gl->center.max_size = diff;
	}
	printf("max_size = %f\n", gl->center.max_size);
	gl->center.cam_offset_x = 0.0;
	gl->center.cam_offset_y = 0.0;
	gl->center.cam_offset_z = -1.8 * (gl->center.max_size / 2.0)
		/ tan(FOV * M_PI / 360);
	gl->center.cam_rot_x = 0.0;
	gl->center.cam_rot_y = 0.0;
	gl->center.cam_rot_z = 0.0;
	printf("cam_offset = %f\n\n", gl->center.cam_offset_z);
}

/*
** ┌─────────────────┐
** │ Calculate Center│
** └─────────────────┘
** Get the min/max of the object from the 3 axes x, y, z
** Calculate the center of the object for rotation
*/

void			calculate_center(t_gl *gl)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		gl->center.min[i] = gl->vertices[i];
		gl->center.max[i] = gl->center.min[i];
	}
	i = 2;
	while (++i < gl->nb_vertices * 3)
	{
		j = i % 3;
		if (gl->vertices[i] < gl->center.min[j])
			gl->center.min[j] = gl->vertices[i];
		if (gl->vertices[i] > gl->center.max[j])
			gl->center.max[j] = gl->vertices[i];
	}
	i = -1;
	while (++i < 3)
	{
		gl->center.mean[i] = (gl->center.min[i] + gl->center.max[i]) / 2.0;
		printf("mean ind %d = %f\n", i, gl->center.mean[i]);
	}
	calculate_ratio(gl);
}
