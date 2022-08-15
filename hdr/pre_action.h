#ifndef PRE_ACTION_H
#define PRE_ACTION_H

int arg_in_arr_str(t_group *group, t_list *env);
int run_command(t_group *group, t_base *base);
int run_exec(t_base *base, char *bin, char **arg);
int apply_fork(t_group *group, t_base *base, int i);
int kill_pid(t_base *base);
int is_builtin(t_group *group);
int redirect(t_group *group, t_list *env);

#endif