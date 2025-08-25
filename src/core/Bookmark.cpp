#include "core/Bookmark.hpp"

#include <iostream>

Bookmark::Bookmark(Bookmark::Builder builder)
        : title_(std::move(builder.title()))
        , url_(std::move(builder).url())
        , tags_(std::move(builder.tags())) {}

const std::string& Bookmark::title() const {
    return title_;
}

const std::string& Bookmark::url() const {
    return url_;
}

const std::vector<std::string>& Bookmark::tags() const {
    return tags_;
}

Bookmark::Builder& Bookmark::Builder::SetTitle(std::string title) {
    title_ = std::move(title);
    return *this;
}

Bookmark::Builder& Bookmark::Builder::SetUrl(std::string url) {
    url_ = std::move(url);
    return *this;
}

Bookmark::Builder& Bookmark::Builder::SetTags(std::vector<std::string> tags) {
    tags_ = std::move(tags);
    return *this;
}

std::string& Bookmark::Builder::title() {
    return title_;
}

std::string& Bookmark::Builder::url() {
    return url_;
}

std::vector<std::string>& Bookmark::Builder::tags() {
    return tags_;
}

Bookmark Bookmark::Builder::build() {
    return Bookmark(*this);
}

void Bookmark::Print() const {
    std::cout << "title: " << title_ << std::endl;
    std::cout << "url: " << url_ << std::endl;
    if (tags_.empty())
        return;

    std::cout << "tags: ";
    for (const auto& tag : tags_) {
        std::cout << "#" << tag << " ";
    }
    std::cout << std::endl;
}
