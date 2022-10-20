//
// Created by Artem Novikov on 23.09.2022.
//

#include "World/WorldData.h"
#include "Ants/Ant.h"
#include "EnemySearchState.h"

std::function<bool(Ant&)> EnemySearchState::GetProximitySensor() const {
  return [&pos = host_.GetPosition(), sq_dist = std::pow(general_data_.visible_range, 2),
      my_idx = general_data_.colony_index](Ant& other_ant) {
    return other_ant.GetColonyIndex() != my_idx && (other_ant.GetPosition() - pos).SquaredLength() <= sq_dist;
  };
}

std::function<void(Ant&)> EnemySearchState::GetEnemySensor() const {
  return [&host = host_,
      min_sq_dist = std::pow(general_data_.visible_range, 2)](Ant& other_ant) mutable {
    auto sq_dist = (other_ant.GetPosition() - host.GetPosition()).SquaredLength();
    if (sq_dist < min_sq_dist) {
      host.SetTarget(other_ant);
      min_sq_dist = sq_dist;
    }
  };
}

void EnemySearchState::Decide(float delta_time) {
  if (host_.GetSensorData().target_ant.has_value()) {
    host_.ChangeState<AttackEnemyState>();
    return;
  }

  FollowPheromone(delta_time);
}

void EnemySearchState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         host_.GetPosition(),
                                         host_.GetPheromoneData().pheromone_strength,
                                         PheromoneType::Home);
}
