//
// Created by Artem Novikov on 21.06.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_EVENT_CREATUREEVENT_H_
#define ANTS_NEW_CREATURE_AI_EVENT_CREATUREEVENT_H_

#include "colony/Hive.h"
#include "EventData.h"

class Creature;

struct CreatureEvent : public EventData {
  CreatureEvent(std::shared_ptr<Creature>& creature) : EventData(EventType::Creature), creature_ptr(creature) {}

  std::shared_ptr<Creature> creature_ptr;
};

#endif //ANTS_NEW_CREATURE_AI_EVENT_CREATUREEVENT_H_
