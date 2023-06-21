//
// Created by Artem Novikov on 21.06.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_EVENT_HIVEEVENT_H_
#define ANTS_NEW_CREATURE_AI_EVENT_HIVEEVENT_H_

#include "colony/Hive.h"
#include "EventData.h"

struct HiveEvent : public EventData {
  HiveEvent(Hive& hive) : EventData(EventType::Hive), hive(hive) {}

  Hive& hive;
};

#endif //ANTS_NEW_CREATURE_AI_EVENT_HIVEEVENT_H_
