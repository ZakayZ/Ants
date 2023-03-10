// Created by Artem Novikov on 27.08.2022.
//

#include "Colony.h"

Colony::Colony(std::vector<Hive>& colony_hives, size_t colony_index)
    : hives_(colony_hives), colony_index_(colony_index) {

  ant_general_data_[AntType::kWorker] = WorkerGeneralData();
  ant_general_data_[AntType::kSoldier] = SoldierGeneralData();
  ant_general_data_[AntType::kScout] = ScoutGeneralData();

  for (auto & general_data : ant_general_data_) {
    general_data.colony_index = colony_index_;
  }

  ant_general_data_[AntType::kQueen].host_type = AntType::kQueen;

  ant_fractions_[AntType::kQueen] = 0;
  ant_fractions_[AntType::kWorker] = 0.8f;
  ant_fractions_[AntType::kSoldier] = 0.0f;
  ant_fractions_[AntType::kScout] = 0.1f;
}

std::unique_ptr<Ant> Colony::CreateAnt(const Vector2f& position) {
  AntType type = AntType::kWorker;

  float total = ant_fractions_[0] + ant_fractions_[1] + ant_fractions_[2] + ant_fractions_[3];
  int rand_value = rand() % 1000;
  int cumulative_value = 0;
  for (size_t i = 0; i < ant_fractions_.size(); ++i) {
    int addition = static_cast<int>(ant_fractions_[i] / total * 1000.f);
    if (rand_value < cumulative_value + addition) {
      type = AntType(i);
      break;
    }
    cumulative_value += addition;
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
  return std::make_unique<Worker>(position, ant_general_data_[AntType::kWorker]);
}

std::unique_ptr<Ant> Colony::MakeWarrior(const Vector2f& position) {
  return std::make_unique<Soldier>(position, ant_general_data_[AntType::kSoldier]);
}

std::unique_ptr<Ant> Colony::MakeQueen(const Vector2f& position) {
  return std::make_unique<Queen>(position, ant_general_data_[AntType::kQueen]);
}

std::unique_ptr<Ant> Colony::MakeScout(const Vector2f& position) {
  return std::make_unique<Scout>(position, ant_general_data_[AntType::kScout]);
}
