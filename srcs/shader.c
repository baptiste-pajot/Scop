/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shader.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 14:20:24 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 15:15:48 by bpajot      ###    #+. /#+    ###.fr     */
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
	"uniform mat4 matProj;\n"
	"uniform mat4 matView;\n"
	"uniform mat4 matModel;\n"
	"out vec3 frgColor;\n"
	"void main() {\n"
	"  gl_Position = matProj * matView * matModel * vec4(glVertex, 1.0);\n"
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
	GLfloat		*mat_proj;
	GLfloat		*mat_view;
	GLfloat		*mat_model;
	GLint		id_mat_proj;
	GLint		id_mat_view;
	GLint		id_mat_model;

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
	id_mat_proj = glGetUniformLocation(gl->sp, "matProj");
	id_mat_view = glGetUniformLocation(gl->sp, "matView");
	id_mat_model = glGetUniformLocation(gl->sp, "matModel");
	rad_angle++;
	mat_view = mat_transpose(mat_translate(0.0, 0.0, -2.0));
	mat_proj = mat_projection();
	mat_model = mat_rot('Y', rad_angle);
	glUniformMatrix4fv(id_mat_proj, 1, GL_FALSE, mat_proj);
	glUniformMatrix4fv(id_mat_view, 1, GL_FALSE, mat_view);
	glUniformMatrix4fv(id_mat_model, 1, GL_FALSE, mat_model);
}
