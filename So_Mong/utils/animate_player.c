#include "../so_long.h"

void collectible_function(char **filenames)
{
    filenames[0] = "assets/coll/1.xpm";
    filenames[1] = "assets/coll/2.xpm";
    filenames[2] = "assets/coll/3.xpm";
    filenames[3] = "assets/coll/4.xpm";
    filenames[4] = "assets/coll/5.xpm";
    filenames[5] = "assets/coll/6.xpm";
}

int standar_animation(t_data *data)
{
    data->frame_counter++;
    draw_game(data);
    return (0);
}


void anime_right(t_data *data)
{
   static int j;

   if (j <= 0)
        j = 106;
    j -= 5;
    if (data->frame_counter % 2 == 0)
    {
        IMG(data->mlx, data->win, data->right, (data->player_x * TILE_WID + 40) - j, data->player_y * TILE_HEI + 40);
    }
    else
    {
        IMG(data->mlx, data->win, data->right1, (data->player_x * TILE_WID + 40) - j, data->player_y * TILE_HEI + 40);
    }
    if (j <= 0)
    {
        data->press = 0;

    }
}

void anime_left(t_data *data)
{
   static int i;

   if (i <= 0)
        i = 106;
    i -= 5;
    if (data->frame_counter % 2 == 0)
    {
        IMG(data->mlx, data->win, data->left, (data->player_x * TILE_WID + 40) + i, data->player_y * TILE_HEI + 40);
    }
    else
    {
        IMG(data->mlx, data->win, data->left1, (data->player_x * TILE_WID + 40) + i, data->player_y * TILE_HEI + 40);
    }
    if (i <= 0)
    {
        data->press = 0;
        i = 0;
    }
}

void anime_up(t_data *data)
{
   static int i;

   if (i <= 0)
        i = 106;
    i -= 5;
    if (data->frame_counter % 2 == 0)
    {
        IMG(data->mlx, data->win, data->up, (data->player_x * TILE_WID + 40), (data->player_y * TILE_HEI + 40) + i);
    }
    else
    {
        IMG(data->mlx, data->win, data->up1, (data->player_x * TILE_WID + 40), (data->player_y * TILE_HEI + 40) + i);
    }
    if (i <= 0)
    {
        data->press = 0;
        i = 0;
    }
}

void anime_down(t_data *data)
{
   static int i;

   if (i <= 0)
        i = 106;
    i -= 5;
    if (data->frame_counter % 2 == 0)
    {
        IMG(data->mlx, data->win, data->down, (data->player_x * TILE_WID + 40), (data->player_y * TILE_HEI + 40) - i);
    }
    else
    {
        IMG(data->mlx, data->win, data->down1, (data->player_x * TILE_WID + 40), (data->player_y * TILE_HEI + 40) - i);
    }
    if (i <= 0)
    {
        data->press = 0;
        i = 0;
    }
}

void render_anime(t_data *data, int key)
{
    if (key == D)
        anime_right(data);
    else if (key == A)
        anime_left(data);
}
