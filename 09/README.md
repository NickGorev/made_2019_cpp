## Домашнее задание номер 9

### Задание

Реализовать пул потоков со следующим интерфейсом:

```c++
class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};
```

Использование пула потоков:

```c++
struct A {};

void foo(const A&) {}

ThreadPool pool(8);

auto task1 = pool.exec(foo, A());
task1.get();

auto task2 = pool.exec([]() { return 1; });
task2.get();
```

### Решение

Реализация пула потоков находится в файле `threadpool.hpp`.

Для тестирования используется версия тестового фреймворка [Catch2](https://github.com/catchorg/Catch2) в виде одного заголовочного файла `../catch/catch.hpp`. Сами тесты находятся в файле `main.cpp`.

Сборка решения

```
make all
```

Запуск тестов

```
make test
```

