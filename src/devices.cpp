#include "devices.hpp"

using namespace ThriftyGramophone;

DeviceRegistry::DeviceRegistry()
  : devices() {
}

void DeviceRegistry::register_schema(std::string schema, Device* dev) {
  devices[schema] = dev;
}

Device* DeviceRegistry::get_device_for_URI(std::string uri) {
  std::string::size_type colon = uri.find_first_of(':');
  if (colon == std::string::npos) {
    return NULL;
  }
  std::string schema = uri.substr(0, colon);
  return devices[schema];
}

void DeviceRegistry::shutdown() {
}
