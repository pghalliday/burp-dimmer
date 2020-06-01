#ifndef Config_ActionType_hpp
#define Config_ActionType_hpp

namespace Config {

  enum class ActionType {
    NETWORK_MANAGER_DESERIALIZE,
    NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT,
    NETWORK_MANAGER_NEXT_PERM_MODE,
    NETWORK_MANAGER_SET_PERM_MODE,
    NETWORK_MANAGER_SET_TEMP_MODE
  };

}

#endif
