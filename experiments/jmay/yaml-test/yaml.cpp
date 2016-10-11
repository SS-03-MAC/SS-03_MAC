
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include "yaml.h"

int main(int argc, char *argv[]) {
    YAML::Node config = YAML::LoadFile("config.yaml");

    //if (config["lastLogin"]) {
        //std::cout << "Last logged in: " << config["lastLogin"].as<DateTime>() << "\n";
    //}

    const std::string username = config["username"].as<std::string>();
    const std::string password = config["password"].as<std::string>();


    std::ofstream fout("config.yaml");
    fout << config;

}