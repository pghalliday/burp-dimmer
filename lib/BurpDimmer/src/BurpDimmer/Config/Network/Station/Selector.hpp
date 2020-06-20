#pragma once

#include <CppRedux/Selector.hpp>
#include "../Selector.hpp"
#include "../State.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        using Selector = CppRedux::Selector<Network::Selector, Network::State, State>;

      }
    }
  }
}
