#pragma once

#include <cstddef>
#include <string>
#include <vector>

class Bookmark {
private:
    class Builder;

public:
    Bookmark(Builder builder);

    const std::string& title() const;
    const std::string& url() const;
    const std::vector<std::string> tags() const;
    std::size_t id() const;

private:
    std::string title_;
    std::string url_;
    std::vector<std::string> tags_;
    std::size_t id_;

    class Builder {
    public:
        Builder& SetTitle(std::string title);
        Builder& SetUrl(std::string url);
        Builder& SetTags(std::vector<std::string> tags);
        Builder& SetId(std::size_t id);

        std::string& title();
        std::string& url();
        std::vector<std::string>& tags();
        std::size_t id();

    private:
        std::string title_;
        std::string url_;
        std::vector<std::string> tags_;
        std::size_t id_;
    };
};