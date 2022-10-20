//
// Created by Artem Novikov on 24.09.2022.
//

#include "World/WorldData.h"
#include "Ants/Ant.h"
#include "DefendingState.h"

DefendingState::DefendingState(Ant& host, StateType last_state) : AntState(host), last_state_(last_state) {}

std::function<bool(Ant&)> DefendingState::GetProximitySensor() const {
  return [&pos = host_.GetPosition(), sq_dist = std::pow(general_data_.visible_range, 2),
      my_idx = general_data_.colony_index](Ant& other_ant) {
    return other_ant.GetColonyIndex() != my_idx && (other_ant.GetPosition() - pos).SquaredLength() <= sq_dist;
  };
}

std::function<void(Ant&)> DefendingState::GetEnemySensor() const {
  return [&host = host_,
      min_sq_dist = std::pow(general_data_.visible_range, 2)](Ant& other_ant) mutable {
    auto sq_dist = (other_ant.GetPosition() - host.GetPosition()).SquaredLength();
    if (sq_dist < min_sq_dist) {
      host.SetTarget(other_ant);
      min_sq_dist = sq_dist;
    }
  };
}

void DefendingState::Decide(float delta_time) {
  if (!host_.GetSensorData().target_ant.has_value()) {
    host_.ChangeState(last_state_);
    return;
  }

  auto& ant = *host_.GetSensorData().target_ant.value();
  FollowPoint(ant.GetPosition());

  if ((ant.GetPosition() - host_.GetPosition()).SquaredLength()
      <= std::pow(host_.GetSensorData().target_ant.value()->GetSize() + general_data_.ant_size, 2)) {
    host_.Stop();
    ant.InitiateFight();
    attack_cooldown_ -= delta_time;
    if (attack_cooldown_ <= 0.f) {
      ant.ReceiveDamage(general_data_.attack_damage);
      host_.ChangeState(last_state_);
      return;
    }
  }
}

void DefendingState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         host_.GetPosition(),
                                         host_.GetPheromoneData().pheromone_strength,
                                         PheromoneType::Enemy);
}
