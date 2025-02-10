#pragma once

#include <string>

enum class OptimismFunc {
  NONE, LINEAR, CLAMPED, SIGMOID, EXPONENTIAL 
};

inline std::string OptimismFuncToString(OptimismFunc optimismFunc) {
  switch (optimismFunc) {
    case OptimismFunc::NONE:
      return "NONE";
    case OptimismFunc::LINEAR:
      return "LINEAR";
    case OptimismFunc::CLAMPED:
      return "CLAMPED";
    case OptimismFunc::SIGMOID:
      return "SIGMOID";
    case OptimismFunc::EXPONENTIAL:
      return "EXPONENTIAL";
  }
}

