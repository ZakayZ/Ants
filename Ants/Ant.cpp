//
// Created by Artem Novikov on 03.09.2022.
//

#include "World/WorldData.h"
#include "World/Sensor.h"
#include "Ant.h"

Ant::Ant(const Vector2f& position, const GeneralData& general_data)
    : movement_data_(position), sensor_data_(), food_data_(), general_data_(general_data),
      pheromone_data_(general_data.pheromone_capacity), fight_data_(general_data.max_health) {
  movement_data_.target_direction = RandomGenerator().GetVector2f();
  movement_data_.random_cooldown = general_data.wander_cooldown * RandomGenerator().GetValue();

  ++general_data_.ant_count;
}

Ant::~Ant() { --general_data_.ant_count; }

void Ant::Update(float delta_time) {
  ant_state_->Decide(delta_time);
  AvoidObstacle();
  Move(delta_time);
}

void Ant::Interact(WorldData& world_data, float delta_time) {
  ant_state_->Interact(world_data, delta_time);
  pheromone_data_.pheromone_strength *= (1 - general_data_.pheromone_decay * delta_time);
}

Sensor Ant::GetSensor() {
  ant_state_->GetState();
  return {ant_state_, general_data_, movement_data_, sensor_data_};
}

void Ant::ResetPheromone() {
  pheromone_data_.pheromone_strength = general_data_.pheromone_capacity;
}

void Ant::TakeFood() {
  food_data_.carry_amount = sensor_data_.food_source.value()
      ->GetFood(general_data_.max_capacity - food_data_.carry_amount);
}

void Ant::StoreFood() {
  sensor_data_.hive_storage.value()->StoreFood(food_data_.carry_amount);
  food_data_.carry_amount = 0;
}

void Ant::AlertColony() {
  sensor_data_.hive_storage.value()->Alert(pheromone_data_.pheromone_strength);
}

void Ant::SetTarget(Ant& ant) {
  sensor_data_.target_ant = &ant;
}

void Ant::Stop() {
  movement_data_.velocity[0] = movement_data_.velocity[1] = 0.f;
}

void Ant::InitiateFight() {
  if (ant_state_->GetState() != StateType::Defending && ant_state_->GetState() != StateType::AttackEnemy) {
    ChangeState<DefendingState>();
  }
}

void Ant::ReceiveDamage(int damage) {
  fight_data_.health -= damage;
}

void Ant::ChangeState(StateType new_state) {
  switch (new_state) {
    case StateType::None: {
      throw std::runtime_error("invalid state");
    }
    case StateType::FoodSearch: {
      ChangeState<FoodSearchState>();
      break;
    }
    case StateType::HomeSearch: {
      ChangeState<HomeSearchState>();
      break;
    }
    case StateType::RepellentPheromone: {
      ChangeState<RepellentPheromoneState>();
      break;
    }
    case StateType::AlertColony: {
      ChangeState<AlertColonyState>();
      break;
    }
    case StateType::EnemySearch: {
      ChangeState<EnemySearchState>();
      break;
    }
    case StateType::AttackEnemy: {
      ChangeState<AttackEnemyState>();
      break;
    }
    case StateType::Defending: {
      ChangeState<DefendingState>();
      break;
    }
    case StateType::Scouting: {
      ChangeState<ScoutingState>();
      break;
    }
    case StateType::Idle: {
      ChangeState<AtHomeState>();
      break;
    }
  }
}

void Ant::Move(float delta_time) {
  movement_data_.random_cooldown += delta_time;
  if (movement_data_.random_cooldown >= general_data_.wander_cooldown) {
    movement_data_.target_direction =
        Normalised(movement_data_.target_direction + 0.5f * RandomGenerator().GetVector2f());
    movement_data_.random_cooldown -= general_data_.wander_cooldown;
  }

  auto acceleration =
      general_data_.steer_speed * (movement_data_.target_direction * general_data_.max_speed - movement_data_.velocity);
  movement_data_.velocity += acceleration * delta_time;

  if (movement_data_.velocity.SquaredLength() > std::pow(general_data_.max_speed, 2)) {
    movement_data_.velocity.SetMagnitude(general_data_.max_speed);
  }

  movement_data_.position += movement_data_.velocity * delta_time;
}

void Ant::AvoidObstacle() {
  if (sensor_data_.is_wall_ahead) {
    for (size_t i = 0; i < 2; ++i) {  /// for both dimension
      if (sensor_data_.wall_data[i] > 0 && movement_data_.velocity[i] > 0 ||
          sensor_data_.wall_data[i] < 0 && movement_data_.velocity[i] < 0) {
        movement_data_.velocity[i] = -movement_data_.velocity[i];
        movement_data_.target_direction[i] = -movement_data_.target_direction[i];
      }
    }
  }
}

//template <>
//void Ant::ChangeState<FoodSearchState>(...) {
//  ant_state_ = std::make_unique<FoodSearchState>(*this);
//}
//
//template <>
//void Ant::ChangeState<HomeSearchState>(...) {
//  ant_state_ = std::make_unique<HomeSearchState>(*this);
//}
//
//template <>
//void Ant::ChangeState<RepellentPheromoneState>(...) {
//  ant_state_ = std::make_unique<RepellentPheromoneState>(*this);
//}
//
//template <>
//void Ant::ChangeState<AlertColonyState>(...) {
//  ant_state_ = std::make_unique<AlertColonyState>(*this);
//}
//
//template <>
//void Ant::ChangeState<EnemySearchState>(...) {
//  ant_state_ = std::make_unique<EnemySearchState>(*this);
//}
//
//template <>
//void Ant::ChangeState<AttackEnemyState>(...) {
//  ant_state_ = std::make_unique<AttackEnemyState>(*this);
//}
//
//template <>
//void Ant::ChangeState<DefendingState>(...) {
//  ant_state_ = std::make_unique<DefendingState>(*this);
//}
//
//template <>
//void Ant::ChangeState<ScoutingState>(...) {
//  ant_state_ = std::make_unique<ScoutingState>(*this);
//}
//
//template <>
//void Ant::ChangeState<AtHomeState>(...) {
//  ant_state_ = std::make_unique<AtHomeState>(*this);
//}
