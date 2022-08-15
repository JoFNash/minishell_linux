#ifndef LEXER_H
#define LEXER_H

void print_lexer(void *content);
char *skip_spaces(char *s);
int check_qutes(char *s);
int is_metachar(char c);
int is_space(char c);

#endif
