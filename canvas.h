#pragma once

#include <SFML/Graphics/Color.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <functional>
#include <thread>

namespace ray {

class Canvas {
public:
  Canvas(std::vector<sf::Color> &data, size_t width, size_t height);

  void SetPixel(size_t x, size_t y, const sf::Color &color);
  size_t width() const;
  size_t height() const;

private:
  std::vector<sf::Color> &data_;
  size_t width_;
  size_t height_;
};

class BaseRayCasting {
public:
  BaseRayCasting(Canvas &canvas, std::function<void()> show);
  virtual ~BaseRayCasting();

  Canvas &canvas();
  void Show();

  virtual void UpdateUI() = 0;
  virtual void Process() = 0;

private:
  Canvas &canvas_;
  std::function<void()> show_;
};

} // namespace ray
