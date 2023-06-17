//
// Created by Artem Novikov on 25.05.2023.
//

#include "AntState.h"
#include "creature/ant/Ant.h"
#include "world/World.h"

AntState::AntState(Ant& host) : State(host), host_(host), general_data_(host_.GetGeneralData()) {}

void AntState::Rotate() {
  host_.GetMoveData().target_direction = -host_.GetMoveData().target_direction;
  host_.GetMoveData().velocity = -host_.GetMoveData().velocity;
}

void AntState::FollowPoint(const Vector2f& point) {
  host_.GetMoveData().target_direction = Normalised(point - host_.GetMoveData().position);
}

void AntState::FollowPheromone(World& world, PheromoneType type, Time dt) {
  auto pheromone_data = world.GetPheromoneMap().GetPheromoneStrength(host_.SensitiveRange(), type);
  if (pheromone_data.total_strength > 0.01f) {
    host_.GetMoveData().target_direction = Normalised(host_.GetMoveData().target_direction +
        (dt * pheromone_data.total_strength) * (pheromone_data.mean_position - host_.GetMoveData().position)
    );
  }
}