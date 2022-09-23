//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__COLONY_H_
#define ANTS__COLONY_H_

#include <vector>

#include "Hive.h"
#include "AntData/GeneralData.h"

#include "Ants/Worker.h"
#include "Ants/Scout.h"
#include "Ants/Soldier.h"
#include "Ants/Queen.h"

class Colony {
 public:
  Colony(std::vector<Hive>& colony_hives, size_t colony_index);

  [[nodiscard]] size_t GetIndex() const { return colony_index_; }

  [[nodiscard]] const auto& GetHives() const { return hives_; }

  template <class Iter>
  void Update(float delta_time, Iter ant_inserter);

  std::unique_ptr<Ant> GetInitialQueen();

 private:
  std::unique_ptr<Ant> CreateAnt(const Vector2f& position);

  std::unique_ptr<Ant> MakeAnt(const Vector2f& position, AntType type);

  std::unique_ptr<Ant> MakeWorker(const Vector2f& position);

  std::unique_ptr<Ant> MakeWarrior(const Vector2f& position);

  std::unique_ptr<Ant> MakeQueen(const Vector2f& position);

  std::unique_ptr<Ant> MakeScout(const Vector2f& position);

  std::vector<Hive>& hives_;
  size_t colony_index_;
  std::array<GeneralData, 4> ant_general_data_;
  std::array<float, 4> ant_fractions_;
};

/////////////////////////////////////////////////DEFINITION///////////////////////////////////////////////////////

template <class Iter>
void Colony::Update(float delta_time, Iter ant_inserter) {
  int ant_cost = 1;
  for (auto& hive : hives_) {
    while (hive.GetStorage().StoredFood() >= ant_cost) {
      ant_inserter = std::move(CreateAnt(hive.GetPosition()));
      hive.GetStorage().StoreFood(-ant_cost);
    }
  }
}

#endif //ANTS__COLONY_H_
