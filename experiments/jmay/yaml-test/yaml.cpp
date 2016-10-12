
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include "yaml.h"

int main(int argc, char *argv[]) {
  try {
    YAML::Node config = YAML::LoadFile("test.yaml");

    //for (int i = 0; i < config.size(); i++) {
    std::cout << config["items"][0]["descrip"] << std::endl;
    //}
  } catch (const std::exception &ex) {
    std::cout << "error" << ex.what() << std::endl;
  }

}