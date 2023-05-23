#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits.h>
#include <stddef.h>

/**
 * struct path_s - linked list structure for PATH variable
 * @directory: directory to lookup
 * @next: pointer to the next node
 */

typedef struct path_s
{
	char *directory;
	struct path_s *next;
} linked_t;


int _putchar(char c);

int handles_exit(char *line, char *newline, char **arr, int command_count);
int handles_cd(char **arr, char **env);
int handles_env(char **env);
int builtin_checker(char **arr, char **env, char *line, char *newline,
		int cmd_number);

linked_t *creates_linked(char *trs);
linked_t *add_nodes_list(char *trs, linked_t *lists);
char *gets_env(const char *name, char **env);
char *handles_path(char *trs, char **env);

void handles_error(char **argv, char **arr, char *line, char *nonline,
		int cmd_count);

int exec_command(char **arr, char **env, char **argv, char *line,
		char *nonline, int command_count);

char *_upstr(char *trs);
char *conc(char *concat, char *s1, char *s2);
int _strlen(char *s);
char *str_conc(char *s1, char *s2);
int str_cmp(char *s1, char *s2);

char *reallocate(char *pointer);
void freelist(linked_t *start);
void freetokens(char **t_array);
void all_free(char *line, char *newline, char **t_array);

void command_prompt(void);

char **give_token(char *line);

void handles_ctrlc(int signal_number);
int handles_ctrld(char *input);

int tens_holder(int x, char *y);
int to_integer(char *y);
char *prints_integer(int value);

#endif
