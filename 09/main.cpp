#define CATCH_CONFIG_MAIN

#include <chrono>
#include <cmath>
#include "threadpool.hpp"
#include "../catch/catch.hpp"


std::string foo (const std::string& s) {
    return s;
}

struct A {
    int x;
    A(int x_) : x(x_) {};
};
int bar (const A& a) {
    return a.x;
}


TEST_CASE( "test ThreadPool" ) {
    SECTION( "test one thread" ){

        ThreadPool pool(1);

        auto task6 = pool.exec(bar, 6);
        auto task5 = pool.exec(bar, 5);
        std::string s;
        s = "!";
        auto task4 = pool.exec(foo, s);
        s = "world";
        auto task3 = pool.exec(foo, s);
        auto task2 = pool.exec(foo, ", ");
        auto task1 = pool.exec(foo, "Hello");

        REQUIRE(task1.get() == "Hello");
        REQUIRE(task2.get() == ", ");
        REQUIRE(task3.get() == "world");
        REQUIRE(task4.get() == "!");
        REQUIRE(task5.get() == 5);
        REQUIRE(task6.get() == 6);
    }

    SECTION( "test two threads" ){

        ThreadPool pool(2);

        auto task6 = pool.exec(bar, 6);
        auto task5 = pool.exec(bar, 5);
        std::string s;
        s = "!";
        auto task4 = pool.exec(foo, s);
        s = "world";
        auto task3 = pool.exec(foo, s);
        auto task2 = pool.exec(foo, ", ");
        auto task1 = pool.exec(foo, "Hello");

        REQUIRE(task1.get() == "Hello");
        REQUIRE(task2.get() == ", ");
        REQUIRE(task3.get() == "world");
        REQUIRE(task4.get() == "!");
        REQUIRE(task5.get() == 5);
        REQUIRE(task6.get() == 6);
    }

    SECTION( "test a lot of threads" ){
        ThreadPool pool(100);

        auto task1 = pool.exec(foo, "Hello, ");

        std::vector<std::future<int>> int_tasks(200);
        for(int i = 0; i < 200; i++) {
            int_tasks[i] = pool.exec(bar, i + 1);
        }

        auto task2 = pool.exec(foo, "world!");

        for(int i = 199; i >= 0; i--) {
            REQUIRE(int_tasks[i].get() == i + 1);
        }

        REQUIRE(task2.get() == "world!");
        REQUIRE(task1.get() == "Hello, ");

        for(int i = 0; i < 200; i++) {
            int_tasks[i] = pool.exec(bar, i + 1);
        }
        for(int i = 0; i < 50; i++) {
            REQUIRE(int_tasks[i].get() == i + 1);
        }
    }

    SECTION( "check multithreading" ){
        using namespace std::chrono_literals;
        auto wait = []{std::this_thread::sleep_for(1s); return;};

        // в один поток две задачи по 1 секунде будут выполняться
        // примерно две секунды
        ThreadPool pool1(1);
        auto task1 = pool1.exec(wait);
        auto task2 = pool1.exec(wait);

        auto start = std::chrono::high_resolution_clock::now();
        task1.get();
        task2.get();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed1 = end - start;
        REQUIRE(abs(elapsed1.count() - 2) < 0.01);

        // в два потока две задачи по 1 секунде на
        // многоядерной платформе должны выполниться
        // примерно за 1 секунду
        ThreadPool pool2(10);
        task1 = pool2.exec(wait);
        task2 = pool2.exec(wait);

        start = std::chrono::high_resolution_clock::now();
        task1.get();
        task2.get();
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed2 = end - start;
        REQUIRE(abs(elapsed2.count() - 1) < 0.01);
    }
}
