#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096


extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *information, char **argv);
int find_builtin(info_t *information);
void find_cmd(info_t *information);
void fork_cmd(info_t *information);

int is_chain(info_t *information, char *buf, size_t *p);
void check_chain(info_t *information, char *buf, size_t *p, size_t i, size_t
		len);
int replace_alias(info_t *information);
int replace_vars(info_t *information);
int replace_string(char **old, char *new);

char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

char *_strcpy(char *destination, char *source);
char *_strdup(const char *source_string);
void _puts(char *str);
int _putchar(char c);

int _strlen(char *s);
int _strcmp(char *string1, char *string2);
char *starts_with(const char *home_string, const char *seeker);
char *_strcat(char *destination, char *source);

int bfree(void **mem);

int is_cmd(info_t *information, char *route);
char *dup_chars(char *str, int first, int last);
char *find_path(info_t *information, char *str, char *command);

char *_memset(char *s, char b, unsigned int j);
void ffree(char **pda);
void *_realloc(void *pointer, unsigned int old, unsigned int new);

char *_strncpy(char *destination, char *source, int f);
char *_strncat(char *str_one, char *str_two, int f);
char *_strchr(char *s, char v);

int interactive(info_t *information);
int is_delim(char ch, char *delimiter);
int _isalpha(int ch);
int _atoi(char *st);

int _myhistory(info_t *information);
int unset_alias(info_t *information, char *string);
int set_alias(info_t *information, char *string);
int print_alias(list_t *node);
int _myalias(info_t *information);

int _myexit(info_t *information);
int _mycd(info_t *information);
int _myhelp(info_t *information);

int _myenv(info_t *information);
char *_getenv(info_t *information, const char *call);
int _mysetenv(info_t *information);
int _myunsetenv(info_t *information);
int populate_env_list(info_t *information);

void _eputs(char *st);
int _eputchar(char ch);
int _putfd(char ch, int fd);
int _putsfd(char *st, int fd);

int _erratoi(char *st);
void print_error(info_t *information,  char *str);
int print_d(int inputs, int fd);
char *convert_number(long int numb, int baze, int flag);
void remove_comments(char *buff);

ssize_t input_buf(info_t *information, char **buf, size_t *len);
ssize_t get_input(info_t *information);
ssize_t read_buf(info_t *information, char *buf, size_t *j);
int _getline(info_t *information, char **ptr, size_t *leng);
void sigintHandler(__attribute__((unused))int sig_num);

char **get_environ(info_t *information);
int _unsetenv(info_t *information, char *variab);
int _setenv(info_t *information, char *variab, char *val);

void clear_info(info_t *information);
void set_info(info_t *information, char **vector);
void free_info(info_t *information, int alls);

char *get_history_file(info_t *information);
int write_history(info_t *information);
int read_history(info_t *information);
int build_history_list(info_t *information, char *buf, int linecount);
int renumber_history(info_t *information);

list_t *add_node(list_t **head, const char *str, int numb);
list_t *add_node_end(list_t **head, const char *str, int numb);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

size_t list_len(const list_t *head);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *head);
list_t *node_starts_with(list_t *node, char *prefix, char ch);
ssize_t get_node_index(list_t *head, list_t *node);

#endif
