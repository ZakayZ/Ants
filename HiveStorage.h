//
// Created by Artem Novikov on 01.09.2022.
//

#ifndef ANTS__HIVESTORAGE_H_
#define ANTS__HIVESTORAGE_H_

class HiveStorage {
 public:
  void StoreFood(int carried_food) { stored_food_ += carried_food; }

  [[nodiscard]] int StoredFood() const { return stored_food_; }

 private:
  int stored_food_ = 100;
};

#endif //ANTS__HIVESTORAGE_H_
