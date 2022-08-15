#include <minishell.h>
#include <pre_action.h>

int heredoc()
{
	return (1);
}

int straight_redirect(t_group *group, t_list *env, t_redirect *redirect, int number_redirect)
{
	int i;
	int fd;

	i = 0;
	if (number_redirect == 0)
	{
		group->buf_sr_fd = -2;
		return (SUCCES);
	}
	while(i < number_redirect - 1)
	{
		if (redirect[i].type_redirect == e_redirect || redirect[i].type_redirect == e_double_redirect)
			fd = open(redirect[i].redirect_file, O_RDWR | O_CREAT);
		if (fd == -1)
			return (FILE_ERROR);
		close(fd);
		i++;
	}
	if (redirect[i].type_redirect == e_redirect)
		fd = open(redirect[i].redirect_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redirect[i].type_redirect == e_double_redirect)
		fd = open(redirect[i].redirect_file,	O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redirect[i].redirect_file);
		return (FILE_ERROR);
	}
	group->fd_redirect = fd;
	group->buf_sr_fd = dup(1);
	dup2(fd, 1);
	close(fd);
	return (SUCCES);
}

int reverse_redirect(t_group *group, t_list *env, t_redirect *redirect, int number_redirect)
{
	int i;
	int fd;

	i = 0;
	if (number_redirect == 0)
	{
		group->buf_rr_fd = -2;
		return (SUCCES);
	}
	while(i < number_redirect - 1)
	{
		if (redirect[i].type_redirect == e_reverse_redirect)
			fd = open(redirect[i].redirect_file, O_RDWR);
		else if (redirect[i].type_redirect == e_double_reverse_redirect)
			fd = heredoc();
		if (fd == -1)
		{
			perror(redirect[i].redirect_file);
			return (FILE_ERROR);
		}
		close(fd);
		i++;
	}
	if (redirect[i].type_redirect == e_reverse_redirect)
		fd = open(redirect[i].redirect_file, O_RDWR);
	else if (redirect[i].type_redirect == e_double_reverse_redirect)
		fd = heredoc();
	if (fd == -1)
	{
		perror(redirect[i].redirect_file);
		return (FILE_ERROR);
	}
	group->fd_reverse_redirect = fd;
	group->buf_rr_fd = dup(0);
	dup2(fd, 0);
	close(fd);
	return (SUCCES);
}


int redirect(t_group *group, t_list *env)
{
	//add env to redirect file
	straight_redirect(group, env, group->redirect, group->number_redirect);
	reverse_redirect(group, env, group->reverse_redirect, group->number_reverse_redirect);
}