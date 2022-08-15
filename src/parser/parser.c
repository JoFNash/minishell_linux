#include "minishell.h"
#include "parser.h"


int group_parser(t_list **lexer, t_group **gr)
{
	int error_code;

	*gr = (t_group *) ft_calloc(sizeof(t_group), 1);
	if (*gr == NULL)
		return (MALLOC_ERROR);
	if (((t_token *)((*lexer)->content))->type == e_newline || ((t_token *)((*lexer)->content))->type == e_pipe)
	{
		printf("minishell: syntax error near unexpected token \'%.*s\'\n", ((t_token *)((*lexer)->content))->len, ((t_token *)((*lexer)->content))->token);
		return (VALID_ERROR);
	}
	while (((t_token *)((*lexer)->content))->type != e_newline && ((t_token *)((*lexer)->content))->type != e_pipe)
	{
		error_code = parse_redirect(lexer, *gr);
		if (error_code != SUCCES)
			return (error_code);
		error_code = parse_arg(lexer, *gr);
		if (error_code != SUCCES)
			return (error_code);
	}
	if (((t_token *)((*lexer)->content))->type == e_pipe)
		(*gr)->pipe_output = 1;
	*lexer = (*lexer)->next;
	return (SUCCES);
}

int parser(t_list *lexer, t_base *base)
{
	t_group *group;
	t_list	*all_groups;
	int		error_code;

	all_groups = NULL;
	if (check_parenthesis(lexer))
		return (2);
	while (lexer != NULL)
	{
		error_code = group_parser(&lexer, &group);
		if (error_code != SUCCES)
		{
			ft_lstclear(&all_groups, free_group_list);
			return (error_code);
		}
		ft_lstadd_back(&all_groups, ft_lstnew((void *)group));
	}
	set_pipe(all_groups);
	base->groups = all_groups;
//	ft_lstiter(all_groups, print_group);
	return (SUCCES);
}