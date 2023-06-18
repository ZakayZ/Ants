//
// Created by Artem Novikov on 09.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_WARRIOR_H_
#define ANTS_NEW_CREATURE_ANT_WARRIOR_H_

#include "Ant.h"

#include "creature/AI/state/antState/WarriorAI.h"
#include "creature/AI/state/antState/AttackState.h"

class Warrior : public Ant {
 public:
  Warrior(MoveData move_data, const GeneralData& general_data)
      : Ant(move_data,
            std::make_unique<WarriorAI>(std::make_unique<AttackState>(*this)),
            general_data) {}
};

#endif //ANTS_NEW_CREATURE_ANT_WARRIOR_H_
