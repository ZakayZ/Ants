//
// Created by Artem Novikov on 27.05.2023.
//

#ifndef ANTS_NEW_UTILS_COOLDOWN_H_
#define ANTS_NEW_UTILS_COOLDOWN_H_

#include "DataTypes.h"

class Cooldown {
 public:
  Cooldown(Time reset) : reset_(reset), value_(0) {}

  void Update(Time dt) { value_ -= dt; }

  bool Ready() const {
    return value_ <= 0;
  }

  void Use() {
    value_ = reset_;
  }

 private:
  const Time reset_;

  Time value_;
};

#endif //ANTS_NEW_UTILS_COOLDOWN_H_
