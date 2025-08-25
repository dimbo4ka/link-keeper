# link-keeper
CLI-менеджер закладок для хранения и организации веб-ссылок. Поддерживает теги, поиск и фильтрацию, хранение данных в SQLite (есть возможность реализовать кастомное хранение).

## Сборка и запуск
```bash
git clone https://github.com/dimbo4ka/link-keeper.git
cd link-keeper
cmake -S . -B build
cmake --build build
cd build/src
```


## Использование

| Флаг / Аргумент      | Описание                                   | Пример использования                          |
|-----------------------|--------------------------------------------|-----------------------------------------------|
| `-a`, `--add`        | Добавить закладку                         | `link-keeper --add --title telegram --url=tg.org --tags social_media p2p` |
| `-r`, `--rm`         | Удалить закладку по названию               | `link-keeper --rm telegram`                   |
| `-g`, `--get`        | Получить закладку по названию              | `link-keeper --get telegram`                  |
| `-s`, `--search`     | Поиск закладок по тегам                    | `link-keeper --search p2p`                    |
| `--all`              | Показать все закладки                      | `link-keeper --all`                           |
| `-t`, `--tags`       | Теги закладки (можно несколько значений)   | `--tags social p2p bitcoin`                   |
| `--title`            | Название закладки (позиционный аргумент)   | `--title=telegram`                            |
| `--url`              | URL закладки                               | `--url=tg.org`                                |
| `-h`, `--help`       | Вывод справки                              | `link-keeper -h`                              |