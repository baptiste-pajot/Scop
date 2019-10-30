/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shader.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <bpajot@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 14:20:24 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 11:38:22 by bpajot      ###    #+. /#+    ###.fr     */
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
	if (gl->paint == COLOR)
	{
		return ("#version 410\n"
		"in vec2 textureUV;\n"
		"out vec4 glFragColor;\n"
		"uniform sampler2D textureBMP;\n"
		"void main() {\n"
		"	float	grey;\n"
		"	grey = (gl_PrimitiveID % 6) / 10.0;\n"
		"	glFragColor = vec4(grey, grey, grey, 1.0);\n"
		"}\n");
	}
	else
	{
		return ("#version 410\n"
		"in vec2 textureUV;\n"
		"out vec4 glFragColor;\n"
		"uniform sampler2D textureBMP;\n"
		"void main() {\n"
		"	float	grey;\n"
		"	grey = (gl_PrimitiveID % 6) / 10.0;\n"
		"	glFragColor = texture(textureBMP, textureUV);\n"
		"}\n");
	}
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

void				manage_shader(t_gl *gl, float rad_angle)
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
	glUniform1f(glGetUniformLocation(gl->sp, "maxSize"), gl->center.max_size);
	glUniformMatrix4fv(glGetUniformLocation(gl->sp, "matProj"), 1, GL_FALSE,
		mat_projection());
	glUniformMatrix4fv(glGetUniformLocation(gl->sp, "matView"), 1, GL_FALSE,
		mat_mult(mat_rot('Y', rad_angle + gl->center.cam_rot_y), mat_mult(
		mat_rot('X', gl->center.cam_rot_x), mat_transpose(mat_translate(
		gl->center.cam_offset_x, gl->center.cam_offset_y,
		gl->center.cam_offset_z)))));
	glUniformMatrix4fv(glGetUniformLocation(gl->sp, "matModel"), 1, GL_FALSE,
		mat_mult(mat_transpose(mat_translate(-gl->center.mean[0],
		-gl->center.mean[1], -gl->center.mean[2])), mat_rot('Y', rad_angle)));
}
