/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:40:56 by gonische          #+#    #+#             */
/*   Updated: 2024/09/14 14:10:24 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	**parse_input(char *input, t_list *env)
{
	t_list		*tokens;

	if (!input)
		return (NULL);
	tokens = tokenize(input, env);
	print_tokens(tokens);
	free (input);
	return (NULL); // TODO
}
