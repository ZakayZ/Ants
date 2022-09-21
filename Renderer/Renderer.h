//
// Created by Artem Novikov on 12.09.2022.
//

#ifndef ANTS__RENDERER_H_
#define ANTS__RENDERER_H_

#include <SFML/Graphics.hpp>
#include <memory>

#include "BoundaryBox.h"
#include "Transform.h"

#include "World/World.h"
#include "World/Colony.h"
#include "World/Hive.h"
#include "Ants/Ant.h"

static const float kUnitLength = 4.f;

class Renderer {
 public:
  Renderer(sf::RenderWindow& window, const Vector2i& size);

  void RegisterShift(const Vector2f& shift);

  void RegisterScale(const Vector2f& center, float scale_factor);

  void Render(const World& world);

 private:
  void Render(const TileMap& map);

  void Render(const PheromoneMap& pheromone_map);

  void Render(const FoodSource& food_source);

  template <class T>
  void RenderCircle(const T& value, sf::Color color);

  void Render(const Colony& colony);

  void Render(const Hive& hive);

  void Render(const Ant& ant);

  sf::RenderWindow& window_;
  sf::VertexArray tile_map_;
  sf::View view_;
};

#endif //ANTS__RENDERER_H_
