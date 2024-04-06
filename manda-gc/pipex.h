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

typedef struct s_node {
    struct s_node *next;
    void *data;
}   t_node;

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
char **parse_commands(t_pipex *pipex, t_node **gc, int  ac, char *av[]);

/* helper1.c */
void clean_up(t_pipex *pipex);
void setup(t_pipex *pipex, t_node **gc, int  ac, char   *av[], char *env[]);
// void freee(t_pipex *pipex);
void handle_status(t_pipex *pipex, int  ac, char *av[]);
void ft_free_data(void **data);
void ft_free_node(t_node **node);

/* str.c */
int ft_strlen(char *str);
char *ft_strdup(char *str, t_node **gc);

/* pipe.c */
int** init_pipes(t_pipex *pipex, t_node **gc, int n_cmds);
void close_allthe_pipes(int **pipes);
void close_unused_pipes(int **pipes, int process_index, int n_pips);

void exit_print(char *msg);
static int	len(char const *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_node **gc);
// static char	**free_all(char **res, int w);
static int	count_words(char const *s1, char c);
static char	**handle_null_malloc(char const *s, char c, t_node **gc);
char	**ft_split(char const *s, char c, t_node **gc);


int ft_strncmp  (const char *s1, const char *s2, size_t n);



/* gc.c */

void *gc_malloc (t_node **gc, size_t size);
void gc_push(t_node **gc, void *data);
t_node* gc_init();
void gc_clear(t_node **gc);



int is_path(char	*cmd);
char *get_env_path(char	*env[]);
char	*make_path(char	*path, char	*cmd, t_node **gc);
char *find_cmd_path(char	*env_path, char *cmd, t_node **gc);

#endif
