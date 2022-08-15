#include "minishell.h"
#include "executer.h"


int get_path(t_list *env, char ***res)
{
	char	*s;
	char 	*path;
	int		i;

	s = find_in_env(env, "PATH");
	if (s == NULL)
		return (ENV_NOT_FOUND);
	path = ft_strdup(s);
	if (path == NULL)
	{
		free(s);
		return (MALLOC_ERROR);
	}
	*res = ft_split(path, ':');
	free(path);
	if (*res == NULL)
	{
		free(s);
		return (MALLOC_ERROR);
	}
	return (SUCCES);
}

int check_bin(char *path, char *bin)
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir(path);
	if (dir == NULL)
	{
		printf("Dir error\n");
		return (DIR_ERROR);
	}
	dent = readdir(dir);
	while (dent)
	{
		if (dent->d_type == 8)
			if (ft_strncmp(dent->d_name, bin, ft_strlen(bin) + 1) == 0)
			{
				closedir(dir);
				return (SUCCES);
			}
		dent = readdir(dir);
	}
	closedir(dir);
	if (errno != 0)
	{
		perror(strerror(errno));
		errno = 0;
		return (DIR_ERROR);
	}
	return (DIR_NOT_FOUND);
}

int find_bin(t_list *env, char *bin, char **res)
{
	int		error_code;
	char	**path_arr;
	char 	*path;
	int 	i;

	error_code = get_path(env, &path_arr);
	if (error_code != SUCCES)
		return (error_code);
	i = 0;
	while (path_arr[i])
	{
		error_code = check_bin(path_arr[i], bin);
		if (error_code == DIR_ERROR && free_arr(path_arr))
			return (error_code);
		if (error_code == SUCCES)
			break;
		i++;
	}
	if (error_code == DIR_NOT_FOUND && free_arr(path_arr))
	{
		printf("%s: command not found\n", bin);
		return (error_code);
	}
	path = ft_strjoin(path_arr[i], "/");
	*res = ft_strjoin(path, bin);
	free(path);
	if (*res == NULL && free_arr(path_arr))
		return (MALLOC_ERROR);
	free_arr(path_arr);
	return (SUCCES);
}
