/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 11:30:49 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 12:03:00 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/scop.h"

int		main(void)
{
	t_env	e;

	printf("Window Open\n");
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, W_WIDTH, W_HEIGHT, W_NAME);
	mlx_loop(e.mlx);
	return (0);
}
