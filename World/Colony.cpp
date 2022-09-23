// Created by Artem Novikov on 27.08.2022.
//

#include "Colony.h"

Colony::Colony(std::vector<Hive>& colony_hives, size_t colony_index)
    : hives_(colony_hives), colony_index_(colony_index) {
  for (auto& general_data : ant_general_data_) {
    general_data.colony_index = colony_index_;
  }

  ant_fractions_[AntType::kQueen] = 0;
  ant_fractions_[AntType::kWorker] = 1;
  ant_fractions_[AntType::kSoldier] = 0;
  ant_fractions_[AntType::kScout] = 0;
}

std::unique_ptr<Ant> Colony::CreateAnt(const Vector2f& position) {
  AntType type = AntType::kWorker;

  int rand_value = rand() % 1000;
  int cumulative_value = 0;
  for (size_t i = 0; i < 4; ++i) {
    int addition = ant_fractions_[i] * 1000.f;
    if (rand_value < cumulative_value + addition) {
      type = AntType(i);
      break;
    }
  }
  return MakeAnt(position, type);
}

std::unique_ptr<Ant> Colony::GetInitialQueen() {
  return MakeQueen(hives_[0].GetPosition());
}

std::unique_ptr<Ant> Colony::MakeAnt(const Vector2f& position, AntType type) {
  switch (type) {
    case AntType::kWorker: { return MakeWorker(position); }
    case AntType::kQueen: { return MakeQueen(position); }
    case AntType::kSoldier: { return MakeWarrior(position); }
    case AntType::kScout: { return MakeScout(position); }
  }
}

std::unique_ptr<Ant> Colony::MakeWorker(const Vector2f& position) {
  return std::make_unique<Worker>(position, colony_index_, ant_general_data_[AntType::kWorker], 10);
}

std::unique_ptr<Ant> Colony::MakeWarrior(const Vector2f& position) {
  return std::make_unique<Soldier>(position, colony_index_, ant_general_data_[AntType::kSoldier], 10);
}

std::unique_ptr<Ant> Colony::MakeQueen(const Vector2f& position) {
  return std::make_unique<Queen>(position, colony_index_, ant_general_data_[AntType::kQueen], 10);
}

std::unique_ptr<Ant> Colony::MakeScout(const Vector2f& position) {
  return std::make_unique<Scout>(position, colony_index_, ant_general_data_[AntType::kScout], 10);
}
