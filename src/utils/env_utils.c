#include "minishell.h"

// варианты: 

// Name_01 				-> 		Name_01
// $Name_01 			-> 		Olga
// Hello$Name_01 		-> 		HelloOlga
// Hello$Name_01$Name_02 -> 	HelloOlgaAlex
// Hello$Name_01_klock 	-> 		Hello

char *find_in_env(t_list *env, char *key)
{
	t_dict *c;
	int 	l;

	l = ft_strlen(key);
	while (env)
	{
		c = (t_dict *)env->content;
		if (ft_strncmp(c->key, key, l) == 0)
			return (c->value);
		env = env->next;
	}
	return (NULL);
}

size_t min(size_t n1, size_t n2)
{
	if (n1 <= n2)
		return (n1);
	return (n2);
}

char *ft_alloc_mem_linepair(char *str1, char* str2, size_t *len1, size_t *len2, size_t n)
{
	char *res;

	if (!str1 || !str2)
		return (NULL);
	*len1 = ft_strlen(str1);
	*len2 = ft_strlen(str2);
	res = (char *)malloc(sizeof(char) * (*len1 + *len2 + 1));
	if (!res)
		return (NULL);
	return (res);
}

char *ft_strnconcat(char *dest, char *src, size_t start, size_t end)
{
	char *res;
	size_t len_dest;
	size_t len_src;
	size_t i;
	size_t j;

	if (!dest || !src)
		return (NULL);
	if (start > end || start > ft_strlen(src) || end > ft_strlen(src))
		return (NULL);
	res = ft_alloc_mem_linepair(dest, src, &len_dest, &len_src, end - start);
	if (!res)
		return (NULL);			
	i = 0;
	while (dest[i] != '\0')
	{
		res[i] = dest[i];
		i++;
	}
	j = 0;
	while (j + start < end)
	{
		res[i] = src[j + start];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char *get_perem(char *str, size_t start, size_t end)
{
	char *res;
	size_t i;

	if (end < start)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < end)
	{
		res[i] = str[i + start];
	}
	res[i] = '\0';
	return (res);
}

int	insert_var(char **str, t_list *env)
{
	size_t i;
	size_t start;
	size_t end;
	char *perem;
	char *res;
	char *key;

	i = 0;
	res = "";

	if (!(*str))
		return (0); // (?)
	// до первого символа '$' (или до '\0')
	while ((*str)[i] && (*str)[i] != '$')
	{
		i++;
	}
	// положили в результат все, что находится до первого '$' (или до '\0')
	res = ft_strnconcat(res, *str, 0, i);
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1])
		{
			start = i;
			while (!ft_isalnum((*str)[i]) || !((*str)[i] = '_'))
			{
				i++;
			}
			perem = get_perem(*str, start + 1, i);
			key = find_in_env(env, perem);
			if (key == NULL)
				res = ft_strnconcat(res, *str, start, i);
			else
				res = ft_strnconcat(res, key, 0, ft_strlen(key));
		}
		
		start = i;
		while (!ft_isalnum((*str)[i]) && !((*str)[i] = '_'))
		{
			i++;
		}
		res = ft_strnconcat(res, *str, start, i);
	}
	return (SUCCES);
}
