//
// Created by Artem Novikov on 28.08.2022.
//

#ifndef ANTS__FOODSOURCE_H_
#define ANTS__FOODSOURCE_H_

class FoodSource {
 public:
  FoodSource(const Vector2f& position, int capacity, float size = 2.f)
      : position_(position), food_stored_(capacity), size_(size) {}

  int GetFood(int desired_food) {
    if (food_stored_ < desired_food) { desired_food = food_stored_; }
    food_stored_ -= desired_food;
    return desired_food;
  }

  [[nodiscard]] const Vector2f& GetPosition() const { return position_; }

  [[nodiscard]] float GetSize() const { return size_; }

  [[nodiscard]] bool IsEmpty() const {
    return food_stored_ == 0;
  }
 private:
  Vector2f position_;
  int food_stored_;
  float size_;
};

#endif //ANTS__FOODSOURCE_H_
