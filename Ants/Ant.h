//
// Created by Artem Novikov on 27.08.2022.
//

#ifndef ANTS__ANT_H_
#define ANTS__ANT_H_

#include <random>

#include "Vector.h"
#include "Utils/RandomGenerator.h"

#include "AntType.h"

#include "AntData/GeneralData.h"
#include "AntData/MovementData.h"
#include "AntData/SensorData.h"
#include "AntData/PheromoneData.h"
#include "AntData/FoodData.h"
#include "AntData/FightData.h"

#include "States/FoodSearchState.h"
#include "States/HomeSearchState.h"
#include "States/RepellentPheromoneState.h"
#include "States/AlertColonyState.h"
#include "States/EnemySearchState.h"
#include "States/AttackEnemyState.h"
#include "States/DefendingState.h"
#include "States/ScoutingState.h"
#include "States/AtHomeState.h"
#include "States/LayingState.h"

class Sensor;
struct WorldData;

class Ant {
 public:
  Ant(const Vector2f& position, const GeneralData& general_data);

  virtual ~Ant() = 0;

  /// getters
  [[nodiscard]] const MovementData& GetMoveData() const { return movement_data_; }

  [[nodiscard]] const SensorData& GetSensorData() { return sensor_data_; }

  [[nodiscard]] const FoodData& GetFoodData() const { return food_data_; }

  [[nodiscard]] const GeneralData& GetGeneralData() const { return general_data_; }

  [[nodiscard]] const PheromoneData& GetPheromoneData() const { return pheromone_data_; }

  [[nodiscard]] const PheromoneData& GetFightData() const { return pheromone_data_; }

  [[nodiscard]] size_t GetColonyIndex() const { return general_data_.colony_index; }

  [[nodiscard]] float GetSize() const { return general_data_.ant_size; }

  [[nodiscard]] const Vector2f& GetPosition() const { return movement_data_.position; }

  [[nodiscard]] const Vector2f& GetTargetDirection() const { return movement_data_.target_direction; }

  [[nodiscard]] const Vector2f& GetFacingDirection() const { return movement_data_.velocity; }

  [[nodiscard]] bool IsAlive() const { return fight_data_.health > 0; }

  /// world interaction
  void Update(float delta_time);

  void Interact(WorldData& world_data, float delta_time);

  Sensor GetSensor();

  /// commands
  void ResetPheromone();

  void TakeFood();

  void StoreFood();

  void AlertColony();

  void SetTarget(Ant& ant);

  void Stop();

  /// ant interaction
  void InitiateFight();

  void ReceiveDamage(int damage);

  template <class State, typename... Args, bool Access = std::is_base_of_v<AntState, State>, typename = std::enable_if_t<Access>>
  void ChangeState(Args&&... args) {
    ant_state_ = std::make_unique<State>(*this, std::forward<Args>(args)...);
  }

  template <>
  void ChangeState<DefendingState>() {
    ant_state_ = std::make_unique<DefendingState>(*this, ant_state_->GetState());
  }

  void ChangeState(StateType new_state);

 protected:
  friend class AntState;

  void Move(float delta_time);

  void AvoidObstacle();

  MovementData movement_data_;
  SensorData sensor_data_;
  FoodData food_data_;
  const GeneralData& general_data_;
  PheromoneData pheromone_data_;
  FightData fight_data_;

  std::unique_ptr<AntState> ant_state_;
};

#endif //ANTS__ANT_H_
