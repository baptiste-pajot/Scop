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
*/

static char			*txt_vertex_shader(void)
{
	return ("#version 410\n"
	"in vec3 vp;\n"
	"void main() {\n"
	"  gl_Position = vec4(vp, 1.0);\n"
	"}\n");
}

/*
** ┌─────────────────┐
** │ Fragment Shader │
** └─────────────────┘
** OpenGL Shading Language (GLSL 4.10)
** Set color of vertex to black
*/

static char			*txt_fragment_shader(void)
{
	return ("#version 410\n"
	"out vec4 frag_colour;\n"
	"void main() {\n"
	"  frag_colour = vec4(0.0, 0.0, 0.0, 1.0);\n"
	"}\n");
}

void                manage_shader(t_gl *gl)
{
    // Create and compile the Vertex Shader
	gl->vs = glCreateShader(GL_VERTEX_SHADER);
	gl->txt_vs = txt_vertex_shader();
	glShaderSource(gl->vs, 1, &(gl->txt_vs), NULL);
	glCompileShader(gl->vs);

	// Create and compile the Fragment Shader
	gl->fs = glCreateShader(GL_FRAGMENT_SHADER);
	gl->txt_fs = txt_fragment_shader();
	glShaderSource(gl->fs, 1, &(gl->txt_fs), NULL);
	glCompileShader(gl->fs);

	// Link the Vertex and the Fragment Shaders
	gl->sp = glCreateProgram();
	glAttachShader(gl->sp, gl->fs);
	glAttachShader(gl->sp, gl->vs);
	glLinkProgram(gl->sp);
	glUseProgram(gl->sp);
}