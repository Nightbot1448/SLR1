## SLR(1) парсер

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
* `-p(--print_table)` - печать таблицы

Пример:
```bash
    ./SLR_parser --print_table --input="n+-n"
```

Запуск тестов(если установлен `gtest`)
```
    ./run_tests
```