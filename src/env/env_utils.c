/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 23:38:03 by gonische          #+#    #+#             */
/*   Updated: 2024/12/14 14:45:16 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "env.h"
#include <stdio.h>
#include <stdlib.h>

bool	env_is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

size_t	get_env_size(t_env *env)
{
	size_t	size;
	t_env	*current;

	size = 0;
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

t_env	*get_env(t_env *env, const char *key)
{
	t_env	*current;

	if (!key)
		return (NULL);
	current = env;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	**env_list_to_array(t_env *env)
{
	char	**arr;
	char	*temp;
	t_env	*current;
	int		i;

	arr = malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		if (current->value)
		{
			temp = ft_strjoin(current->key, "=");
			arr[i] = ft_strjoin(temp, current->value);
			free(temp);
		}
		else
			arr[i] = ft_strdup(current->key);
		if (!arr[i])
		{
			free_2dmatrix(arr);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}
