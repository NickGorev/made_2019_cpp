## Домашнее задание номер 8

### Задание

Написать свой контейнер Vector аналогичный std::vector, аллокатор и итератор произвольного доступа для него. Из поддерживаемых методов достаточно operator[], push_back, pop_back, empty, size, clear, begin, end, rbegin, rend, resize, reserve.

Чтобы тесты проходили, классы должны иметь такие имена:

```c++
template <class T>
class Allocator
{
};

template <class T>
class Iterator
{
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;

private:
    Alloc alloc_;
};
```

Интерфейс аллокатора и итератора смотрите в документации.

### Решение

Реализация аллокатора находится в файле `allocator.hpp`, итератора - в файле `iterator.hpp`, вектора - в файле `vector.hpp`.

Для тестирования используется версия тестового фреймворка [Catch2](https://github.com/catchorg/Catch2) в виде одного заголовочного файла `../catch/catch.hpp`. Сами тесты находятся в файле `main.cpp`.

Сборка решения

```
make all
```

Запуск тестов

```
make test
```

