#pragma once

#include <Redux/Store.hpp>
#include <Redux/ReducerMap.hpp>
#include <ArduinoJson.h>
#include <Json/Serializer.hpp>
#include "Config/ActionType.hpp"
#include "Config/Network.hpp"
#include "Config/Light.hpp"

namespace Config {

    class State : public Json::Serializer {
      public:
        const Network::State * network;
        const Light::State * light;
        State(const State * previous, const JsonObject & object);
        State(const State * previous, const Action & action);
        void serialize(JsonObject & object) const override;
    };
    
    using Reducer = Redux::ReducerMap<State, ActionType, JsonObject>;
    using Store = Redux::Store<State, ActionType, JsonObject>;

    extern const Reducer reducer;
    extern Store store;

}
