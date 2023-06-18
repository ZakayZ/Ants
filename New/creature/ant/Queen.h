//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_QUEEN_H_
#define ANTS_NEW_CREATURE_ANT_QUEEN_H_

#include "Ant.h"

#include "creature/AI/state/antState/QueenAI.h"

class Queen : public Ant {
 public:
  Queen(MoveData move_data, const GeneralData& general_data)
      : Ant(move_data,
            std::make_unique<QueenAI>(std::make_unique<FoodSearchState>(*this)),
            general_data) {}
};

#endif //ANTS_NEW_CREATURE_ANT_QUEEN_H_
