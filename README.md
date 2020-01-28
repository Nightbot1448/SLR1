## SLR(1) парсер(GNU only)

Парсер работает для грамматик, в которых нет ε-правил. Стартовым нетерминалом должен являться `S`.

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
* `-f(--file)` - файл, содержащий строку(строки)*
* `-p(--print_table)` - печать таблицы
* `-t(--print_tree)` - печать дерева

Пример:
```bash
./SLR_parser --print_table --print_tree --input="n+-n"
```

Запуск тестов(если установлен `gtest`)
```
./run_tests
```

\* - Пример файла.
```
n+n
-n+n
n+-n
n*n/n+--n
n+nn
n-a
```