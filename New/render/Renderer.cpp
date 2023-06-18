//
// Created by Artem Novikov on 18.06.2023.
//

#include "Renderer.h"
#include "creature/ant/Ant.h"

const float Renderer::UnitLength = 6;

Renderer::Renderer(int width, int height)
    : window_(sf::VideoMode(width * Renderer::UnitLength, height * Renderer::UnitLength), "Ants"),
      view_(window_.getDefaultView()), tile_map_(sf::Quads, 4 * width * height) {
  for (int x = 0; x < width; ++x) {
    for (int y = 0; y < height; ++y) {
      size_t index = 4 * (x * height + y);

      tile_map_[index + 0].position = sf::Vector2f(float(x), float(y)) * UnitLength;
      tile_map_[index + 1].position = sf::Vector2f(float(x + 1), float(y)) * UnitLength;
      tile_map_[index + 2].position = sf::Vector2f(float(x + 1), float(y + 1)) * UnitLength;
      tile_map_[index + 3].position = sf::Vector2f(float(x), float(y + 1)) * UnitLength;

      tile_map_[index + 0].color = tile_map_[index + 1].color =
      tile_map_[index + 2].color = tile_map_[index + 3].color = sf::Color(121, 96, 76); /// brown
    }
  }
}

bool Renderer::Display(const World& world) {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
      return false;
    }
  }

  window_.clear();
  Render(world);
  window_.display();

  return window_.isOpen();
}

void Renderer::Render(const World& world) {
  Render(world.GetObjectMap(), world.GetPheromoneMap());

  for (const auto& food : world.GetFoodMap()) {
    Render(food);
  }

  for (const auto& hive : world.GetHiveMap()) {
    Render(hive);
  }

  for (const auto& creature : world.GetCreatureMap()) {
    Render(dynamic_cast<Ant&>(*creature));
  }
}

void Renderer::RegisterShift(const Vector2f& shift) {
  view_.move(shift[0], shift[1]);  /// TODO
}

void Renderer::RegisterScale(const Vector2f& center, float scale_factor) {
  view_.zoom(scale_factor);  /// TODO
}

void Renderer::Render(const ObjectMap& map, const PheromoneMap& pheromone_map) {
  for (size_t x = 0; x < map.GetWidth(); ++x) {
    for (size_t y = 0; y < map.GetHeight(); ++y) {
      if (map.Empty(x, y)) {
        size_t index = 4 * (x * map.GetHeight() + y);

        auto enemy_pheromone =
            pheromone_map.GetPheromone(0, x, y, PheromoneType::Enemy); // + map.GetPheromone(1, x, y, PheromoneType::Enemy);
        auto home_pheromone =
            pheromone_map.GetPheromone(0, x, y, PheromoneType::Home); // + map.GetPheromone(1, x, y, PheromoneType::Home);
        auto food_pheromone =
            pheromone_map.GetPheromone(0, x, y, PheromoneType::Food); // + map.GetPheromone(1, x, y, PheromoneType::Food);

        tile_map_[index + 0].color = tile_map_[index + 1].color =
        tile_map_[index + 2].color = tile_map_[index + 3].color = sf::Color::Magenta;
        uint8_t value = static_cast<uint8_t>(std::clamp(enemy_pheromone, 0.f, 1.f) * 255);
        if (home_pheromone < food_pheromone) {
          tile_map_[index + 0].color = tile_map_[index + 1].color =
          tile_map_[index + 2].color = tile_map_[index + 3].color = sf::Color::Cyan;
          value = static_cast<uint8_t>(std::clamp(food_pheromone, 0.f, 1.f) * 255);
        }
        if (enemy_pheromone < home_pheromone) {
          tile_map_[index + 0].color = tile_map_[index + 1].color =
          tile_map_[index + 2].color = tile_map_[index + 3].color = sf::Color::Blue;
          value = static_cast<uint8_t>(std::clamp(home_pheromone, 0.f, 1.f) * 255);
        }

        tile_map_[index + 0].color.a = tile_map_[index + 1].color.a =
        tile_map_[index + 2].color.a = tile_map_[index + 3].color.a = value;
      }
    }
  }
  window_.draw(tile_map_);
}

void Renderer::Render(const FoodSource& food_source) {
  sf::Color color = sf::Color::Green;
  RenderCircle(food_source, color);
}

template <class T>
void Renderer::RenderCircle(const T& value, sf::Color color) {
  auto circle = sf::CircleShape(value.GetSize() * UnitLength);
  circle.setPosition(sf::Vector2f(value.GetPosition()[0] - value.GetSize(),
                                  value.GetPosition()[1] - value.GetSize()) * UnitLength);
  circle.setFillColor(color);
  window_.draw(circle);
}

void Renderer::Render(const Colony& colony) {
  /// TODO colour
  for (const auto& hive : colony.GetHives()) {
    Render(*hive);
  }
}

void Renderer::Render(const Hive& hive) {
  auto color = sf::Color::Yellow;
  RenderCircle(hive, color);
}

void Renderer::Render(const Ant& ant) {
  sf::Color color;
  if (ant.GetGeneralData().colony_index == 0) {  /// TODO color
    color = sf::Color::Red;
  } else {
    color = sf::Color::White;
  }
  RenderCircle(ant, color);
}

