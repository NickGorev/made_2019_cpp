#pragma once
#include <future>
#include <deque>
#include <vector>

struct ThreadPool {
    public:
        explicit ThreadPool(size_t poolSize = 1) : stop_flag(false) {
            // Создаем poolSize потоков и в каждом запускаем thread_task
            threads.reserve(poolSize);
            for (std::size_t i = 0; i < poolSize; i++) {
                threads.emplace_back([this]{thread_task();});
            }
        }


        // Новая задача добавляется в очередь,
        // при этом происходит оповещение спящих потоков
        // pass arguments by value
        template<class Func, class ... Args>
        auto exec(Func func,
                Args ... args) -> std::future<decltype(func(args...))> {
            // упаковываем задачу
            std::packaged_task<decltype(func(args...))()>
                task(std::bind(func, args...));

            auto future = task.get_future();

            // кладем задачу в очередь
            {
                std::unique_lock<std::mutex> lock(mtx_tasks);
                tasks.emplace_back(std::move(task));
            }
            // разбудим один из спящих потоков,
            // чтобы он выполнил задачу
            cond_var_tasks.notify_one();

            return future;
        }


        ~ThreadPool() {
            {
                std::unique_lock<std::mutex> lock(mtx_tasks);
                stop_flag = true;
            }
            cond_var_tasks.notify_all();
            for (auto& thread : threads) {
                thread.join();
            }
        }

    private:
        std::mutex mtx_tasks;
        std::condition_variable cond_var_tasks;

        std::deque<std::packaged_task<void()>> tasks;
        std::vector<std::thread> threads;

        bool stop_flag;

        void thread_task() {
            while (true) {
                std::packaged_task<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mtx_tasks);
                    // Если задачи нет, поток засыпает, ожидая оповещения
                    if (tasks.empty() && !stop_flag) {
                        cond_var_tasks.wait(lock,
                                [&]{return !tasks.empty() || stop_flag;});
                    }
                    // если выставлен флаг остановки, прерываем выполнение
                    if (stop_flag) return;
                    // иначе, извлекаем задачу из очереди
                    task = std::move(tasks.front());
                    tasks.pop_front();
                }
                // выполняем задачу
                task();
            }
        }
};
