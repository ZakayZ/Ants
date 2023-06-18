//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_WORKER_H_
#define ANTS_NEW_CREATURE_ANT_WORKER_H_

#include "Ant.h"
#include "creature/ant/antData/ResourceSack.h"
#include "creature/AI/state/antState/WorkerAI.h"
#include "creature/AI/state/antState/FoodSearchState.h"

class Worker : public Ant {
 public:
  Worker(MoveData move_data, const GeneralData& general_data)
      : Ant(move_data,
            std::make_unique<WorkerAI>(std::make_unique<FoodSearchState>(*this)),
            general_data),
        resource_sack_(general_data.max_capacity) {}

  ResourceSack& GetResourceSack() { return resource_sack_; }

 private:
  ResourceSack resource_sack_;
};

#endif //ANTS_NEW_CREATURE_ANT_WORKER_H_
