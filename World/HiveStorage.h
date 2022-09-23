//
// Created by Artem Novikov on 01.09.2022.
//

#ifndef ANTS__HIVESTORAGE_H_
#define ANTS__HIVESTORAGE_H_

class HiveStorage {
 public:
  HiveStorage(int initial_capacity) : stored_food_(initial_capacity) {}

  void StoreFood(int carried_food) { stored_food_ += carried_food; }

  void Alert(float pheromone_level) { enemy_pheromone_ += pheromone_level; }

  [[nodiscard]] int StoredFood() const { return stored_food_; }

 private:
  int stored_food_;
  float enemy_pheromone_;
};

#endif //ANTS__HIVESTORAGE_H_
