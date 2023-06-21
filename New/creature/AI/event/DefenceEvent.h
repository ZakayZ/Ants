//
// Created by Artem Novikov on 21.06.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_EVENT_DEFENCEEVENT_H_
#define ANTS_NEW_CREATURE_AI_EVENT_DEFENCEEVENT_H_

#include "colony/Hive.h"
#include "EventData.h"

class Creature;

struct DefenceEvent : public EventData {
  DefenceEvent(std::shared_ptr<Creature>& creature, uint32_t damage)
      : EventData(EventType::Attacked), attacker(creature), damage(damage) {}

  std::shared_ptr<Creature> attacker;
  uint32_t damage;
};

#endif //ANTS_NEW_CREATURE_AI_EVENT_DEFENCEEVENT_H_
