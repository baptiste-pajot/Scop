/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   center.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 11:38:12 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 16:10:08 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

static void		calculate_ratio(t_gl *gl)
{
	int		i;
	GLfloat	diff;

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
	while (++i < gl->nb_vertices * 5)
	{
		j = i % 3;
		if (j < 3)
		{
			if (gl->vertices[i] < gl->center.min[j])
				gl->center.min[j] = gl->vertices[i];
			if (gl->vertices[i] > gl->center.max[j])
				gl->center.max[j] = gl->vertices[i];
		}
	}
	i = -1;
	while (++i < 3)
	{
		gl->center.mean[i] = (gl->center.min[i] + gl->center.max[i]) / 2.0;
		printf("mean ind %d = %f\n", i, gl->center.mean[i]);
	}
	calculate_ratio(gl);
}
