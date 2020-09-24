#pragma once

#include <BurpTree/Factory.hpp>
#include "Status.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        class Factory : public BurpTree::Factory<State, Status> {

          public:

            void setDefaultHostname(const char * defaultHostname);
            bool deserialize(const JsonVariant & serialized) override ;
            bool createDefault() override;

          private:

            const char * _defaultHostname;

        };

      }
    }
  }
}