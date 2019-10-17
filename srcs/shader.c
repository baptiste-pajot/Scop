/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shader.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 14:20:24 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 12:27:09 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌───────────────┐
** │ Vertex Shader │
** └───────────────┘
** OpenGL Shading Language (GLSL 4.10)
** Keep the x,y,z coordinates and add the w homogeneous coordinates equal to 1
** Keep the point color between in and out
*/

static char			*txt_vertex_shader(void)
{
	return ("#version 410\n"
	"layout (location = 0) in vec3 glVertex;\n"
	"layout (location = 1) in vec3 glColor;\n"
	"uniform mat4 matRX;\n"
	"uniform mat4 matRY;\n"
	"out vec3 frgColor;\n"
	"void main() {\n"
	"  gl_Position = matRX * matRY * vec4(glVertex, 1.0);\n"
	"  frgColor  = glColor;\n"
	"}\n");
}

/*
** ┌─────────────────┐
** │ Fragment Shader │
** └─────────────────┘
** OpenGL Shading Language (GLSL 4.10)
** Set color of vertex
*/

static char			*txt_fragment_shader(void)
{
	return ("#version 410\n"
	"in vec3 frgColor;\n"
	"out vec4 glFragColor;\n"
	"void main() {\n"
	"  glFragColor = vec4(frgColor, 1.0);\n"
	"}\n");
}

/*
** ┌─────────────────┐
** │ Manage Shader   │
** └─────────────────┘
** Create and compile the Vertex Shader
** Create and compile the Fragment Shader
** Link the Vertex and the Fragment Shaders
*/

void				manage_shader(t_gl *gl, float rad_angle)
{
	GLfloat		*mat_rot_X;
	GLfloat		*mat_rot_Y;
	GLint		id_mat_rot_X;
	GLint		id_mat_rot_Y;

	gl->vs = glCreateShader(GL_VERTEX_SHADER);
	gl->txt_vs = txt_vertex_shader();
	glShaderSource(gl->vs, 1, &(gl->txt_vs), NULL);
	glCompileShader(gl->vs);
	gl->fs = glCreateShader(GL_FRAGMENT_SHADER);
	gl->txt_fs = txt_fragment_shader();
	glShaderSource(gl->fs, 1, &(gl->txt_fs), NULL);
	glCompileShader(gl->fs);
	gl->sp = glCreateProgram();
	glAttachShader(gl->sp, gl->fs);
	glAttachShader(gl->sp, gl->vs);
	glLinkProgram(gl->sp);
	glUseProgram(gl->sp);
	id_mat_rot_X = glGetUniformLocation(gl->sp, "matRX");
	id_mat_rot_Y = glGetUniformLocation(gl->sp, "matRY");
	mat_rot_X = mat_rot('X', rad_angle);
	mat_rot_Y = mat_rot('Y', rad_angle);
	glUniformMatrix4fv(id_mat_rot_X, 1, GL_FALSE, mat_rot_X);
	glUniformMatrix4fv(id_mat_rot_Y, 1, GL_FALSE, mat_rot_Y);
}
