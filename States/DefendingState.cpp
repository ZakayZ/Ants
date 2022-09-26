//
// Created by Artem Novikov on 24.09.2022.
//

#include "World/WorldData.h"
#include "Ants/Ant.h"
#include "DefendingState.h"

DefendingState::DefendingState(StateType last_state, SensorData& ant_sensor, PheromoneData& ant_pheromone,
                               MovementData& ant_move, const GeneralData& ant_general)
    : AntState(ant_sensor, ant_pheromone, ant_move, ant_general), last_state_(last_state) {}

std::function<bool(Ant&)> DefendingState::GetProximitySensor() const {
  return [&pos = move_data_.position, sq_dist = std::pow(general_data_.visible_range, 2),
      my_idx = general_data_.colony_index](Ant& other_ant) {
    return other_ant.GetColonyIndex() != my_idx && (other_ant.GetPosition() - pos).SquaredLength() <= sq_dist;
  };
}

std::function<void(Ant&)> DefendingState::GetEnemySensor() const {
  return [&pos = move_data_.position, &sensor_data = sensor_data_,
      min_sq_dist = std::pow(general_data_.visible_range, 2)](Ant& other_ant) mutable {
    auto sq_dist = (other_ant.GetPosition() - pos).SquaredLength();
    if (sq_dist < min_sq_dist) {
      sensor_data.target_ant = {&other_ant};
      min_sq_dist = sq_dist;
    }
  };
}

void DefendingState::Decide(float delta_time) {
  if (!sensor_data_.target_ant.has_value()) {
    change_state_ = last_state_;
    return;
  }

  auto& ant = *sensor_data_.target_ant.value();
  FollowPoint(ant.GetPosition());

  if ((ant.GetPosition() - move_data_.position).SquaredLength()
      <= std::pow(sensor_data_.target_ant.value()->GetSize() + general_data_.ant_size, 2)) {
    move_data_.velocity[0] = move_data_.velocity[1] = 0.f;
    ant.InitiateFight();
    attack_cooldown_ -= delta_time;
    if (attack_cooldown_ <= 0.f) {
      ant.ReceiveDamage(general_data_.attack_damage);
      change_state_ = last_state_;
    }
  }
}

void DefendingState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength,
                                         PheromoneType::Enemy);
}
