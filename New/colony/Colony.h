//
// Created by Artem Novikov on 05.06.2023.
//

#ifndef ANTS_NEW_COLONY_COLONY_H_
#define ANTS_NEW_COLONY_COLONY_H_

#include <memory>
#include <list>
#include <vector>

#include "Hive.h"
#include "creature/ant/antData/GeneralData.h"

class Ant;

class Larva;

class Colony {
 public:
  using AntPtr = std::shared_ptr<Ant>;

  Colony(std::vector<Hive>& colony_hives);

  [[nodiscard]] size_t GetIndex() const { return colony_id_; }

  [[nodiscard]] const std::vector<Hive>& GetHives() const { return hives_; }

  void Update(Time dt);

  std::unique_ptr<Ant> GetInitialQueen();

 private:
  static size_t colonies_count;

  AntPtr CreateAnt(const Vector2f& position);

  AntPtr MakeWorker(const Vector2f& position);

  AntPtr MakeWarrior(const Vector2f& position);

  AntPtr MakeQueen(const Vector2f& position);

  AntPtr MakeScout(const Vector2f& position);

  const size_t colony_id_;

  std::vector<Hive>& hives_;
  std::array<GeneralData, 4> ant_general_data_;
  std::array<Float, 4> target_ant_fractions_;
  std::list<Larva> larva_;
};

#endif //ANTS_NEW_COLONY_COLONY_H_
