#ifndef GLOBAL_H
#define GLOBAL_H

#include <future>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

using namespace std::string_literals;

#define panic(msg) throw std::runtime_error(msg)

#endif  // GLOBAL_H
