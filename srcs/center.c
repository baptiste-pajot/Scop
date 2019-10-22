/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   center.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 11:38:12 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 13:46:07 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

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
}