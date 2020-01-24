## SLR(1) парсер(GNU only)

Сборка:
```bash
    mkdir build
    cd build
    cmake ..
    make -j4 -l4
```

Запуск:
```bash
    ./SLR_parser
```

Ключи:
* `-i(--input)` - проверяемая строка
* `-f(--file)` - файл, содержащий строку(строки)
* `-p(--print_table)` - печать таблицы
* `-t(--print_tree)` - печать дерева

Пример:
```bash
    ./SLR_parser --print_table --input="n+-n"
```

Запуск тестов(если установлен `gtest`)
```
    ./run_tests
```