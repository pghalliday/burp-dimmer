#include "../../Util/Debug.hpp"
#include "Actions.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      void deserialize(const JsonObject & object, f_onParams onParams) {
        if (!object.isNull()) {
          if (object.containsKey(levelsField)) {
            if (object.containsKey(saveStateDelayField)) {
              if (object.containsKey(offLevelField)) {
                JsonArray array = object[levelsField].as<JsonArray>();
                if (array) {
                  auto size = array.size();
                  if (size > maxLevels) {
                    BURP_DEBUG_INFO("Error::maxLevels");
                    return onParams(Error::maxLevels, nullptr);
                  }
                  if (size == 0) {
                    BURP_DEBUG_INFO("Error::minLevels");
                    return onParams(Error::minLevels, nullptr);
                  }
                  auto index = 0;
                  Levels levels;
                  for(JsonVariant v : array) {
                    if (!v.is<unsigned char>()) {
                      BURP_DEBUG_INFO("Error::invalidLevels");
                      return onParams(Error::invalidLevels, nullptr);
                    }
                    const unsigned char level = v.as<unsigned char>();
                    if (level == 0) {
                      BURP_DEBUG_INFO("Error::levelZero");
                      return onParams(Error::levelZero, nullptr);
                    }
                    levels[index++] = level;
                  }
                  if (!object[saveStateDelayField].is<unsigned long>()) {
                    BURP_DEBUG_INFO("Error::invalidSaveStateDelay");
                    return onParams(Error::invalidSaveStateDelay, nullptr);
                  }
                  unsigned long saveStateDelay = object[saveStateDelayField];
                  if (!object[offLevelField].is<unsigned char>()) {
                    BURP_DEBUG_INFO("Error::invalidOffLevel");
                    return onParams(Error::invalidOffLevel, nullptr);
                  }
                  unsigned char offLevel = object[offLevelField];
                  if (offLevel >= size) {
                    BURP_DEBUG_INFO("Error::offLevelOutOfRange");
                    return onParams(Error::offLevelOutOfRange, nullptr);
                  }
                  const Params params = {
                    levels,
                    saveStateDelay,
                    offLevel
                  };
                  return onParams(Error::noError, &params);
                }
                BURP_DEBUG_INFO("Error::notAnArray");
                return onParams(Error::notAnArray, nullptr);
              }
              BURP_DEBUG_INFO("Error::noOffLevel");
              return onParams(Error::noOffLevel, nullptr);
            }
            BURP_DEBUG_INFO("Error::noSaveStateDelay");
            return onParams(Error::noSaveStateDelay, nullptr);
          }
          BURP_DEBUG_INFO("Error::noLevels");
          return onParams(Error::noLevels, nullptr);
        }
        BURP_DEBUG_INFO("Error::noObject");
        return onParams(Error::noObject, nullptr);
      }

    }
  }
}