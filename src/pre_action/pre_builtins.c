#include "minishell.h"
#include "pre_action.h"

int chech_builtin(t_group *group, t_base *base)
{
	if (ft_strncmp(group->program, "echo", 4) == 0)
		return (echo(group->arg_str, group->number_arg));
	if (ft_strncmp(group->program, "pwd", 3) == 0)
		return (pwd(base));
	if (ft_strncmp(group->program, "cd", 2) == 0)
		return (cd(group->arg_str, group->number_arg));
	return (NOT_FOUND);



}