//
// Created by Artem Novikov on 17.09.2022.
//

#ifndef ANTS_STATES_REPELANTPHEROMONESTATE_H_
#define ANTS_STATES_REPELANTPHEROMONESTATE_H_

#include "HomeSearchState.h"

class RepellentPheromoneState : public HomeSearchState {
 public:
  RepellentPheromoneState(SensorData& ant_senses, MovementData& ant_move,
                          PheromoneData& ant_pheromone, const GeneralData& ant_general)
      : HomeSearchState(ant_senses, ant_move, ant_pheromone), general_data_(ant_general) {}

  void Decide() override {
    HomeSearchState::Decide();

    if (active_time_ >= general_data_.repellent_duration) {
      change_state_ = StateType::HomeSearch;
    }
  }

  void Interact(WorldData& world_data, float delta_time) override {
    active_time_ += delta_time;
    world_data.pheromone_map_.LayPheromone(move_data_.position, -pheromone_data_.pheromone_strength * delta_time,
                                           PheromoneType::Food);
  }

 private:
  const GeneralData& general_data_;
  float active_time_{};
};

#endif //ANTS_STATES_REPELANTPHEROMONESTATE_H_
