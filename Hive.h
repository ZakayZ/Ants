//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__HIVE_H_
#define ANTS__HIVE_H_

#include "Vector.h"
#include "HiveStorage.h"

class Hive {
 public:
  Hive(const Vector2f& position, float initial_size = 3.f)
      : position_(position), storage_(), size_(initial_size) {}

  HiveStorage& GetStorage() { return storage_; }

  [[nodiscard]] const Vector2f& GetPosition() const { return position_; }

  [[nodiscard]] float GetSize() const { return size_; }

 private:
  Vector2f position_;
  HiveStorage storage_;
  float size_;
};

#endif //ANTS__HIVE_H_
