/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrice_pipeline.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/06 16:08:31 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/06 16:48:52 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

GLfloat		*mat_view(t_gl *gl)
{
	GLfloat	*mat_view1;
	GLfloat	*mat_view2;
	GLfloat	*mat_view3;
	GLfloat	*mat_view4;
	GLfloat	*mat_view5;

	mat_view1 = mat_rot('Y', gl->center.rad_angle + gl->center.cam_rot_y);
	mat_view2 = mat_rot('X', gl->center.cam_rot_x);
	mat_view3 = mat_transpose(mat_translate(gl->center.cam_offset_x,
		gl->center.cam_offset_y, gl->center.cam_offset_z));
	mat_view4 = mat_mult(mat_view2, mat_view3);
	mat_view5 = mat_mult(mat_view1, mat_view4);
	if (mat_view1)
		free(mat_view1);
	if (mat_view2)
		free(mat_view2);
	if (mat_view3)
		free(mat_view3);
	if (mat_view4)
		free(mat_view4);
	return (mat_view5);
}

GLfloat		*mat_model(t_gl *gl)
{
	GLfloat	*mat_model1;
	GLfloat	*mat_model2;
	GLfloat	*mat_model3;

	mat_model1 = mat_transpose(mat_translate(-gl->center.mean[0],
		-gl->center.mean[1], -gl->center.mean[2]));
	mat_model2 = mat_rot('Y', gl->center.rad_angle);
	mat_model3 = mat_mult(mat_model1, mat_model2);
	if (mat_model1)
		free(mat_model1);
	if (mat_model2)
		free(mat_model2);
	return (mat_model3);
}
