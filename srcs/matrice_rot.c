/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matrice_rot.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 18:07:46 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 18:07:50 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

static GLfloat		*mat_rot_x(float rad_angle, GLfloat *matrice)
{
	matrice[0] = 1.0;
	matrice[5] = cos(rad_angle);
	matrice[10] = matrice[5];
	matrice[9] = sin(rad_angle);
	matrice[6] = -matrice[9];
	matrice[15] = 1.0;
	return (matrice);
}

static GLfloat		*mat_rot_y(float rad_angle, GLfloat *matrice)
{
	matrice[0] = cos(rad_angle);
	matrice[10] = matrice[0];
	matrice[5] = 1.0;
	matrice[2] = sin(rad_angle);
	matrice[8] = -matrice[2];
	matrice[15] = 1.0;
	return (matrice);
}

static GLfloat		*mat_rot_z(float rad_angle, GLfloat *matrice)
{
	matrice[0] = cos(rad_angle);
	matrice[5] = matrice[0];
	matrice[4] = sin(rad_angle);
	matrice[1] = -matrice[4];
	matrice[10] = 1.0;
	matrice[15] = 1.0;
	return (matrice);
}

GLfloat				*mat_rot(char axe, float rad_angle)
{
	GLfloat	*matrice;

	matrice = mat_zero();
	if (axe == 'X' || axe == 'x')
		matrice = mat_rot_x(rad_angle, matrice);
	if (axe == 'Y' || axe == 'y')
		matrice = mat_rot_y(rad_angle, matrice);
	if (axe == 'Z' || axe == 'z')
		matrice = mat_rot_z(rad_angle, matrice);
	return (matrice);
}
