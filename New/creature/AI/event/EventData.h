//
// Created by Artem Novikov on 21.06.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_EVENT_EVENTDATA_H_
#define ANTS_NEW_CREATURE_AI_EVENT_EVENTDATA_H_

#include "EventType.h"

struct EventData {
  EventData(EventType type) : type(type) {}

  virtual ~EventData() = 0;

  const EventType type;
};

#endif //ANTS_NEW_CREATURE_AI_EVENT_EVENTDATA_H_
