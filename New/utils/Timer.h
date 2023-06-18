//
// Created by Artem Novikov on 01.09.2022.
//

#ifndef ANTS__TIMER_H_
#define ANTS__TIMER_H_

#include <chrono>

class Timer {
 public:
  Timer() : last_tick_(std::chrono::high_resolution_clock::now()) {}

  void Update() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> dt = std::chrono::high_resolution_clock::now() - last_tick_;
    last_tick_ = now;

    auto delta_time = dt.count() * 1e-3f;
    delta_time_ = delta_time * (delta_time <= 0.2f) + 0.2f * (delta_time > 0.2f); // std::clamp(delta_time, 0.f, 0.2f);
    elapsed_time_ += delta_time_;
//    std::cout << delta_time_ * 1000.f << '\n';
  }

  [[nodiscard]] float GetDeltaTime() const { return delta_time_; }

  [[nodiscard]] float GetElapsedTime() const { return elapsed_time_; }

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_tick_;
  float elapsed_time_;
  float delta_time_;
};

#endif //ANTS__TIMER_H_
