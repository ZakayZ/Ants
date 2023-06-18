//
// Created by Artem Novikov on 18.06.2023.
//

#ifndef ANTS_NEW_RENDER_RENDERER_H_
#define ANTS_NEW_RENDER_RENDERER_H_

#include <SFML/Graphics.hpp>
#include "world/World.h"


class Renderer {
 public:
  Renderer(int width, int height);

  bool Display(const World& world);

  void RegisterShift(const Vector2f& shift);

  void RegisterScale(const Vector2f& center, float scale_factor);

 private:
  static const float UnitLength;

  void Render(const World& world);

  void Render(const ObjectMap& map, const PheromoneMap& pheromone_map);

  void Render(const FoodSource& food_source);

  void Render(const Colony& colony);

  void Render(const Hive& hive);

  void Render(const Ant& ant);

  template <class T>
  void RenderCircle(const T& value, sf::Color color);

  sf::RenderWindow window_;
  sf::View view_;
  sf::VertexArray tile_map_;
};

#endif //ANTS_NEW_RENDER_RENDERER_H_
