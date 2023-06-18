//
// Created by Artem Novikov on 09.05.2023.
//

#include "Ant.h"
#include "utils/Randomizer.h"
#include "world/World.h"

void Ant::Update(World& world, Time dt) {
  brain_->Decide(world, dt);
  AvoidCollision(world, dt); /// it is simular to avoid collision state
  Move(dt);
}

BoundaryBox2<Float> Ant::VisibleRange() const {
  auto delta = Vector2<Float>(general_data_.visible_range, general_data_.visible_range);
  return {move_data_.position - delta, move_data_.position + delta};
}

BoundaryBox2<Float> Ant::SensitiveRange() const {
  auto delta = Vector2<Float>(general_data_.pheromone_range, general_data_.pheromone_range);
  return {move_data_.position - delta, move_data_.position + delta};
}

void Ant::LayPheromone(World& world, Time dt) {
  return world.GetPheromoneMap().AddPheromone(move_data_.position, dt, pheromone_gland_.GetPheromoneType());
}

void Ant::Move(Time dt) {
  random_walk_.Update(dt);
  if (random_walk_.Ready()) {
    move_data_.target_direction =
        Normalised(move_data_.target_direction + Random::IsotropicVector<Float, 2>());
    random_walk_.Use();
  }

  auto acceleration =
      general_data_.steer_speed * (move_data_.target_direction * general_data_.max_speed - move_data_.velocity);
  move_data_.velocity += acceleration * dt;

  if (move_data_.velocity.SquaredLength() > std::pow(general_data_.max_speed, 2)) {
    move_data_.velocity.SetMagnitude(general_data_.max_speed);
  }

  move_data_.position += move_data_.velocity * dt;
}

void Ant::AvoidCollision(World& world, Time dt) {
  auto wall_info = world.GetObjectMap().WallDistances(move_data_.position);
  // TODO avoidance
}
