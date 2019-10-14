/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 11:30:49 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 17:15:45 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

static const char	*ft_vertex_shader(void)
{
	return ("#version 400\n"
	"in vec3 vp;\n"
	"void main() {\n"
	"  gl_Position = vec4(vp, 1.0);\n"
	"}\n");
}

static const char	*ft_fragment_shader(void)
{
	return ("#version 400\n"
	"out vec4 frag_colour;\n"
	"void main() {\n"
	"  frag_colour = vec4(1, 1, 1, 1);\n"
	"}\n");
}

static void			display(void)
{
	float			points[] = {
		+0.0, +0.5, +0.0,
		-0.5, -0.5, +0.0,
		+0.5, -0.5, +0.0,
		+0.0, +0.8, +0.0,
		-0.5, +0.7, +0.0,
		+0.5, +0.7, +0.0
	};
	GLuint			vbo;
	GLuint			vao;
	const char		*txt_vertex_shader = ft_vertex_shader();
	const char		*txt_fragment_shader = ft_fragment_shader();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &txt_vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &txt_fragment_shader, NULL);
	glCompileShader(fs);
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_programme);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 3, 3);
}

int					main(void)
{
	t_env	e;

	e.mlx = mlx_init();
	e.win = mlx_new_opengl_window(e.mlx, W_WIDTH, W_HEIGHT, W_NAME);
	mlx_opengl_window_set_context(e.win);
	printf("Graphic Card : %s\n", (char *)glGetString(GL_RENDERER));
	printf("Version : %s\n", (char *)glGetString(GL_VERSION));
	printf("GLSL : %s\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
	display();
	mlx_opengl_swap_buffers(e.win);
	mlx_loop(e.mlx);
	return (0);
}
