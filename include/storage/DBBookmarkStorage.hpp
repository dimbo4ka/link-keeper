#include "IBookmarkStorage.hpp"

#include "SQLiteCpp/SQLiteCpp.h"

class DBBookmarkStorage : public IBookmarkStorage {
public:
    DBBookmarkStorage();

    bool DeleteBookmark(std::string title) override;
    bool AddBookMark(Bookmark) override;
    std::optional<Bookmark> GetBookmark(std::string title) override;

private:
    SQLite::Database database_;
};
