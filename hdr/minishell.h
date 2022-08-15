#ifndef MINISHELL_H
# define MINISHELL_H


# include "../src/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <dirent.h>
#include <signal.h>


#define VALID_ERROR 1
#define MALLOC_ERROR -1
#define FORK_ERROR -2
#define SUCCES 0
#define ENV_NOT_FOUND -405
#define DIR_ERROR -3
#define DIR_NOT_FOUND -42
#define NOT_FOUND -404
#define EXEC_ERROR -5
#define FILE_ERROR -21
#define END_OF_LEXER 2


enum e_type
{
	e_pipe,
	e_redirect,
	e_reverse_redirect,
	e_double_redirect,
	e_double_reverse_redirect,
	e_open_parenthesis,
	e_close_parenthesis,
	e_and,
	e_or,
	e_newline,
	e_str
};

typedef struct s_dict
{
	char *key;
	char *value;
}		t_dict;


typedef struct s_token
{
	char	*token;
	int 	len;
	enum	e_type type;
	int		rep_var;
}			t_token;

typedef struct s_base
{
	t_list	*env_lst;
	char 	**env_arr;

	t_list	*lexer;
	t_list	*groups;

	pid_t *pid;

	char	*command;

	char	cwd[PATH_MAX];
}			t_base;

typedef struct s_arg
{
	char	*arg;
	int		rep_var;
}			t_arg;

typedef struct s_redirect
{
	int 		rep_var;
	enum e_type	type_redirect;
	char		*redirect_file;
}				t_redirect;

typedef struct s_group
{
	char		*program;

	t_arg		*arg;
	char 		**arg_str;
	int			number_arg;

//	t_redirect redirect;
//	t_redirect reverse_redirect;

	t_redirect	*redirect;
	int 		number_redirect;

	t_redirect	*reverse_redirect;
	int 		number_reverse_redirect;


	int 		fd_redirect;
	int 		fd_reverse_redirect;
	int 		buf_sr_fd;
	int 		buf_rr_fd;

	int			use_fork;

	int 		pipe_input;
	int 		pipe_output;
}			t_group;

//executer
int executer(t_group *group, t_base *base);

//builtin
int echo(char **arg, int num_arg);
int pwd(t_base *base);
int cd(char **arg, int num_arg);

//pre_action
int chech_builtin(t_group *group, t_base *base);
int pre_action(t_base *base);

//parser
int parser(t_list *lexer, t_base *base);
void free_group_list(void *content);

//lexer
int lexer(char *command, t_base *base);
void free_token(void *content);
void print_token(void *content);

//parse lst and lst utils
t_list *parse_envp(char *envp[]);
void print_content(void *content);
void free_dict(void *content);

//main
char *read_cmd(t_base *base);
int get_cwd(t_base *base);
int is_space_string(char *s);

int	insert_var(char **str, t_list *env);


//env
char	*find_in_env(t_list *env, char *key);


//free
int free_arr(char **s);
int free_one(void *k);

#endif