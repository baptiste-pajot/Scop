/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 11:30:49 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 12:24:05 by bpajot      ###    #+. /#+    ###.fr     */
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

static void			delete_gl(t_gl *gl){
	glDeleteProgram(gl->sp);
	glDeleteShader(gl->vs);
	glDeleteShader(gl->fs);
	glDeleteBuffers(1, &(gl->vbov));
	glDeleteBuffers(1, &(gl->vboi));
	glDeleteVertexArrays(1, &(gl->vao));
}

static void			display(t_gl *gl)
{
	manage_vbo(gl);

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

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Clear the screen to white
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	delete_gl(gl);
}

static void			display_info(void)
{
	printf("Graphic Card : %s\n", (char *)glGetString(GL_RENDERER));
	printf("Version : %s\n", (char *)glGetString(GL_VERSION));
	printf("GLSL : %s\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

int					main(void)
{
	t_env	e;
	t_gl	gl;

	e.mlx = mlx_init();
	e.win = mlx_new_opengl_window(e.mlx, W_WIDTH, W_HEIGHT, W_NAME);
	mlx_opengl_window_set_context(e.win);
	display_info();
    printf("toto");
	display(&gl);
	mlx_opengl_swap_buffers(e.win);
	mlx_loop(e.mlx);
	return (0);
}
