/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shader1.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 15:57:49 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/22 16:01:32 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌───────────────┐
** │ Vertex Shader │
** └───────────────┘
** OpenGL Shading Language (GLSL 4.10)
** Take the x,y,z coordinates and add the w homogeneous coordinates equal to 1
** Make the transformations with 3 matrixes
** Keep the point color between in and out
*/

static char			*txt_vertex_shader(void)
{
	return ("#version 410\n"
	"layout (location = 0) in vec3 glVertex;\n"
	"uniform float maxSize;\n"
	"uniform mat4 matProj;\n"
	"uniform mat4 matView;\n"
	"uniform mat4 matModel;\n"
	"out vec2 textureUV;\n"
	"void main() {\n"
	"	gl_Position = matProj * matView * matModel * vec4(glVertex, 1.0);\n"
	"	textureUV  = 10 * vec2(glVertex.z / maxSize, glVertex.x / maxSize"
	"		+ glVertex.y / maxSize);\n"
	"}\n");
}

/*
** ┌─────────────────┐
** │ Fragment Shader │
** └─────────────────┘
** OpenGL Shading Language (GLSL 4.10)
** Set color of vertex
*/

static char			*txt_fragment_shader(t_gl *gl)
{
	if (gl->paint == color && gl->paint_prev == color)
		return (fragment_shader_color_to_color());
	else if (gl->paint == color)
		return (fragment_shader_texture_to_color());
	else if (gl->paint_prev == color)
		return (fragment_shader_color_to_texture());
	else
		return (fragment_shader_texture_to_texture());
}

static void			send_uniform(t_gl *gl)
{
	glUniform1i(glGetUniformLocation(gl->sp, "textureBMP"), 0);
	glUniform1i(glGetUniformLocation(gl->sp, "texturePrev"), 1);
	glUniform1f(glGetUniformLocation(gl->sp, "maxSize"), gl->center.max_size);
	glUniform1f(glGetUniformLocation(gl->sp, "ratio"), gl->ratio);
	glUniformMatrix4fv(glGetUniformLocation(gl->sp, "matProj"), 1, GL_FALSE,
		mat_projection());
	glUniformMatrix4fv(glGetUniformLocation(gl->sp, "matView"), 1, GL_FALSE,
		mat_mult(mat_rot('Y', gl->center.rad_angle + gl->center.cam_rot_y),
		mat_mult(mat_rot('X', gl->center.cam_rot_x), mat_transpose(
		mat_translate(gl->center.cam_offset_x, gl->center.cam_offset_y,
		gl->center.cam_offset_z)))));
	glUniformMatrix4fv(glGetUniformLocation(gl->sp, "matModel"), 1, GL_FALSE,
		mat_mult(mat_transpose(mat_translate(-gl->center.mean[0],
		-gl->center.mean[1], -gl->center.mean[2])),
		mat_rot('Y', gl->center.rad_angle)));
}

/*
** ┌─────────────────┐
** │ Manage Shader   │
** └─────────────────┘
** Create and compile the Vertex Shader
** Create and compile the Fragment Shader
** Link the Vertex and the Fragment Shaders
** Calculate and send the proj, view and model matrixes to shader
*/

void				manage_shader(t_gl *gl)
{
	gl->vs = glCreateShader(GL_VERTEX_SHADER);
	gl->txt_vs = txt_vertex_shader();
	glShaderSource(gl->vs, 1, &(gl->txt_vs), NULL);
	glCompileShader(gl->vs);
	gl->fs = glCreateShader(GL_FRAGMENT_SHADER);
	gl->txt_fs = txt_fragment_shader(gl);
	glShaderSource(gl->fs, 1, &(gl->txt_fs), NULL);
	glCompileShader(gl->fs);
	gl->sp = glCreateProgram();
	glAttachShader(gl->sp, gl->fs);
	glAttachShader(gl->sp, gl->vs);
	glLinkProgram(gl->sp);
	glUseProgram(gl->sp);
	send_uniform(gl);
}
