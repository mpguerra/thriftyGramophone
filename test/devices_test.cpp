#include "gtest/gtest.h"
#include "../src/devices.hpp"

class DevicesTest : public ::testing::Test {
};

class NullDevice : public ThriftyGramophone::Device {
  int play(std::string uri) { return 0; }
};

TEST_F(DevicesTest, TestUri) {
  ThriftyGramophone::DeviceRegistry reg;
  reg.register_schema("foobar", new NullDevice());
  
  ThriftyGramophone::Device* d = reg.get_device_for_URI("foobar:adfadf");
  ASSERT_TRUE(d != NULL);

  d = reg.get_device_for_URI("barfoo:adfadf");
  ASSERT_TRUE(d == NULL);

  d = reg.get_device_for_URI("fooba"); // not valid URI
  ASSERT_TRUE(d == NULL);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
