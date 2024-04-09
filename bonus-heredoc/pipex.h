#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
# include <stdarg.h>

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
    int *pids;
    int **pipes;
    int n_cmds;
    int n_pips;
    int infile;
    int outfile;
    char **cmds;
    char **env;
    int status;

}  t_pipex;


/* gnl */
char	*get_next_line(int fd, t_node **gc);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin_gnl(char *left_str, char *buff, t_node **gc);
char	*ft_get_line(char *left_str, t_node **gc);
char	*get_rest(char *left_str, t_node **gc);


/* split.c */
int	len(char const *s1);
int	count_words(char const *s1, char c);
char	**handle_null_malloc(char const *s, char c, t_node **gc);
char	**ft_split(char const *s, char c, t_node **gc);

/* helper.c */
void setup(t_pipex *pipex, t_node **gc, int  ac, char   *av[], char *env[]);
void handle_infile(t_pipex *pipex);
void handle_status(t_pipex *pipex, int  ac, char *av[]);

/* pipex.c */
int main(int ac, char *av[], char *env[]);
char **parse_commands(t_pipex *pipex, t_node **gc, int  ac, char *av[]);
void parent(t_pipex *pipex, t_node **gc, int hd_flag);
void setup(t_pipex *pipex, t_node **gc, int  ac, char   *av[], char *env[]);

/* str.c */
int	ft_strcmp(const char *s1, const char *s2);
int ft_strlen(char *str);
char *ft_strdup(char *str, t_node **gc);
char	*ft_strjoin(char const *s1, char const *s2, t_node **gc);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_node **gc);
int ft_strncmp  (const char *s1, const char *s2, size_t n);

/* pipe.c */
int** init_pipes(t_pipex *pipex, t_node **gc, int n_cmds);
void close_allthe_pipes(int **pipes);
void close_unused_pipes(int **pipes, int process_index, int n_pips);

/* gc.c */
void *gc_malloc (t_node **gc, size_t size);
void gc_push(t_node **gc, void *data);
t_node* gc_init();
void gc_clear(t_node **gc);

/* path.c */
int is_path(char	*cmd);
char *get_env_path(char	*env[]);
char	*make_path(char	*path, char	*cmd, t_node **gc);
char *find_cmd_path(char	*env_path, char *cmd, t_node **gc);

/* exec.c */
void handle_cmd_path(t_pipex *pipex, int i, t_node **gc, char **cmd_args);
void handle_unset_path(t_pipex *pipex, int  i, t_node **gc);
void handle_unkown_cmd(t_pipex *pipex, char **cmd_args, int i, t_node **gc);
void handle_dup(t_pipex *pipex, int i);
void execute_cmd(t_pipex *pipex, int i, t_node **gc);

/* */
void handle_here_doc(int ac, char *av[], char *env[], t_node **gc);

int		ft_printf(const char *s, ...);
void	ft_putstr(char *s, int *i);

#endif
