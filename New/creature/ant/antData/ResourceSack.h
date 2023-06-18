//
// Created by Artem Novikov on 27.05.2023.
//

#ifndef ANTS_NEW_CREATURE_ANT_ANTDATA_RESOURCESACK_H_
#define ANTS_NEW_CREATURE_ANT_ANTDATA_RESOURCESACK_H_

#include <cstdint>
#include "ResourceType.h"

struct ResourceData {
  uint32_t amount;
  ResourceType type;
};

class ResourceSack {
 public:
  ResourceSack(uint32_t max_capacity) : Capacity(max_capacity), resource_{0, ResourceType::None} {}

  void Fill(uint32_t resource, ResourceType type);

  void Fill(ResourceData resource);

  [[nodiscard]] const ResourceData& View() const;

  ResourceData EmptySack();

  bool IsEmpty() const;

  const uint32_t Capacity;

 private:
  ResourceData resource_;
};

#endif //ANTS_NEW_CREATURE_ANT_ANTDATA_RESOURCESACK_H_
