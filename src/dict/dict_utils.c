# include "minishell.h"

//разбиение строки КЛЮЧ=ЗНАЧЕНИЕ на элемент словаря
t_dict *parse_line_envp(char *line)
{
	t_dict *res;

	res = (t_dict *)ft_calloc(sizeof(t_dict), 1);
	if (res == NULL)
		return (NULL);
	int i = 0;
	while (line[i] != '=')
		i++;
	res->key = ft_substr(line, 0, i);
	res->value = ft_substr(line, i + 1, ft_strlen(line));
	return (res);
}

t_list *parse_envp(char *envp[])
{
	int		i;
	t_list	*env_lst;

	if (envp == NULL)
		return (NULL);
	env_lst = ft_lstnew((void *) parse_line_envp(envp[0]));
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&env_lst, ft_lstnew((void *) parse_line_envp(envp[i])));
		i++;
		if (errno != 0)
			return (NULL);
	}
	return (env_lst);
}


void print_content(void *content)
{
	t_dict *c = (t_dict *)content;
	printf("%-40s%s\n", c->key, c->value);
}

void free_dict(void *content)
{
	t_dict *c = (t_dict *)content;
	free(c->key);
	free(c->value);
	free(c);
}




