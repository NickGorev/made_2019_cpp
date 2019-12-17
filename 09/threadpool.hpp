#pragma once
#include <future>
#include <deque>
#include <vector>

struct ThreadPool {
    public:
        explicit ThreadPool(size_t poolSize = 1) {
            // Создаем poolSize потоков и в каждом запускаем thread_task
            threads.reserve(poolSize);
            for (std::size_t i = 0; i < poolSize; i++) {
                threads.emplace_back(std::thread([this]{thread_task();}));
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
                tasks.clear();
                // чтобы остановить все потоки, кладем в очередь
                // пустые задачи
                for (size_t i = 0; i < threads.size(); i++) {
                    tasks.push_back({});
                }
            }
            // разбудим все потоки, чтобы они обработали
            // пустые задачи и завершились
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


        void thread_task() {
            while (true) {
                std::packaged_task<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mtx_tasks);
                    // Если задачи нет, поток засыпает, ожидая оповещения
                    if (tasks.empty()) {
                        cond_var_tasks.wait(lock, [&]{return !tasks.empty();});
                    }
                    // иначе, извлекаем задачу из очереди
                    task = std::move(tasks.front());
                    tasks.pop_front();
                }
                // если задача пустая, прерываем поток
                if (!task.valid())
                    return;
                // иначе, выполняем задачу
                task();
            }
        }
};
