#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int a = 1;
std::string v = "";

int main() {
  std::atomic<bool> ready = false;

  std::thread t1([&ready]() {
    ready.notify_all();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ready = true;
  });

  std::thread t2([&ready]() {
    while (!ready) {
      std::cout << "Waiting for ready" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Ready" << std::endl;
  });

  std::thread t3([&ready]() {
    ready.wait(false);
    std::cout << "Ready3" << std::endl;
  });
  std::thread t4([&ready]() {
    ready.wait(false);
    std::cout << "Ready4" << std::endl;
  });
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  return 0;
}
