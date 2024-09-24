# Привет, Руслан! 

Это README специально для тебя. 

Я постаралась структурировать файлы, чтобы тебе было удобно по ним пермещаться.

# CODE

В main.c я возвращаю t_cub *cub. Это стурктура, о которой мы говорили. 
В cub.h: 
```C
typedef struct s_cub
{
	struct s_sprite_list *list;
	char **map;
} t_cub;
```
Структура struct s_sprite_list *list уже возвращает готовый лист со спрайтами - именем и его значением. map пока что NULL.

Если тебе нужно распечатать этот лист, вызови функцию print_sprite_list(cub->list).
Я ее уже вызываю в парсинге. При компиляции и запуске программы тебе как раз покажется контент этого листа. 

# Some functions that could be useful for you

Это кастомный perror(), выводит сообщение во 2 fd уже с новой строкой.
```C 
void p_error(char *str);
```

Вывкдет имя спрайта как строку, а не как число. Принимает enum. 
```C
char *sprite_to_string(t_sprites sprite);
```

Улучшенный strcmp()
```C
int safe_strncmp(char *s1, char *s2);
```

зафришить cub при ошибке:
```C
void free_cub(t_cub *cub);

```

Удачи!