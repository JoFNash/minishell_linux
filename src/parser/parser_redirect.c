#include "minishell.h"
#include "parser.h"


t_redirect	*add_redirect(t_redirect *redirect, int num_redirect, t_token *token, enum e_type type)
{
	t_redirect	*res;
	int 	i;

	res = (t_redirect *)ft_calloc(sizeof(t_redirect), num_redirect + 1);
	if (res == NULL && free_group_redirect(redirect, num_redirect))
		return (NULL);
	i = -1;
	while (++i < num_redirect)
		res[i] = redirect[i];
	res[i].redirect_file = ft_substr(token->token, 0, token->len);
	if (res[i].redirect_file == NULL && free_group_redirect(res, num_redirect + 1) && free_group_redirect(redirect, num_redirect))
		return (NULL);
	res[i].rep_var = token->rep_var;
	res[i].type_redirect = type;
	free(redirect);
	return (res);
}

int parse_redirect(t_list **lexer, t_group *group)
{
	if (((t_token *)((*lexer)->content))->type != e_redirect					&& \
		((t_token *)((*lexer)->content))->type != e_double_redirect				&& \
		((t_token *)((*lexer)->content))->type != e_reverse_redirect			&& \
		((t_token *)((*lexer)->content))->type != e_double_reverse_redirect)
		return (SUCCES);
	if (((t_token *)((*lexer)->next->content))->type != e_str)
	{
		printf("minishell: syntax error near unexpected token \'%.*s\'\n", ((t_token *) ((*lexer)->content))->len,
			   ((t_token *) ((*lexer)->content))->token);
		return (VALID_ERROR);
	}
	if (((t_token *)((*lexer)->content))->type == e_redirect || \
		((t_token *)((*lexer)->content))->type == e_double_redirect)
		group->redirect = add_redirect(group->redirect, (group->number_redirect)++, ((t_token *)((*lexer)->next->content)), ((t_token *)((*lexer)->content))->type);
	else
		group->redirect = add_redirect(group->reverse_redirect, (group->number_reverse_redirect)++, ((t_token *)((*lexer)->next->content)), ((t_token *)((*lexer)->content))->type);
	if (group->redirect == NULL && free_group(group))
		return (MALLOC_ERROR);
	(*lexer) = (*lexer)->next->next;
	return (SUCCES);
}