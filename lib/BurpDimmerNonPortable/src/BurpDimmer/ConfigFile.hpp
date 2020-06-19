#pragma once

#include <functional>
#include <CppRedux/Subscriber.hpp>
#include <BurpDimmer/Json/withDoc.hpp>
#include <BurpDimmer/Config.hpp>
#include "Json/File.hpp"

namespace BurpDimmer {

  template <class JsonDocumentClass>
  class ConfigFile : public CppRedux::Subscriber {

    public:

      ConfigFile(const char * path) :
        _file(path)
      {}

      void init() {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          _file.read(doc);
          Config::init(doc.as<JsonObject>());
        });
      }

      void notify() override {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          JsonObject object = doc.as<JsonObject>();
          Config::store.getState()->serialize(object);
          _file.write(doc);
        });
      }

    private:

      const Json::File _file;

  };

  using ConfigFileDocumentClass = StaticJsonDocument<1024>;
  extern ConfigFile<ConfigFileDocumentClass> configFile;

}
