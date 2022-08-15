#include "minishell.h"

int pwd(t_base *base)
{
	if (get_cwd(base))
		return (-1);
	printf("%s\n", base->cwd);
	return (0);
}
