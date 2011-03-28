#define HUMMSTRUMM_ENGINE_SOURCE

#include "hummstrummengine.hpp"

#include <iostream>


using namespace hummstrumm::engine::math;

int
main()
{
  Vector4D<float> *vector4DTest = new Vector4D<float>[2];

  delete []  vector4DTest;
  return 0;
}
