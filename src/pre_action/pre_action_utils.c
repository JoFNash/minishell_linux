#include "minishell.h"
#include "pre_action.h"

int kill_pid(t_base *base)
{
	int l;
	int i;

	l = ft_lstsize(base->groups);
	i = 0;
	while (i < l)
	{
		if (base->pid[i] != 0)
			kill(base->pid[i], SIGKILL);
		i++;
	}
	return (1);
}

int is_builtin(t_group *group)
{
	if ((ft_strncmp(group->program, "cd", 3) == 0		|| \
		ft_strncmp(group->program, "echo", 5) == 0		|| \
		ft_strncmp(group->program, "pwd", 4) == 0		|| \
		ft_strncmp(group->program, "export", 7) == 0	|| \
		ft_strncmp(group->program, "unset", 6) == 0		|| \
		ft_strncmp(group->program, "env", 4) == 0		|| \
		ft_strncmp(group->program, "exit", 5) == 0))
		return (1);
	return (0);
}