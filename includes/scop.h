/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scop.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: bpajot <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 11:31:07 by bpajot       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 12:02:18 by bpajot      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx_macos/mlx.h"

# define W_HEIGHT	1200
# define W_WIDTH		2400
# define W_NAME		"SCOP"

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	void	*image;
	int		bpp;
	int		endian;
}				t_env;

#endif
