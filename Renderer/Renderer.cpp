//
// Created by Artem Novikov on 12.09.2022.
//

#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& window, const Vector2i& size)
    : window_(window), view_(window.getDefaultView()), tile_map_(sf::Quads, 4 * size[0] * size[1]) {
  for (int x = 0; x < size[0]; ++x) {
    for (int y = 0; y < size[1]; ++y) {
      size_t index = 4 * (x * size[1] + y);

      tile_map_[index + 0].position = sf::Vector2f(float(x), float(y)) * kUnitLength;
      tile_map_[index + 1].position = sf::Vector2f(float(x + 1), float(y)) * kUnitLength;
      tile_map_[index + 2].position = sf::Vector2f(float(x + 1), float(y + 1)) * kUnitLength;
      tile_map_[index + 3].position = sf::Vector2f(float(x), float(y + 1)) * kUnitLength;

      tile_map_[index + 0].color = tile_map_[index + 1].color =
      tile_map_[index + 2].color = tile_map_[index + 3].color = sf::Color(121, 96, 76); /// brown
    }
  }
}

void Renderer::RegisterShift(const Vector2f& shift) {   /// TODO
  view_.move(shift[0], shift[1]);
}

void Renderer::RegisterScale(const Vector2f& center, float scale_factor) {  /// TODO
  view_.zoom(scale_factor);
}

void Renderer::Render(const World& world) {
  const auto& world_data = world.GetWorldData();

  Render(world_data.map_);

  for (const auto& food : world_data.food_map_) {
    Render(food);
  }

  for (const auto& colony : world.GetColonies()) {
    Render(colony);
  }

  for (const auto& ant : world.GetAnts()) {
    Render(*ant.object);
  }
}

void Renderer::Render(const Map& map) {
  for (size_t x = 0; x < map.GetWidth(); ++x) {
    for (size_t y = 0; y < map.GetHeight(); ++y) {
      if (!map.HasObstacle(x, y)) {
        size_t index = 4 * (x * map.GetHeight() + y);

        auto enemy_pheromone =
            map.GetPheromone(0, x, y, PheromoneType::Enemy); // + map.GetPheromone(1, x, y, PheromoneType::Enemy);
        auto home_pheromone =
            map.GetPheromone(0, x, y, PheromoneType::Home); // + map.GetPheromone(1, x, y, PheromoneType::Home);
        auto food_pheromone =
            map.GetPheromone(0, x, y, PheromoneType::Food); // + map.GetPheromone(1, x, y, PheromoneType::Food);
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
  auto circle = sf::CircleShape(value.GetSize() * kUnitLength);
  circle.setPosition(sf::Vector2f(value.GetPosition()[0] - value.GetSize(),
                                  value.GetPosition()[1] - value.GetSize()) * kUnitLength);
  circle.setFillColor(color);
  window_.draw(circle);
}

void Renderer::Render(const Colony& colony) {
  /// TODO colour
  for (const auto& hive : colony.GetHives()) {
    Render(hive);
  }
}

void Renderer::Render(const Hive& hive) {
  auto color = sf::Color::Yellow;
  RenderCircle(hive, color);
}

void Renderer::Render(const Ant& ant) {
  sf::Color color;
  if (ant.GetColonyIndex() == 0) {  /// TODO color
    color = sf::Color::Red;
  } else {
    color = sf::Color::White;
  }
  RenderCircle(ant, color);
}
