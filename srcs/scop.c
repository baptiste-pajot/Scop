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

static const char	*ft_vertex_shader(void)
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
** Set color of vertex to white
*/

static const char	*ft_fragment_shader(void)
{
	return ("#version 410\n"
	"out vec4 frag_colour;\n"
	"void main() {\n"
	"  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);\n"
	"}\n");
}

static void			display(void)
{
	GLfloat			vertices[] = {
		-0.5, +0.5, +0.0,
		+0.5, +0.5, +0.0,
		+0.5, -0.5, +0.0,
		-0.5, -0.5, +0.0,
		-0.6, +0.4, +0.0,
	};

	GLuint			indices[] = {
		0, 1, 2,
		2, 3, 4
	};

	GLuint			vao;
	GLuint			vbov;
	GLuint			vboi;

	const char		*txt_vertex_shader = ft_vertex_shader();
	const char		*txt_fragment_shader = ft_fragment_shader();

	// Generate and activate the Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate and activate the Vertex Buffer Object Vertices
	glGenBuffers(1, &vbov);
	glBindBuffer(GL_ARRAY_BUFFER, vbov);
	// Copy data to VBO Vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Generate and activate the Vertex Buffer Object Indices
	glGenBuffers(1, &vboi);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi);
	// Copy data to VBO Indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
			GL_STATIC_DRAW);

	// Create and compile the Vertex Shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &txt_vertex_shader, NULL);
	glCompileShader(vs);

	// Create and compile the Fragment Shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &txt_fragment_shader, NULL);
	glCompileShader(fs);

	// Link the Vertex and the Fragment Shaders
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	glUseProgram(shader_programme);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Clear the screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDeleteProgram(shader_programme);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteBuffers(1, &vbov);
	glDeleteBuffers(1, &vboi);
	glDeleteVertexArrays(1, &vao);
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
