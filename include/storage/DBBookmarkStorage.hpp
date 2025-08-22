#include "IBookmarkStorage.hpp"

class DBBookmarkStorage : public IBookmarkStorage {
public:
    bool DeleteBookmark(std::size_t id) override;
    bool AddBookMark() override;
    bool UpdateBookmark() override;
    std::optional<Bookmark> GetBookmark(std::size_t id) override;

private:
    
};
