## Домашнее задание номер 2

### Задание
Написать библиотеку-парсер строк состоящих из следующих токенов:

- строка
- число

Число состоит из символов от 0 до 9, строка - все остальные символы. Токены разделены пробелами, символами табуляции и первода строки.

Пользователь библиотеки должен иметь возможность зарегистрировать колбек-функцию вызываемую каждый раз, когда найден токен, функция получает токен. Должно быть возможно зарегистрировать свой обработчик под каждый тип токена. Также должны быть колбеки вызываемые перед началом парсинга и по его окончанию.

### Решение
Реализация находится в файлах `parser.h` и `parser.cpp`.

Для тестирования используется версия тестового фреймворка [Catch2](https://github.com/catchorg/Catch2) в виде одного заголовочного файла `../catch/catch.hpp`. Сами тесты находятся в файле `main.cpp`.

Компиляция библиотеки:

```
make libparser.a
```
Создается библиотечный файл `libparser.a`.

Сборка решения вместе с тестами:
```
make all
```

Запуск тестов:

```
make test
```
