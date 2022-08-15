#include "lexer.h"
#include "minishell.h"

void free_token(void *content)
{
	t_token *c;

	c = (t_token *)content;
	free(c);
}

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int is_metachar(char c)
{
	if (c == '|' || c == '>' || c == '<' || \
		c == '(' || c == ')')
		return (1);
	return (0);
}

void print_lexer(void *content)
{
	t_token *c = (t_token *)content;
	write(1, "_",1);
	write(1, c->token, c->len);
	write(1, "_",1);
	printf("\n-----------------\n");
}

void print_token(void *content)
{
	t_token *c = (t_token *)content;
	write(1, "_", 1);
	write(1, c->token, c->len);
	write(1, "_", 1);
	write(1, "\n", 1);
}

char *skip_spaces(char *s)
{
	while (is_space(*s))
		s++;
	return (s);
}

int check_qutes(char *s)
{
	char c;
	int qo;

	qo = 0;
	while (*s != '\0')
	{
		if ((*s == '\'' || *s == '"'))
		{
			if (!qo)
			{
				c = *s;
				qo = 1;
			}
			else if (c == *s)
				qo = 0;
		}
		s++;
	}
	return (qo);
}