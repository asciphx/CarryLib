#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
struct Timer {
  template<typename F> void setTimeout(F func, uint32_t milliseconds);
  template<typename F> void setInterval(F func, uint32_t milliseconds);
  template<typename F> void setTimeoutSec(F func, uint32_t seconds);
  template<typename F> void setIntervalSec(F func, uint32_t seconds);
  void stop();
private: std::atomic<bool> alive{ true };
};
template<typename F> void Timer::setTimeout(F func, uint32_t milliseconds) {
  alive = true; std::thread t([=]() {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	if (!alive.load()) return; func();
	});
  t.detach();
}
template<typename F> void Timer::setInterval(F func, uint32_t milliseconds) {
  alive = true; std::thread t([=]() {
	while (alive.load()) {
	  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	  if (!alive.load()) return; func();
	}
	});
  t.detach();
}
template<typename F> void Timer::setTimeoutSec(F func, uint32_t seconds) {
  alive = true; std::thread t([=]() {
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
	if (!alive.load()) return; func();
	});
  t.detach();
}
template<typename F> void Timer::setIntervalSec(F func, uint32_t seconds) {
  alive = true; std::thread t([=]() {
	while (alive.load()) {
	  std::this_thread::sleep_for(std::chrono::seconds(seconds));
	  if (!alive.load()) return; func();
	}
	});
  t.detach();
}
void Timer::stop() { alive = false; }
int main() {
using namespace std;
  std::locale::global(std::locale("en_US.UTF8"));
  Timer t; int i = 0; bool run = true;
  t.setTimeout([&t, &run]() {
	cout << "经过6.18s" << endl;
	t.stop(); run = false;
	}, 6180);
  t.setInterval([&i]() {
	cout << "持续" << ++i << "秒" << endl;
	}, 1000);
  cout << "定时器开始!" << endl;
  while (run) this_thread::yield();
  return 0;
}
