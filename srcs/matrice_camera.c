/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrice_camera.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 18:13:00 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 18:32:39 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

GLfloat					*mat_proj(void)
{
	GLfloat	*matrice;
	float	top;
	float	right;
	float	ratio;

	ratio = W_WIDTH / W_HEIGHT;
	top = NEAR * tan(M_PI / 180.0 * FOV / 2);
	right = top * ratio;
	matrice = mat_zero();
	matrice[0] = NEAR / right;
	matrice[5] = NEAR / top;
	matrice[10] = -(FAR + NEAR) / (FAR - NEAR);
	matrice[14] = -1.0;
	return (matrice);
}

/*GLfloat				*mat_camera(void)
{
	GLfloat *mat_proj;
	GLfloat *mat_transpose;
}*/
