//
// Created by Artem Novikov on 30.08.2022.
//

#ifndef ANTS_ANTDATA_GENERALDATA_H_
#define ANTS_ANTDATA_GENERALDATA_H_

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
  float  pheromone_capacity = 10.f;
  float pheromone_decay = 0.1f;
  float repellent_duration = 0.2f;

  /// colony related
  mutable size_t ant_count{};
};

#endif //ANTS_ANTDATA_GENERALDATA_H_
