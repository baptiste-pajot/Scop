/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vbo.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 14:22:35 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:22:37 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/scop.h"

/*
** ┌───────────────┐
** │ Create VAO    │
** └───────────────┘
** Generate and Activate the Vertex Array Object
*/

static void		create_vao(t_gl *gl)
{
	glGenVertexArrays(1, &(gl->vao));
	glBindVertexArray(gl->vao);
}

/*
** ┌────────────────────────┐
** │ Create VBO Vertices    │
** └────────────────────────┘
** Generate and Activate the Vertex Buffer Object Vertices
** Then, Copy data
*/

static void		create_vbov(t_gl *gl)
{
	GLfloat			vertices[] = {
		-0.5, +0.5, +0.0,
		+0.5, +0.5, +0.0,
		+0.5, -0.5, +0.0,
		-0.5, -0.5, +0.0,
		-0.6, +0.4, +0.0
	};

	glGenBuffers(1, &(gl->vbov));
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbov);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

/*
** ┌────────────────────────┐
** │ Create VBO Indices     │
** └────────────────────────┘
** Generate and Activate the Vertex Buffer Object Indices
** Then, Copy data
*/

static void		create_vboi(t_gl *gl)
{
	GLuint			indices[] = {
		0, 1, 2,
		2, 3, 4
	};

	glGenBuffers(1, &(gl->vboi));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl->vboi);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);
}

void			manage_vbo(t_gl *gl)
{
	create_vao(gl);
	create_vbov(gl);
	create_vboi(gl);
}
