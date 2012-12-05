#ifndef TG_DEVICE_PLUGIN_H
#define TG_DEVICE_PLUGIN_H

#include <tr1/unordered_map>
#include <string>

namespace ThriftyGramophone {
  class Device {
  public:
    virtual int play(std::string uri) = 0;
  };

  class DeviceRegistry {
  public:
    DeviceRegistry();
    void register_schema(std::string schema, Device* dev);
    Device* get_device_for_URI(std::string uri);
    void shutdown();
  private:
    std::tr1::unordered_map<std::string, Device*> devices;
  };
}
#endif
