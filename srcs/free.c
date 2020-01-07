/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/06 14:31:54 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 14:09:43 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

void		init_struct(t_gl *gl)
{
	int		i;

	gl->paint = color;
	gl->paint_prev = gl->paint;
	gl->ratio = 1.0;
	gl->center.rad_angle = 0.0;
	gl->center.old_angle = 0.0;
	gl->mat_proj = mat_projection();
	gl->indices = NULL;
	gl->vertices = NULL;
	gl->txt_file = NULL;
	gl->line_file = NULL;
	i = -1;
	while (++i < 3)
		gl->texture[i].bmp = NULL;
}

void		free_gl_struct(t_gl *gl)
{
	int		i;

	if (gl->indices)
		free(gl->indices);
	if (gl->vertices)
		free(gl->vertices);
	if (gl->txt_file)
		free(gl->txt_file);
	if (gl->line_file)
		free(gl->line_file);
	if (gl->mat_proj)
		free(gl->mat_proj);
	i = -1;
	while (++i < 3)
	{
		if (gl->texture[i].bmp)
			free(gl->texture[i].bmp);
	}
}
