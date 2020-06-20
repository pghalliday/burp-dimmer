#pragma once

#include <CppRedux/Selector.hpp>
#include "../Store.hpp"
#include "../State.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      using Selector = CppRedux::Selector<Store, Config::State, State>;

    }
  }
}
