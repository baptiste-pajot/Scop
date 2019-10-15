/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shader.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 14:20:24 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:20:26 by bpajot      ###    #+. /#+    ###.fr     */
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
	"out vec3 frgColor;\n"
	"void main() {\n"
	"  gl_Position = vec4(glVertex, 1.0);\n"
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

void				manage_shader(t_gl *gl)
{
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
}
