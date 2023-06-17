//
// Created by Artem Novikov on 27.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_ANTDATA_RESOURCESACK_H_
#define ANTS_NEW_CREATURE_ANT_ANTDATA_RESOURCESACK_H_

#include "ResourceType.h"

struct ResourceData {
  int amount;
  ResourceType type;
};

class ResourceSack {
 public:
  ResourceSack(int max_capacity) : carry_capacity_(max_capacity), resource_{0, ResourceType::None} {}

  void Fill(int resource, ResourceType type);

  void Fill(ResourceData resource);

  const ResourceData& View() const;

  ResourceData EmptySack();

  bool IsEmpty() const;

 private:
  const int carry_capacity_;
  ResourceData resource_;
};

#endif //ANTS_NEW_CREATURE_ANT_ANTDATA_RESOURCESACK_H_
