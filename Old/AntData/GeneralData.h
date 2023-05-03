//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_ANTDATA_GENERALDATA_H_
#define ANTS_ANTDATA_GENERALDATA_H_

#include "Ants/AntType.h"

struct GeneralData {
  float ant_size = 1.f;

  /// movement related
  float max_speed = 15.f;
  float steer_speed = 5.f;
  float wander_cooldown = 0.2f;

  /// food related
  float visible_range = 30.f;
  int max_capacity = 1;

  /// pheromone related
  float pheromone_range = 6.f;
  float pheromone_capacity = 10.f;
  float pheromone_decay = 0.1f;
  float repellent_duration = 0.2f;

  /// fight related
  int attack_damage = 5;
  int max_health = 10000;
  float attack_delay = 0.1;

  /// colony related
  AntType host_type;
  size_t colony_index = 0;
  mutable size_t ant_count = 0;
};

struct WorkerGeneralData : GeneralData {
  WorkerGeneralData() {
    ant_size = 1.f;

    /// movement related
    max_speed = 15.f;
    steer_speed = 5.f;
    wander_cooldown = 0.2f;

    /// food related
    visible_range = 15.f;
    max_capacity = 2;

    /// pheromone related
    pheromone_range = 6.f;
    pheromone_capacity = 10.f;
    pheromone_decay = 0.1f;
    repellent_duration = 0.2f;

    /// fight related
    attack_damage = 5;
    max_health = 100;
    attack_delay = 0.1;

    /// colony related
    host_type = AntType::kWorker;
    colony_index = 0;
    ant_count = 0;
  }
};

struct ScoutGeneralData : GeneralData {
  ScoutGeneralData() {
    ant_size = 0.5f;

    /// movement related
    max_speed = 25.f;
    steer_speed = 10.f;
    wander_cooldown = 0.1f;

    /// food related
    visible_range = 30.f;
    max_capacity = 0;

    /// pheromone related
    pheromone_range = 3.f;
    pheromone_capacity = 30.f;
    pheromone_decay = 0.05f;
    repellent_duration = 2.f;

    /// fight related
    attack_damage = 3;
    max_health = 50;
    attack_delay = 0.1;

    /// colony related
    host_type = AntType::kScout;
    colony_index = 0;
    ant_count = 0;
  }
};

struct SoldierGeneralData : GeneralData {
  SoldierGeneralData() {
    ant_size = 2.f;

    /// movement related
    max_speed = 12.f;
    steer_speed = 5.f;
    wander_cooldown = 0.2f;

    /// food related
    visible_range = 20.f;
    max_capacity = 0;

    /// pheromone related
    pheromone_range = 5.f;
    pheromone_capacity = 5.f;
    pheromone_decay = 0.1f;
    repellent_duration = 0.f;

    /// fight related
    attack_damage = 20;
    max_health = 200;
    attack_delay = 0.1;

    /// colony related
    host_type = AntType::kSoldier;
    colony_index = 0;
    ant_count = 0;
  }
};

#endif //ANTS_ANTDATA_GENERALDATA_H_
