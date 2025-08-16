#include "core/Bookmark.hpp"

Bookmark::Bookmark(Bookmark::Builder builder)
        : title_(std::move(builder.title()))
        , url_(std::move(builder).url())
        , tags_(std::move(builder.tags()))
        , id_(builder.id()) {}

const std::string& Bookmark::title() const {
    return title_;
}

const std::string& Bookmark::url() const {
    return url_;
}

const std::vector<std::string> Bookmark::tags() const {
    return tags_;
}

std::size_t Bookmark::id() const {
    return id_;
}

Bookmark::Builder& Bookmark::Builder::SetTitle(std::string title) {
    title_ = std::move(title);
}

Bookmark::Builder& Bookmark::Builder::SetUrl(std::string url) {
    url_ = std::move(url);
}

Bookmark::Builder& Bookmark::Builder::SetTags(std::vector<std::string> tags) {
    tags_ = std::move(tags);
}

Bookmark::Builder& Bookmark::Builder::SetId(std::size_t id) {
    id_ = id;
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

std::size_t Bookmark::Builder::id() {
    return id_;
}
