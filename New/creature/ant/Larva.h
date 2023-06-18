//
// Created by Artem Novikov on 05.06.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_LARVA_H_
#define ANTS_NEW_CREATURE_ANT_LARVA_H_

#include "Ant.h"

class Larva : public Ant {
 public:
  Larva() : Ant(MoveData{},
                nullptr,
                GeneralData()) {}

  void Update(World& world, Time dt) override {} /// TODO

 private:
};

#endif //ANTS_NEW_CREATURE_ANT_LARVA_H_
