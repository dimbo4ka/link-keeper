#pragma once

#include <cstddef>
#include <string>
#include <vector>

class Bookmark {
public:
    Bookmark(std::string title, std::string url_, std::vector<std::string> tags_, std::size_t id) {}

private:
    std::string title_;
    std::string url_;
    std::vector<std::string> tags_;
    std::size_t id_;
};