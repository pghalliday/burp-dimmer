#include "Actions.hpp"
#include "Deserialize.hpp"

namespace BurpDimmer {
  namespace Light {

    void deserialize(State::Creator & creator, const JsonObject & object, const Config * config, f_onState onState) {
      deserialize(object, config, [&](const Error error, const State::Params * params) {
          onState(creator.init(params));
      });
    }

  }
}
