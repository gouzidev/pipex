#ifndef PIPEX
#define PIPEX

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

typedef struct s_pipex
{
    int **pipes;
    int n_cmds;
    int n_pips;
    pid_t *pids;
    int infile;
    int outfile;
    int infile_status;
    int outfile_status;
    char **cmds;
    char **env;
    char *env_path;
    char *cmd_path;
    char **cmd_args;
    int status;

}  t_pipex;

/* prase.c */
char **parse_commands(int  ac, char *av[]);

/* helper1.c */
void clean_up(t_pipex *pipex);
void setup(t_pipex *pipex, int  ac, char   *av[], char *env[]);
void freee(t_pipex *pipex);
void handle_status(t_pipex *pipex, int  ac, char *av[]);

/* str.c */
int ft_strlen(char *str);
char *ft_strdup(char *str);

/* pipe.c */
int** init_pipes(int n_cmds);
void close_allthe_pipes(int **pipes);
void close_unused_pipes(int **pipes, int process_index, int n_pips);

void exit_print(char *msg);
static int	len(char const *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
static char	**free_all(char **res, int w);
static int	count_words(char const *s1, char c);
static char	**handle_null_malloc(char const *s, char c);
char	**ft_split(char const *s, char c);


int ft_strncmp  (const char *s1, const char *s2, size_t n);


typedef struct s_node {
    struct s_node *next;
    struct s_node *prev;
    char *cmd;
    int fd[2];
}   t_node;


/* linked_list.c */
t_node *new (char   *cmd);
void	push(t_node **head, t_node *new);
void	pop(t_node **head);
int	size(t_node *node);
t_node	*duplicate(t_node *node);
t_node	*before_last(t_node *head);
t_node	*last(t_node *head);
int	exists(t_node *head, t_node *node);
void	clear(t_node **head);


int is_path(char	*cmd);
char *get_env_path(char	*env[]);
char	*make_path(char	*path, char	*cmd);
char *find_cmd_path(char	*env_path, char *cmd);

#endif
