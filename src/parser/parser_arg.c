#include "minishell.h"
#include "parser.h"

t_arg	*add_arg(t_arg *arg, int num_arg, t_token *token)
{
	t_arg	*res;
	int 	i;

	res = (t_arg *)ft_calloc(sizeof(t_arg), num_arg + 1);
	if (res == NULL && free_group_arg(arg, num_arg))
		return (NULL);
	i = -1;
	while (++i < num_arg)
		res[i] = arg[i];
	res[i].arg = ft_substr(token->token, 0, token->len);
	if (res[i].arg == NULL && free_group_arg(res, num_arg + 1) && free_group_arg(arg, num_arg))
		return (NULL);
	res[i].rep_var = token->rep_var;
	free(arg);
	return (res);
}

int parse_arg(t_list **lexer, t_group *group)
{
	t_token	*content;


	content = ((t_token *)((*lexer)->content));
	if (content->type != e_str)
		return (SUCCES);
	group->arg = add_arg(group->arg, (group->number_arg)++, content);
	if (group->arg == NULL && free_group(group))
		return (MALLOC_ERROR);
	if (group->number_arg != 0)
		group->program = group->arg[0].arg;
	(*lexer) = (*lexer)->next;
	return (SUCCES);
}