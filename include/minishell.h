/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:25:50 by gonische          #+#    #+#             */
/*   Updated: 2024/09/13 17:23:07 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "limits.h"
# include "../libft/libft.h"

#define SHELL_NAME "Minishell"

# ifndef ARG_MAX
#  define ARG_MAX	131072
# endif

// Tokens
# define TOKEN_UNKNOWN		0
# define TOKEN_IN			1	// <
# define TOKEN_OUT			2	// >
# define TOKEN_PIPE			3	// |
# define TOKEN_INDELIMITER 	4	// <<
# define TOKEN_OUTAPPEND	5	// >>
# define TOKEN_DOUBLEQUOTE	6 	// ""
# define TOKEN_VARIABLE		7	// $
# define TOKEN_SINGLEQUOTE	8	// '
# define TOKEN_WORD			9	// str
# define TOKEN_FLAG			10	// -FLAG

typedef struct s_token
{
	char	token;
	char	*value;
}	t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	*path;
	t_token	*arg[ARG_MAX];
	int		in;
	int		out;
	int		err;
}	t_cmd;

/*
	p_parse.c
*/
t_cmd	**parse_input(char *input, char **envp);

/*
	p_tokenizer.c
*/
t_list	*tokenize(char *s, char const **envp);

/*
	p_tokenizer_utils.c
*/
t_list	*alloc_token(char const *s, size_t len);
t_token *combine_words(t_list *words);
int		expand_variable(char const *s, char const **envp, t_list **words);
int		str_to_token_type(const char *s);
void	print_tokens(t_list *lst);

/*
	p_utils.c
*/

/*
	p_booleans.c
*/
bool	is_space(char c);
bool	is_quote(char c);
int		is_operator(const char *s);
bool	is_metachar(const char *s);

/*
	utils.c
*/
void	print_2dmatrix(char const **matrix);
void	free_2dmatrix(char **matrix);

#endif // MINISHELL_H