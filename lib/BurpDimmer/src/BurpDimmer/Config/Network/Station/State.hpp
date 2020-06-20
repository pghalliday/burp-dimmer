#pragma once

#include "../../../Json/Serializer.hpp"
#include "../../../Memory/Pair.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        constexpr char testField[] = "test";

        struct Params {
          const int test;
        };

        class State : public Json::Serializer {

          public:
            
            const int test;

            State(const Params * params);
            void serialize(JsonObject & object) const override;

        };

        using Memory = Memory::Pair<State, Params>;
        extern Memory memory;

      }
    }
  }
}