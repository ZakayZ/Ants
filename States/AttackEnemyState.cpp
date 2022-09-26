//
// Created by Artem Novikov on 23.09.2022.
//

#include "World/WorldData.h"
#include "Ants/Ant.h"
#include "AttackEnemyState.h"

std::function<bool(Ant&)> AttackEnemyState::GetProximitySensor() const {
  return [&pos = move_data_.position, sq_dist = std::pow(general_data_.visible_range, 2)](Ant& other_ant) {
    return (other_ant.GetPosition() - pos).SquaredLength() <= sq_dist;
  };
}

std::function<void(Ant&)> AttackEnemyState::GetEnemySensor() const {
  return [&pos = move_data_.position, &sensor_data = sensor_data_, my_idx = general_data_.colony_index,
      min_sq_dist = std::pow(general_data_.visible_range, 2)](Ant& other_ant) mutable {
    auto sq_dist = (other_ant.GetPosition() - pos).SquaredLength();
    if (my_idx == other_ant.GetColonyIndex()) {
      other_ant.InitiateFight();
    } else {
      if (sq_dist < min_sq_dist) {
        sensor_data.target_ant = {&other_ant};
        min_sq_dist = sq_dist;
      }
    }
  };
}

void AttackEnemyState::Decide(float delta_time) {
  if (!sensor_data_.target_ant.has_value()) {
    change_state_ = StateType::EnemySearch;
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
      attack_cooldown_ += general_data_.attack_delay;
    }
  }
}

void AttackEnemyState::Interact(WorldData& world_data, float delta_time) {
  world_data.pheromone_map_.LayPheromone(general_data_.colony_index,
                                         move_data_.position,
                                         pheromone_data_.pheromone_strength,
                                         PheromoneType::Enemy);
}
