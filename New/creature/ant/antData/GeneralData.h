//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_ANTDATA_GENERALDATA_H_
#define ANTS_NEW_CREATURE_ANT_ANTDATA_GENERALDATA_H_

#include "DataTypes.h"

struct GeneralData {
  Float ant_size = 1.f;

  /// movement related
  Float max_speed = 15.f;
  Float steer_speed = 5.f;
  Float wander_cooldown = 0.2f;

  /// food related
  Float visible_range = 30.f;
  int max_capacity = 1;

  /// pheromone related
  Float pheromone_range = 6.f;
  Float pheromone_capacity = 10.f;
  Float pheromone_decay = 0.1f;
  Float repellent_duration = 0.2f;

  /// fight related
  int attack_damage = 5;
  int max_health = 10000;
  Float attack_delay = 0.1;

  /// colony related
//  AntType host_type;
  size_t colony_index = 0;
  mutable size_t ant_count = 0;
};

#endif //ANTS_NEW_CREATURE_ANT_ANTDATA_GENERALDATA_H_
