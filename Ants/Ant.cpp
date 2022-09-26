//
// Created by Artem Novikov on 03.09.2022.
//

#include "World/WorldData.h"
#include "World/Sensor.h"
#include "Ant.h"

Ant::Ant(const Vector2f& position, const GeneralData& general_data)
    : movement_data_(position), general_data_(general_data), pheromone_data_(general_data.pheromone_capacity),
      fight_data_(general_data.max_health) {
  movement_data_.target_direction = RandomGenerator().GetVector2f();
  movement_data_.random_cooldown = general_data.wander_cooldown * RandomGenerator().GetValue();

  ++general_data_.ant_count;
}

Ant::~Ant() { --general_data_.ant_count; }

void Ant::Update(float delta_time) {
  ant_state_->Decide(delta_time);
  ChangeState();
  AvoidObstacle();
  Move(delta_time);
}

void Ant::Interact(WorldData& world_data, float delta_time) {
  ant_state_->Interact(world_data, delta_time);
  pheromone_data_.pheromone_strength *= (1 - general_data_.pheromone_decay * delta_time);
}

Sensor Ant::GetSensor() {
  return {ant_state_, general_data_, movement_data_, sensor_data_};
}

void Ant::InitiateFight() {
  if (ant_state_->GetState() != StateType::Defending && ant_state_->GetState() != StateType::AttackEnemy) {
    ant_state_ = std::make_unique<DefendingState>(ant_state_->GetState(), sensor_data_, pheromone_data_,
                                                  movement_data_, general_data_);
  }
}

void Ant::ReceiveDamage(int damage) {
  fight_data_.health -= damage;
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

void Ant::ChangeState() {
  switch (ant_state_->StateTransition()) {
    case StateType::None: { break; }

    case StateType::FoodSearch: {
      ant_state_ = std::make_unique<FoodSearchState>(food_data_, sensor_data_, pheromone_data_,
                                                     movement_data_, general_data_);
      break;
    }

    case StateType::HomeSearch: {
      ant_state_ = std::make_unique<HomeSearchState>(sensor_data_, pheromone_data_, movement_data_, general_data_);
      break;
    }

    case StateType::RepellentPheromone: {
      ant_state_ =
          std::make_unique<RepellentPheromoneState>(sensor_data_, pheromone_data_, movement_data_, general_data_);
      break;
    }

    case StateType::AlertColony: {
      ant_state_ =
          std::make_unique<AlertColonyState>(sensor_data_, pheromone_data_, movement_data_, general_data_);
      break;
    }

    case StateType::EnemySearch: {
      ant_state_ =
          std::make_unique<EnemySearchState>(sensor_data_, pheromone_data_, movement_data_, general_data_);
      break;
    }

    case StateType::AttackEnemy: {
      ant_state_ =
          std::make_unique<AttackEnemyState>(sensor_data_, pheromone_data_, movement_data_, general_data_);
      break;
    }

    case StateType::Defending: {
      ant_state_ = std::make_unique<DefendingState>(ant_state_->GetState(), sensor_data_, pheromone_data_,
                                                    movement_data_, general_data_);
      break;
    }
    case StateType::Scouting: {
      ant_state_ = std::make_unique<ScoutingState>(sensor_data_, pheromone_data_, movement_data_, general_data_);
      break;
    }

    case StateType::Idle: {
      ant_state_ = std::make_unique<AtHomeState>(ant_state_->GetState(), food_data_, sensor_data_, pheromone_data_,
                                                 movement_data_, general_data_);
      break;
    }
  }
}
