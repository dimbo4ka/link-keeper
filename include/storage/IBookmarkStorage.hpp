#pragma once

#include "storage/Bookmark.hpp"

#include <cstddef>
#include <optional>

class IBookmarkStorage {
public:  
    virtual bool DeleteBookmark(std::size_t id) = 0;
    virtual bool AddBookMark() = 0;
    virtual bool UpdateBookmark() = 0;
    virtual std::optional<Bookmark> GetBookmark(std::size_t id) = 0;

    virtual ~IBookmarkStorage() = default;
};