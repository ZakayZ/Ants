//
// Created by Artem Novikov on 03.09.2022.
//

#include "Ant.h"

Ant::Ant(const Vector2f& position, size_t colony_index, const GeneralData& general_data, float pheromone_initial)
    : movement_data_(position), pheromone_data_(pheromone_initial),
      ant_data_(colony_index), general_data_(general_data) {
  movement_data_.target_direction = RandomGenerator().GetVector2f();
  movement_data_.random_cooldown = general_data.wander_cooldown * RandomGenerator().GetValue();

  ++general_data_.ant_count;
}

Ant::~Ant() { --general_data_.ant_count; }

void Ant::Update(float delta_time) {
  ant_state_->Decide();
  ChangeState();
  AvoidObstacle();
  Move(delta_time);
}

void Ant::Interact(WorldData& world_data, float delta_time) {
  ant_state_->Interact(world_data, delta_time);
  pheromone_data_.pheromone_strength *= (1 - general_data_.pheromone_decay * delta_time);  /// TODO better solution
}

Sensor Ant::GetSensor() {
  return {ant_state_, general_data_, movement_data_, sensor_data_};
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
      ant_state_ = std::make_unique<FoodSearchState>(sensor_data_, movement_data_, pheromone_data_);
      pheromone_data_.pheromone_strength = general_data_.pheromone_capacity;
      break;
    }
    case StateType::GrabFood: {
      ant_state_ =
          std::make_unique<GrabFoodState>(sensor_data_, movement_data_,
                                          food_data_, pheromone_data_, general_data_);
      break;
    }
    case StateType::HomeSearch: {
      ant_state_ = std::make_unique<HomeSearchState>(sensor_data_, movement_data_, pheromone_data_);
      pheromone_data_.pheromone_strength = general_data_.pheromone_capacity;
      break;
    }
    case StateType::StoreFood: {
      ant_state_ = std::make_unique<StoreFoodState>(sensor_data_, movement_data_,
                                                    food_data_, pheromone_data_, general_data_);
      break;
    }
    case StateType::RepellentPheromone: {
      ant_state_ = std::make_unique<RepellentPheromoneState>(sensor_data_, movement_data_,
                                                             pheromone_data_, general_data_);
      break;
    }
  }
}
