/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhong <fhong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 23:57:39 by fhong             #+#    #+#             */
/*   Updated: 2018/08/29 04:05:02 by mjacques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_asm.h"

char	*ft_checklabel(char *label)
{
	int		i;

	i = -1;
	while (label[++i])
	{
		if (!ft_strchr(LABEL_CHARS, label[i]))
		{
			free(label);
			ft_error("ERROR: invalid Label");
		}
	}
	return (label);
}

int		print_line(t_line *line, t_label *label, int file, int index)
{
	int	i;

	i = 0;
	ft_putcharsize_fd(line->op->opcode, file, 1);
	if (line->op->is_coding_byte == 1)
		print_arg_type(line->op->p, file);
	line->str += ft_strlen(line->op->op_name);
	while (i < line->op->arg_nbr)
	{
		while (*line->str && ft_isspace(*line->str))
			line->str++;
		if (line->op->p[i] == REG_CODE)
			line->str = print_reg(line->str, 1, file);
		else if (line->op->p[i] == DIR_CODE)
			line->str = print_dir(line, label, file, index);
		else if (line->op->p[i] == IND_CODE)
			line->str = print_ind(line, label, file, index);
		while (*line->str && *line->str != SEPARATOR_CHAR
			&& !ft_isspace(*line->str))
			line->str++;
		if (*line->str == SEPARATOR_CHAR)
			line->str++;
		i++;
	}
	return (index + line->size);
}

void	print_op(t_label *list, int file)
{
	t_label	*begin;
	t_line	*line_tmp;
	int		index;

	begin = list;
	while (list)
	{
		index = list->index;
		line_tmp = list->line;
		while (line_tmp && line_tmp->str != NULL)
		{
			index = print_line(line_tmp, begin, file, index);
			line_tmp = line_tmp->next;
		}
		list = list->next;
	}
}