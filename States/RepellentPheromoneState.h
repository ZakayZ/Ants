//
// Created by Artem Novikov on 17.09.2022.
//

#ifndef ANTS_STATES_REPELANTPHEROMONESTATE_H_
#define ANTS_STATES_REPELANTPHEROMONESTATE_H_

#include "HomeSearchState.h"

class RepellentPheromoneState : public HomeSearchState {
 public:
  RepellentPheromoneState(SensorData& ant_senses, PheromoneData& ant_pheromone,
                          MovementData& ant_move, const GeneralData& ant_general)
      : HomeSearchState(ant_senses, ant_pheromone, ant_move, ant_general) {}

  void Decide(float delta_time) override {
    HomeSearchState::Decide(delta_time);

    if (active_time_ >= general_data_.repellent_duration) {
      change_state_ = StateType::HomeSearch;
    }
  }

  void Interact(WorldData& world_data, float delta_time) override {
    active_time_ += delta_time;
    world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                           move_data_.position,
                                           -pheromone_data_.pheromone_strength * delta_time,
                                           PheromoneType::Food);
  }

 private:
  float active_time_{};
};

#endif //ANTS_STATES_REPELANTPHEROMONESTATE_H_
