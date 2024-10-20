#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include <vector>

class TaskQueue
{
 public:
    void AddTask(std::function<void()>&& task)
    {
        std::lock_guard lock(mutex_);
        tasks_.emplace_back(std::move(task));
    }

    bool IsEmpty()
    {
        std::lock_guard lock(mutex_);
        return tasks_.empty();
    }

    void RunTask()
    {
        std::lock_guard lock(mutex_);
        for (auto task : tasks_)
        {
            task();
        }
        tasks_.clear();
    }

 private:
    std::vector<std::function<void()>> tasks_;
    std::mutex mutex_;
};

class ThreadPool
{
 public:
    ThreadPool(int task)
    {
        for (int i = 0; i < task; ++i)
        {
            pool_.emplace_back([this]() {
                auto& tasks = thread_tasks_[std::this_thread::get_id()];
                while (true)
                {
                    if (!tasks.IsEmpty())
                    {
                        tasks.RunTask();
                        std::cout << "thread " << std::this_thread::get_id() << " finish task" << std::endl;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "thread " << std::this_thread::get_id() << " sleep 1s" << std::endl;
                }
            });
        }
    }

    ~ThreadPool()
    {
        for (auto& t : pool_)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    }

    void AddTask(std::function<void()>&& task)
    {
        int index = std::rand() % pool_.size();
        thread_tasks_[pool_[index].get_id()].AddTask(std::move(task));
    }

 private:
    std::vector<std::thread> pool_;
    std::unordered_map<std::thread::id, TaskQueue> thread_tasks_;
};

int main()
{
    ThreadPool pool(3);
    pool.AddTask([]() { std::cout << "task 1" << std::endl; });
    pool.AddTask([]() { std::cout << "task 2" << std::endl; });
    pool.AddTask([]() { std::cout << "task 3" << std::endl; });
    pool.AddTask([]() {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "task 4" << std::endl;
    });
    return 0;
}
