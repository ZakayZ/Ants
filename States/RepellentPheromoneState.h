//
// Created by Artem Novikov on 17.09.2022.
//

#ifndef ANTS_STATES_REPELANTPHEROMONESTATE_H_
#define ANTS_STATES_REPELANTPHEROMONESTATE_H_

#include "HomeSearchState.h"

class RepellentPheromoneState : public HomeSearchState {
 public:
  RepellentPheromoneState(SensorData& ant_senses, PheromoneData& ant_pheromone,
                          MovementData& ant_move, const GeneralData& ant_general);

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;

 private:
  float active_time_{};
};

#endif //ANTS_STATES_REPELANTPHEROMONESTATE_H_
