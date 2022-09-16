//
// Created by Artem Novikov on 01.09.2022.
//

#ifndef ANTS__TIMER_H_
#define ANTS__TIMER_H_

#include "chrono"

class Timer {
 public:
  Timer() : initial_time_(std::chrono::high_resolution_clock::now()) {}

  void Update() {
    auto current_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> time_from_start = current_time - initial_time_;
    float now = time_from_start.count() * 1e-3f;
    delta_time_ = std::clamp(now - elapsed_time_, 0.f, 0.2f);
    elapsed_time_ += delta_time_;
    std::cout << delta_time_ * 1000.f << '\n';
  }

  float GetDeltaTime() const { return delta_time_; }

  float GetElapsedTime() const { return elapsed_time_; }

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> initial_time_;
  float elapsed_time_;
  float delta_time_;
};

#endif //ANTS__TIMER_H_
