//
// Created by Artem Novikov on 27.05.2023.
//

#include "ResourceSack.h"

void ResourceSack::Fill(uint32_t resource, ResourceType type) {
  Fill(ResourceData{resource, type});
}

void ResourceSack::Fill(ResourceData resource) {
  resource_ = resource;
}

const ResourceData& ResourceSack::View() const {
  return resource_;
}

ResourceData ResourceSack::EmptySack() {
  auto copy = resource_;
  resource_ = ResourceData{0, ResourceType::None};
  return copy;
}

bool ResourceSack::IsEmpty() const {
  return resource_.amount == 0;
}
