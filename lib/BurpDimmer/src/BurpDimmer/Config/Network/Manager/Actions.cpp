#include "../../../Util/Debug.hpp"
#include "Actions.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        void deserialize(const JsonObject & object, f_onParams onParams) {
          if (!object.isNull()) {
            if (object.containsKey(modeField)) {
              if (object.containsKey(accessPointTimeoutField)) {
                const JsonVariant vapt = object[accessPointTimeoutField];
                if (!vapt.is<unsigned long>()) {
                  BURP_DEBUG_INFO("Error::invalidAccessPointTimeout");
                  return onParams(Error::invalidAccessPointTimeout, nullptr);
                }
                const unsigned long accessPointTimeout = vapt.as<unsigned long>();
                const JsonVariant vm = object[modeField];
                if (!vm.is<const char *>()) {
                  BURP_DEBUG_INFO("Error::invalidMode");
                  return onParams(Error::invalidMode, nullptr);
                }
                const char * modeString = vm.as<const char *>();
                for (size_t i = 0 ; i < PermMode::count; i++) {
                  if (strcmp(modeString, permModeNames[i]) == 0) {
                    const Params params = {
                      static_cast<PermMode>(i),
                      defaultTempMode,
                      defaultTempModeActive,
                      accessPointTimeout
                    };
                    return onParams(Error::noError, &params);
                  }
                }
                BURP_DEBUG_INFO("Error::unknownMode");
                return onParams(Error::unknownMode, nullptr);
              }
              BURP_DEBUG_INFO("Error::noAccessPointTimeout");
              return onParams(Error::noAccessPointTimeout, nullptr);
            }
            BURP_DEBUG_INFO("Error::noMode");
            return onParams(Error::noMode, nullptr);
          }
          BURP_DEBUG_INFO("Error::noObject");
          return onParams(Error::noObject, nullptr);
        }

        void nextPermMode(const State * previous, f_onParams onParams) {
          const Params params = {
            static_cast<PermMode>((previous->permMode + 1) % PermMode::count),
            previous->tempMode,
            false,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

        void startTempAccessPoint(const State * previous, f_onParams onParams) {
          const Params params = {
            previous->permMode,
            TempMode::ACCESS_POINT,
            true,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

        void startWpsConfig(const State * previous, f_onParams onParams) {
          const Params params = {
            previous->permMode,
            TempMode::WPS_CONFIG,
            true,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

        void stopTempMode(const State * previous, f_onParams onParams) {
          const Params params = {
            previous->permMode,
            previous->tempMode,
            false,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

        void setNormalMode(const State * previous, f_onParams onParams) {
          const Params params = {
            PermMode::NORMAL,
            previous->tempMode,
            false,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

      }
    }
  }
}
