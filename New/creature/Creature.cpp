//
// Created by Artem Novikov on 18.06.2023.
//

#include "Creature.h"
#include "AI/AI.h"

Creature::Creature(MoveData move_data, CreatureData creature_data, std::unique_ptr<AI>&& brain)
    : move_data_(move_data), creature_data_(creature_data), brain_(std::move(brain)) {}

Creature::~Creature() = default;

