#pragma once

#include "core/Bookmark.hpp"

#include <cstddef>
#include <optional>

class IBookmarkStorage {
public:  
    virtual bool DeleteBookmark(std::string title) = 0;
    virtual bool AddBookMark(Bookmark) = 0;
    virtual std::optional<Bookmark> GetBookmark(std::string title) = 0;

    virtual ~IBookmarkStorage() = default;
};
