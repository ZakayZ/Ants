//
// Created by Artem Novikov on 19.09.2022.
//

#ifndef ANTS_WORLD_HIVEMAP_H_
#define ANTS_WORLD_HIVEMAP_H_

#include "Hive.h"

class HiveMap {
 public:
  using Holder = std::vector<Hive>;
  using iterator = Holder::iterator;
  using const_iterator = Holder::const_iterator;

  HiveMap(const std::vector<Hive>& hives) : hives_(hives) {}

  void Update(float delta_time) {}

  void AddHive(const Hive& source) { hives_.push_back(source); }

  auto& operator[](size_t index) { return hives_[index]; }

  iterator begin() { return hives_.begin(); }

  const_iterator begin() const { return hives_.cbegin(); }

  const_iterator cbegin() const { return hives_.cbegin(); }

  iterator end() { return hives_.end(); }

  const_iterator end() const { return hives_.cend(); }

  const_iterator cend() const { return hives_.cend(); }

 private:
  std::vector<Hive> hives_;
};

#endif //ANTS_WORLD_HIVEMAP_H_
