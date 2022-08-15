#ifndef PARSER_H
#define PARSER_H

void set_pipe(t_list *group);
int check_pipe(t_list *lexer);
int check_parenthesis(t_list *lexer);
//int	manager_redirect(t_list **lexer, t_group *group);
int parse_redirect(t_list **lexer, t_group *group);
int free_group(t_group *group);
int parse_arg(t_list **lexer, t_group *group);
int free_group_arg(t_arg *arg, int num_arg);

t_arg	*add_arg(t_arg *arg, int num_arg, t_token *token);

int free_group_redirect(t_redirect *arg, int num_arg);

void print_group(void *gr);


#endif