#pragma once

#include <string>

enum class OptimismFunc {
  NONE,
  LINEAR,
  SIGMOID,
  EXPONENTIAL
};

inline std::string OptimismFuncToString(OptimismFunc optimismFunc) {
  switch (optimismFunc) {
    case OptimismFunc::NONE:
      return "NONE";
    case OptimismFunc::LINEAR:
      return "LINEAR";
    case OptimismFunc::SIGMOID:
      return "SIGMOID";
    case OptimismFunc::EXPONENTIAL:
      return "EXPONENTIAL";
  }
}

