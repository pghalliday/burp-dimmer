#include <Arduino.h>
#include <BurpDebug.hpp>
#include "Light.hpp"


namespace BurpDimmer {
  namespace Components {
    namespace Light {

      Instance::Instance(int pin) :
        _pin(pin)
      {}

      void Instance::setup(const State * state) {
        pinMode(_pin, OUTPUT);
        update(state);
      }

      void Instance::update(const State * state) {
        if (state->on) {
          analogWrite(_pin, state->pwm);
        } else {
          digitalWrite(_pin, LOW);
        }
      }

    }
  }
}
