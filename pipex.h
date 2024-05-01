/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:30 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/27 22:20:48 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_node
{
	struct s_node	*next;
	void			*data;
}					t_node;

typedef struct s_pipex
{
	int				*pids;
	int				**pipes;
	int				n_cmds;
	int				n_pips;
	int				infile_fd;
	int				outfile_fd;
	char			*outfile;
	char			*infile;
	char			**cmds;
	char			**env;
	int				status;
}					t_pipex;

/* gnl */
char				*get_next_line(int fd, t_node **gc);
char				*ft_strchr(char *s, int c);
char				*ft_strjoin_gnl(char *left_str, char *buff, t_node **gc);
char				*ft_get_line(char *left_str, t_node **gc);
char				*get_rest(char *left_str, t_node **gc);

/* family.c */
void				child(t_pipex *pipex, int i, t_node **gc);
void				parent(t_pipex *pipex, t_node **gc);

/* split.c */
int					count_words(char const *s1, char *sep);
char				**handle_null_malloc(char const *s, char *sep, t_node **gc);
char				**ft_split(char const *s, char *sep, t_node **gc);
int					is_sep(char c, char *sep);

/* helper.c */
void				check_infile(t_pipex *pipex, t_node **gc);
void				check_outfile(t_pipex *pipex, t_node **gc);
void				setup(t_pipex *pipex, t_node **gc, int ac, char *av[]);
void				read_hd(t_pipex *pipex, t_node **gc, char *av[]);
void				ft_close(int fd, t_node **gc);
void				close_here_doc_fd(t_pipex *pipex, t_node **gc);
void				perror_clear_exit(char *str, t_node **gc, int exit_code);
/* pipex.c */
int					main(int ac, char *av[], char *env[]);
char				**parse_commands(t_pipex *pipex, t_node **gc, int ac,
						char *av[]);
void				close_unused_files(int i, t_pipex *pipex, t_node **gc);
/* str.c */
int					ft_strcmp(const char *s1, const char *s2);
int					len(char *str);
char				*ft_strdup(char *str, t_node **gc);
char				*ft_strjoin(char *s1, char *s2, t_node **gc);
char				*ft_substr(char const *s, unsigned int start, size_t len,
						t_node **gc);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/* pipe.c */
int					**init_pipes(t_node **gc, int n_cmds);
void				close_allthe_pipes(t_pipex *pipex, int **pipes,
						t_node **gc);
void				close_unused_pipes(t_pipex *pipex, int process_index,
						t_node **gc);

char				**handle_cmd_str(t_pipex *pipex, int i, t_node **gc,
						char *cmd);
void				handle_no_path(t_pipex *pipex, int i, t_node **gc,
						char **cmd_args);
void				handle_cmd_path(t_pipex *pipex, int i, t_node **gc,
						char **cmd_args);
void				handle_fail(t_pipex *pipex, int i, t_node **gc,
						char **cmd_args);

/* gc.c */
void				*gc_malloc(t_node **gc, size_t size);
void				gc_push(t_node **gc, void *data);
t_node				*gc_init(void);
void				gc_clear(t_node **gc);

/* path.c */
char				*get_env_path(char *env[]);
char				*find_cmd_path(char *env_path, char *cmd, t_node **gc);

/* exec.c */
void				handle_dup(t_pipex *pipex, int i, t_node **gc);
void				execute_cmd(t_pipex *pipex, int i, t_node **gc);
int					ft_dup2(int oldfd, int newfd, t_node **gc);

/* */
void				handle_here_doc(int ac, char *av[], char *env[],
						t_node **gc);
void				setup_hd(t_pipex *pipex, t_node **gc, int ac, char *av[]);
void				check_n_setup(t_pipex *pipex, t_node **gc, int ac,
						char *av[]);

void				ft_putstr(char *s, int *i);

#endif