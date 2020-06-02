#pragma once

#include <ArduinoJson.h>
#include <Redux/Action.hpp>
#include "../../../ActionType.hpp"
#include "./State.hpp"

namespace Config {
  namespace Network {
    namespace Station {
      namespace Actions {

        class Deserialize: public Redux::Action<ActionType> {
          public:
            const JsonObject & object;
            Deserialize(const JsonObject & object);
        };

      }
    }
  }
}
