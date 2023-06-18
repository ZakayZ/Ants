//
// Created by Artem Novikov on 05.06.2023.
//

#include "Colony.h"

#include <utility>

#include "creature/ant/antData/AntType.h"

#include "creature/ant/Larva.h"
#include "creature/ant/Warrior.h"
#include "creature/ant/Scout.h"
#include "creature/ant/Worker.h"
#include "creature/ant/Queen.h"

#include "world/World.h"

size_t Colony::colonies_count = 0;

Colony::Colony(std::vector<Hive*>&& colony_hives) : colony_id_(colonies_count++), hives_(std::move(colony_hives)) {
  ant_general_data_[AntType::kWorker] = GeneralData(colony_id_); /// TODO Specialization
  ant_general_data_[AntType::kSoldier] = GeneralData(colony_id_);
  ant_general_data_[AntType::kScout] = GeneralData(colony_id_);

  for (auto& general_data : ant_general_data_) {
    general_data.colony_index = colony_id_;
  }

  target_ant_fractions_[AntType::kQueen] = 0; /// TODO
  target_ant_fractions_[AntType::kWorker] = 0.8f;
  target_ant_fractions_[AntType::kSoldier] = 0.0f;
  target_ant_fractions_[AntType::kScout] = 0.1f;
}

void Colony::Update(World& world, Time) {
  uint32_t unit_cost = 10;
  for (auto& hive : hives_) {
    while (hive->food_cnt_ >= unit_cost) {
      hive->food_cnt_ -= unit_cost;
      world.GetCreatureMap().AddCreature(CreateAnt(hive->position_));
    }
  }
}

Colony::AntPtr Colony::CreateAnt(const Vector2f& position) {
  return std::make_shared<Worker>(MoveData{.position=position}, ant_general_data_[AntType::kWorker]);
}

Colony::AntPtr Colony::MakeWorker(const Vector2f& position) {
  return std::make_shared<Worker>(MoveData{.position=position}, ant_general_data_[AntType::kWorker]);
}

Colony::AntPtr Colony::MakeWarrior(const Vector2f& position) {
  return std::make_shared<Warrior>(MoveData{.position=position}, ant_general_data_[AntType::kSoldier]);
}

Colony::AntPtr Colony::MakeQueen(const Vector2f& position) {
  return std::make_shared<Queen>(MoveData{.position=position}, ant_general_data_[AntType::kQueen]);
}

Colony::AntPtr Colony::MakeScout(const Vector2f& position) {
  return std::make_shared<Scout>(MoveData{.position=position}, ant_general_data_[AntType::kScout]);
}

