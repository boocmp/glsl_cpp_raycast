#include "../canvas.h"

#include <array>

namespace ray {

class RayCaster : public BaseRayCasting {
public:
  using BaseRayCasting::BaseRayCasting;
  ~RayCaster() override;

  void UpdateUI() override;
  void Process() override;

private:
  std::array<float, 3> color_ = {0.5f, 0.33f, 0.33f};
};

} // namespace ray