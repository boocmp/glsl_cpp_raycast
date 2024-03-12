#include "ray_castring.h"
#include <iostream>

#include <thread>

namespace ray {

struct vec3 {
  vec3(float x, float y, float z) : data{x, y, z} {}
  float data[3];
};

struct CanvasEnumerator {
  struct iterator {
    const CanvasEnumerator &ce;
    size_t x, y;

    iterator(const CanvasEnumerator &ce, size_t x, size_t y)
        : ce(ce), x(x), y(y) {}

    iterator &operator++() {
      if (x + 1 < ce.w) {
        ++x;
      } else {
        x = 0;
        ++y;
      }
      return *this;
    }

    vec3 operator*() const {
      return vec3(2.0f * float(x) / (ce.w - 1) - 1,
                  2.0f * float(y) / (ce.h - 1), 0.0f);
    }

    bool operator!=(const iterator &o) const { return x != o.x && y != o.y; }
  };

  CanvasEnumerator(size_t w, size_t h) : w(w), h(h) {}

  iterator begin() const { return iterator(*this, 0, 0); }

  iterator end() const { return iterator(*this, w, h); }

  size_t w, h;
};

RayCaster::~RayCaster() = default;

void RayCaster::UpdateUI() {
  if (ImGui::ColorEdit3("Color", color_.data())) {
    Process();
  }
}

void RayCaster::Process() {
  /*for (size_t x = 0; x < canvas().width(); ++x) {
    for (size_t y = 0; y < canvas().height(); ++y) {
      canvas().SetPixel(
          x, y, sf::Color(x * color_[0], y * color_[1], 255 * color_[2]));
    }
  }*/
  for (auto v : CanvasEnumerator(canvas().width(), canvas().height())) {
    std::cout << v.data[0] << " " << v.data[1] << std::endl;
  }
  Show();
}

} // namespace ray