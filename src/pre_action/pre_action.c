#include "minishell.h"
#include "pre_action.h"

int arg_in_arr_str(t_group *group, t_list *env)
{
	int i;


	//добавить переменные среды внутрь агрументов
	group->arg_str = ft_calloc(sizeof(char *), group->number_arg + 1);
//	group->arg_str = NULL;
	if (group->arg_str == NULL)
	{
//		printf("Malloc Error");
		return (MALLOC_ERROR);
	}
	i = 0;
	while (i < group->number_arg)
	{
		group->arg_str[i] = group->arg[i].arg;
		if (insert_var(&(group->arg_str[i]), env) != SUCCES)
			return (MALLOC_ERROR);
		i++;
	}
	group->arg_str[i] == NULL;
	return (SUCCES);
}

int pre_action(t_base *base)
{
	int		error_code;
	int 	status;
	t_group	*group;
	t_list	*all_groups;
	int 	i;

	all_groups = base->groups;

	if (ft_lstsize(all_groups) == 1 && is_builtin(all_groups->content))
		return (run_command(all_groups->content, base));

	base->pid = ft_calloc(sizeof (pid_t), ft_lstsize(base->groups));
	if (base->pid == NULL)
		return (MALLOC_ERROR);
	i = 0;
	while (all_groups)
	{
		group = (t_group *)all_groups->content;
		error_code = apply_fork(group, base, i);
		if (error_code != SUCCES && kill_pid(base))
			return (error_code);
		all_groups = all_groups->next;
		i++;
	}
	while (i)
	{
		waitpid(base->pid[i--], &status, 0);
//		printf("_%d_\n", WEXITSTATUS(status));
		if (WEXITSTATUS(status) != SUCCES && kill_pid(base))
			return (WEXITSTATUS(status));
	}
	return (SUCCES);
}
