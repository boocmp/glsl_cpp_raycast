#include "canvas.h"

namespace ray {

Canvas::Canvas(std::vector<sf::Color> &data, size_t width, size_t height)
    : data_(data), width_(width), height_(height) {}

void Canvas::SetPixel(size_t x, size_t y, const sf::Color &color) {
  data_[x * height_ + y] = color;
}

size_t Canvas::width() const { return width_; }

size_t Canvas::height() const { return height_; }

//---------------------------------------------------------------------------

BaseRayCasting::BaseRayCasting(Canvas &canvas, std::function<void()> show)
    : canvas_(canvas), show_(std::move(show)) {}

BaseRayCasting::~BaseRayCasting() = default;

Canvas &BaseRayCasting::canvas() { return canvas_; }

void BaseRayCasting::Show() { show_(); }

} // namespace ray
