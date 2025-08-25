#pragma once

#include <memory>

#include "ArgParser/ArgParser.hpp"

class Application {
public:
    Application();
    bool Run(int argc, char** argv);

private:
    ArgumentParser::ArgParser arg_parser_;
    ArgumentParser::Argument<std::string>& tags_;
};
