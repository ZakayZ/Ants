//
// Created by Artem Novikov on 17.09.2022.
//

#ifndef ANTS_STATES_REPELANTPHEROMONESTATE_H_
#define ANTS_STATES_REPELANTPHEROMONESTATE_H_

#include "HomeSearchState.h"

class RepellentPheromoneState : public HomeSearchState {
 public:
  using ::HomeSearchState::HomeSearchState;

  void Decide(float delta_time) override;

  void Interact(WorldData& world_data, float delta_time) override;

 private:
  float active_time_{};
};

#endif //ANTS_STATES_REPELANTPHEROMONESTATE_H_
