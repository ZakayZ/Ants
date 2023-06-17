//
// Created by Artem Novikov on 05.06.2023.
//

#include "Colony.h"

#include "creature/ant/antData/AntType.h"

#include "creature/ant/Larva.h"
#include "creature/ant/Warrior.h"
#include "creature/ant/Worker.h"
#include "creature/ant/Scout.h"
#include "creature/ant/Queen.h"

size_t Colony::colonies_count = 0;

Colony::Colony(std::vector<Hive>& colony_hives) : colony_id_(colonies_count++), hives_(colony_hives) {
  ant_general_data_[AntType::Worker] = GeneralData(); /// TODO Specialization
  ant_general_data_[AntType::Soldier] = GeneralData();
  ant_general_data_[AntType::Scout] = GeneralData();

  for (auto& general_data : ant_general_data_) {
    general_data.colony_index = colony_id_;
  }

  target_ant_fractions_[AntType::Queen] = 0; /// TODO
  target_ant_fractions_[AntType::Worker] = 0.8f;
  target_ant_fractions_[AntType::Soldier] = 0.0f;
  target_ant_fractions_[AntType::Scout] = 0.1f;
}

void Colony::Update(Time dt) {
  /// TODO
}

Colony::AntPtr Colony::CreateAnt(const Vector2f& position) {
  std::make_shared<>();
}

Colony::AntPtr Colony::MakeWorker(const Vector2f& position) {

}

Colony::AntPtr Colony::MakeWarrior(const Vector2f& position) {

}

Colony::AntPtr Colony::MakeQueen(const Vector2f& position) {

}

Colony::AntPtr Colony::MakeScout(const Vector2f& position) {

}

