#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <errno.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WID 1000
# define WINDOW_HEI 700
# define BUFFER_SIZE 10 
# define W 13
# define D 2
# define A 0
# define S 1
# define ESC 53
# define IMG mlx_put_image_to_window
# define WIN mlx_new_window

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_mlx
{
	char **map;
	void *mlx;
	void *win;
	int player_x;
	int player_y;
	int map_wid;
	int map_hei;
	int collectible;
	int moves;
}   t_data;

int		found_newline(t_list *list);
t_list	*find_lst_node(t_list *list);
char	*get_line(t_list *list);
void	copy_str(t_list *list, char *str);
int		len_to_newline(t_list *list);
void	polish_list(t_list **list);
char	*get_next_line(int fd);
void	dealloc(t_list **list, t_list *clean_node, char *buf);
void	create_list(t_list **list, int fd);
void	append(t_list **list, char *buf);
char 	**add_to_map(char **map, char *new_line);
int		window_init(t_data *data);
int 	key_press(int key, t_data *data);
void 	move_player(int dierection, t_data *data);
void 	exit_game(t_data *data);

#endif /* SO_LONG_H  */