//
// Created by Artem Novikov on 21.06.2023.
//

#ifndef ANTS_NEW_CREATURE_AI_EVENT_RESOURCEEVENT_H_
#define ANTS_NEW_CREATURE_AI_EVENT_RESOURCEEVENT_H_

#include "food/FoodSource.h"
#include "EventData.h"

struct ResourceEvent : public EventData {
  ResourceEvent(FoodSource& food) : EventData(EventType::Resource), food_source(food) {}

  FoodSource& food_source;
};

#endif //ANTS_NEW_CREATURE_AI_EVENT_RESOURCEEVENT_H_
