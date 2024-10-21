#include "../cub.h"
#include <stdlib.h>

void draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
        }
    }
}

void drawMap2D(void *mlx_ptr, void *win_ptr, int mapX, int mapY, char **map, int mapS)
{
    int x, y, xo, yo;
    int color;

    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map[y][x] == 1)
            {
                color = 0xFFFFFF; // белый цвет
            }
            else
            {
                color = 0x000000; // черный цвет
            }

            xo = x * mapS;
            yo = y * mapS;

            draw_square(mlx_ptr, win_ptr, xo + 1, yo + 1, mapS - 2, color);
        }
    }
}