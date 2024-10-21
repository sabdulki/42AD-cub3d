#include "../cub.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// Размеры окна
int win_width = 1024;
int win_height = 512;

// Размер блока карты для миникарты
#define mapS 64 // исходный размер блока
#define miniMapScale 0.2 // коэффициент масштабирования миникарты

// Структура для хранения данных MiniLibX
typedef struct  s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int     bpp;
    int     size_line;
    int     endian;
}               t_data;

// Структура игрока
typedef struct s_player
{
    float px;
    float py;
    float pdx;
    float pdy;
    float pa;
}   t_player;


// Структура игры, объединяющая все данные
typedef struct s_game
{
    t_data data;
    t_player player;
    t_cub *cube;
}   t_game;

// Конвертация градусов в радианы
float degToRad(float a)
{
    return (a * M_PI / 180.0);
}

// Функция для фиксации угла в диапазоне от 0 до 360
float FixAng(float a)
{
    if (a > 359)
        a -= 360;
    if (a < 0)
        a += 360;
    return a;
}

// Функция для установки пикселя в изображении
void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= win_width || y < 0 || y >= win_height)
        return;
    dst = game->data.img_data + (y * game->data.size_line + x * (game->data.bpp / 8));
    *(unsigned int*)dst = color;
}

// Функция для рисования прямоугольника
void draw_rectangle(t_game *game, float x, float y, float width, float height, int color)
{
    int i;
    int j;
    int xi = (int)x;
    int yi = (int)y;
    int wi = (int)(x + width) - xi;
    int hi = (int)(y + height) - yi;

    for (j = 0; j < hi; j++)
    {
        for (i = 0; i < wi; i++)
        {
            my_mlx_pixel_put(game, xi + i, yi + j, color);
        }
    }
}

// Функция для рисования линии (алгоритм Брезенхема)
void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put(game, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// Функция для рисования карты
void drawMap2D(t_game *game)
{
    int x, y;
    float xo, yo;
    int color;
    t_map *map_struct = game->cube->map;
    char **map = map_struct->map;
    int mapX = map_struct->width;
    int mapY = map_struct->height;
    float blockSize = mapS * miniMapScale;

    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map[y][x] == '1')
                color = 0xFFFFFF; // белый цвет для стен
            else
                color = 0x000000; // черный цвет для пустого пространства
            xo = x * blockSize;
            yo = y * blockSize;
            draw_rectangle(game, xo, yo, blockSize, blockSize, color);
        }
    }
}

// Функция для рисования игрока на миникарте
void drawPlayer2D(t_game *game)
{
    int color = 0xFFFF00; // Желтый цвет
    float px = game->player.px * miniMapScale;
    float py = game->player.py * miniMapScale;
    int player_size = 8; // Увеличенный размер игрока
    int direction_length = 1; // Длина направления в единицах карты
    float line_length = direction_length * mapS * miniMapScale; // Длина линии в пикселях
    float angle_offset = 15.0; // Угол смещения для конуса (в градусах)

    // Рисуем игрока как квадрат большего размера
    draw_rectangle(game, px - player_size / 2, py - player_size / 2, player_size, player_size, color);

    // Вычисляем углы для конуса
    float pa_left = degToRad(FixAng(game->player.pa + angle_offset));
    float pa_right = degToRad(FixAng(game->player.pa - angle_offset));

    // Вычисляем конечные точки для линий конуса
    float left_dx = cos(pa_left) * line_length;
    float left_dy = -sin(pa_left) * line_length;

    float right_dx = cos(pa_right) * line_length;
    float right_dy = -sin(pa_right) * line_length;

    // Рисуем левую линию конуса
    draw_line(game, px, py, px + left_dx, py + left_dy, color);
    // Рисуем правую линию конуса
    draw_line(game, px, py, px + right_dx, py + right_dy, color);
}

// Функция для рисования лучей и стен (можно оставить без изменений)
void drawRays2D(t_game *game)
{
    int r, mx, my, dof;
    float rx, ry, ra, xo, yo;
    float disV, disH, disT;
    float Tan;

    // Рисуем потолок
    draw_rectangle(game, 0, 0, win_width, win_height / 2, 0x00FFFF); // цвет cyan
    // Рисуем пол
    draw_rectangle(game, 0, win_height / 2, win_width, win_height / 2, 0x0000FF); // синий цвет

    ra = FixAng(game->player.pa + 30); // угол луча, стартовый, на 30 градусов больше направления игрока

    for (r = 0; r < 60; r++)
    {
        // --- Вертикальные линии ---
        dof = 0;
        disV = 100000;
        Tan = tan(degToRad(ra));
        if (cos(degToRad(ra)) > 0.001)
        {
            rx = (((int)game->player.px >> 6) << 6) + 64;
            ry = (game->player.px - rx) * Tan + game->player.py;
            xo = 64;
            yo = -xo * Tan;
        }
        else if (cos(degToRad(ra)) < -0.001)
        {
            rx = (((int)game->player.px >> 6) << 6) - 0.0001;
            ry = (game->player.px - rx) * Tan + game->player.py;
            xo = -64;
            yo = -xo * Tan;
        }
        else
        {
            rx = game->player.px;
            ry = game->player.py;
            dof = 8;
        }

        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            if (mx >= 0 && mx < game->cube->map->width && my >= 0 && my < game->cube->map->height && game->cube->map->map[my][mx] == '1')
            {
                dof = 8;
                disV = cos(degToRad(ra)) * (rx - game->player.px) - sin(degToRad(ra)) * (ry - game->player.py);
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        // --- Горизонтальные линии ---
        dof = 0;
        disH = 100000;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ra)) > 0.001)
        {
            ry = (((int)game->player.py >> 6) << 6) - 0.0001;
            rx = (game->player.py - ry) * Tan + game->player.px;
            yo = -64;
            xo = -yo * Tan;
        }
        else if (sin(degToRad(ra)) < -0.001)
        {
            ry = (((int)game->player.py >> 6) << 6) + 64;
            rx = (game->player.py - ry) * Tan + game->player.px;
            yo = 64;
            xo = -yo * Tan;
        }
        else
        {
            rx = game->player.px;
            ry = game->player.py;
            dof = 8;
        }

        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            if (mx >= 0 && mx < game->cube->map->width && my >= 0 && my < game->cube->map->height && game->cube->map->map[my][mx] == '1')
            {
                dof = 8;
                disH = cos(degToRad(ra)) * (rx - game->player.px) - sin(degToRad(ra)) * (ry - game->player.py);
            }
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        int color;
        if (disV < disH)
        {
            disT = disV;
            color = 0x009900; // темно-зеленый цвет
        }
        else
        {
            disT = disH;
            color = 0x00CC00; // светло-зеленый цвет
        }

        // Исправляем искажения (fish-eye)
        float ca = FixAng(game->player.pa - ra);
        disT = disT * cos(degToRad(ca));

        // Вычисляем высоту линии и ее положение
        int lineH = (mapS * win_height) / (disT);
        if (lineH > win_height)
            lineH = win_height;
        int lineOff = (win_height / 2) - (lineH >> 1);

        // Рисуем вертикальную стену
        draw_rectangle(game, r * (win_width / 60), lineOff, (win_width / 60) + 1, lineH, color);

        ra = FixAng(ra - 1); // уменьшаем угол луча на 1 градус
    }
}

// Функция для отрисовки сцены
void draw(t_game *game)
{
    drawRays2D(game);       // Сначала рисуем лучи и стены
    drawMap2D(game);        // Затем рисуем миникарту поверх
    drawPlayer2D(game);     // И игрока на миникарте
}

int keyPressed(int keycode, t_game *game)
{
    float moveSpeed = 5.0;

    if (keycode == 0) // клавиша 'A'
    {
        game->player.pa += 5;
        game->player.pa = FixAng(game->player.pa);
        game->player.pdx = cos(degToRad(game->player.pa));
        game->player.pdy = -sin(degToRad(game->player.pa));
    }
    if (keycode == 2) // клавиша 'D'
    {
        game->player.pa -= 5;
        game->player.pa = FixAng(game->player.pa);
        game->player.pdx = cos(degToRad(game->player.pa));
        game->player.pdy = -sin(degToRad(game->player.pa));
    }
    if (keycode == 13) // клавиша 'W'
    {
        float new_px = game->player.px + game->player.pdx * moveSpeed;
        float new_py = game->player.py + game->player.pdy * moveSpeed;

        int mapX = (int)(new_px) / mapS;
        int mapY = (int)(new_py) / mapS;

        if (game->cube->map->map[mapY][mapX] != '1')
        {
            game->player.px = new_px;
            game->player.py = new_py;
        }
    }
    if (keycode == 1) // клавиша 'S'
    {
        float new_px = game->player.px - game->player.pdx * moveSpeed;
        float new_py = game->player.py - game->player.pdy * moveSpeed;

        int mapX = (int)(new_px) / mapS;
        int mapY = (int)(new_py) / mapS;

        if (game->cube->map->map[mapY][mapX] != '1')
        {
            game->player.px = new_px;
            game->player.py = new_py;
        }
    }
    // Перерисовываем окно
    mlx_clear_window(game->data.mlx_ptr, game->data.win_ptr);
    mlx_destroy_image(game->data.mlx_ptr, game->data.img_ptr);
    game->data.img_ptr = mlx_new_image(game->data.mlx_ptr, win_width, win_height);
    game->data.img_data = mlx_get_data_addr(game->data.img_ptr, &game->data.bpp, &game->data.size_line, &game->data.endian);
    draw(game);
    mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr, game->data.img_ptr, 0, 0);
    return (0);
}

// Функция для инициализации игрока на основе карты
void initialize_player(t_game *game)
{
    t_map *map_struct = game->cube->map;
    char **map = map_struct->map;
    int mapX = map_struct->width;
    int mapY = map_struct->height;
    int x, y;

    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
            {
                // Устанавливаем позицию игрока в центр ячейки
                game->player.px = x * mapS + mapS / 2;
                game->player.py = y * mapS + mapS / 2;

                // Устанавливаем направление игрока
                if (map[y][x] == 'N')
                    game->player.pa = 90;
                else if (map[y][x] == 'S')
                    game->player.pa = 270;
                else if (map[y][x] == 'E')
                    game->player.pa = 0;
                else if (map[y][x] == 'W')
                    game->player.pa = 180;

                game->player.pdx = cos(degToRad(game->player.pa));
                game->player.pdy = -sin(degToRad(game->player.pa));

                // Заменяем символ на '0' (пустое пространство)
                map[y][x] = '0';

                return; // Предполагаем, что на карте только одна позиция игрока
            }
        }
    }

    // Если позиция игрока не найдена, устанавливаем по умолчанию
    game->player.px = mapS / 2;
    game->player.py = mapS / 2;
    game->player.pa = 90;
    game->player.pdx = cos(degToRad(game->player.pa));
    game->player.pdy = -sin(degToRad(game->player.pa));
}

// Функция raycast
int raycast(t_cub *cube)
{
    t_game game;

    // Инициализация структуры игры
    game.cube = cube;

    // Инициализация MiniLibX
    game.data.mlx_ptr = mlx_init();
    game.data.win_ptr = mlx_new_window(game.data.mlx_ptr, win_width, win_height, "Cub3D");

    // Инициализация изображения
    game.data.img_ptr = mlx_new_image(game.data.mlx_ptr, win_width, win_height);
    game.data.img_data = mlx_get_data_addr(game.data.img_ptr, &game.data.bpp, &game.data.size_line, &game.data.endian);

    // Инициализация игрока на основе карты
    initialize_player(&game);

    // Отрисовка начальной сцены
    draw(&game);
    mlx_put_image_to_window(game.data.mlx_ptr, game.data.win_ptr, game.data.img_ptr, 0, 0);

    // Установка хуков на события
    mlx_hook(game.data.win_ptr, 2, 1L<<0, keyPressed, &game); // обработка нажатия клавиш
    mlx_loop(game.data.mlx_ptr);
    return (0);
}