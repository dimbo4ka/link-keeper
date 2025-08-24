#pragma once

#include <cstddef>
#include <string>
#include <vector>

class Bookmark {
public:
    class Builder;

    const std::string& title() const;
    const std::string& url() const;
    const std::vector<std::string>& tags() const;

    void Print() const;
    
private:
    std::string title_;
    std::string url_;
    std::vector<std::string> tags_;
    
    Bookmark(Builder builder);

public:
    class Builder {
    public:
        Builder& SetTitle(std::string title);
        Builder& SetUrl(std::string url);
        Builder& SetTags(std::vector<std::string> tags);
        Bookmark build();

        std::string& title();
        std::string& url();
        std::vector<std::string>& tags();

    private:
        std::string title_;
        std::string url_;
        std::vector<std::string> tags_;
    };
};
