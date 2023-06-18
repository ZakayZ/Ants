//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_SCOUT_H_
#define ANTS_NEW_CREATURE_ANT_SCOUT_H_

#include "Ant.h"

#include "creature/AI/state/antState/WorkerAI.h"
#include "creature/AI/state/antState/FoodSearchState.h"

class Scout : public Ant {
 public:
  Scout(MoveData move_data, const GeneralData& general_data)
      : Ant(move_data,
            std::make_unique<WorkerAI>(std::make_unique<FoodSearchState>(*this)),
            general_data) {}
};

#endif //ANTS_NEW_CREATURE_ANT_SCOUT_H_
