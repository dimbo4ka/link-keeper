#include "storage/DBBookmarkStorage.hpp"

#include <format>
#include <iostream>

DBBookmarkStorage::DBBookmarkStorage()
        : database_("bookmark.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
        {
    database_.exec(
        "CREATE TABLE IF NOT EXISTS bookmarks("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL UNIQUE, "
        "url TEXT NOT NULL)"
    );
    database_.exec(
        "CREATE TABLE IF NOT EXISTS tags("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL UNIQUE)"
    );
    database_.exec(
        "CREATE TABLE IF NOT EXISTS bookmark_tags("
        "bookmark_id INTEGER NOT NULL, "
        "tag_id INTEGER NOT NULL, "
        "FOREIGN KEY (bookmark_id) REFERENCES bookmarks(id), "
        "FOREIGN KEY (tag_id) REFERENCES tags(id), "
        "PRIMARY KEY (bookmark_id, tag_id))"
    );
}

bool DBBookmarkStorage::DeleteBookmark(std::string title) {
    try {
        SQLite::Statement delete_bookmark(database_, "DELETE FROM bookmarks WHERE title = ?");
        delete_bookmark.bind(1, title);
        delete_bookmark.exec();
        std::cout << "Bookmark has been deleted success!" << std::endl;
        return true;
    } catch (std::exception& e) {
        std::cerr << "Error deleting bookmark: " << e.what() << std::endl;
    }
    return false;
}

bool DBBookmarkStorage::AddBookMark(Bookmark bookmark) {
    try {
        SQLite::Statement insert_bookmark(database_, "INSERT OR IGNORE INTO bookmarks (title, url) VALUES (?, ?)");
        insert_bookmark.bind(1, bookmark.title());
        insert_bookmark.bind(2, bookmark.url());
        insert_bookmark.exec();
        int bookmark_id = database_.getLastInsertRowid();

        for (const auto& tag : bookmark.tags()) {
            SQLite::Statement insert_tag(database_, "INSERT OR IGNORE INTO tags (name) VALUES (?)");
            insert_tag.bind(1, tag);
            insert_tag.exec();

            SQLite::Statement select_tag(database_, "SELECT id FROM tags WHERE name = ?");
            select_tag.bind(1, tag);
            select_tag.executeStep();
            int tag_id = select_tag.getColumn(0).getInt();

            SQLite::Statement insert_link(database_, "INSERT OR IGNORE INTO bookmark_tags (bookmark_id, tag_id) VALUES (?, ?)");
            insert_link.bind(1, bookmark_id);
            insert_link.bind(2, tag_id);
            insert_link.exec();
        }
        return true;
    } catch (std::exception& e) {
        std::cerr << "Error adding bookmark: " << e.what() << std::endl;
    }
    return false;
}

std::optional<Bookmark> DBBookmarkStorage::GetBookmark(std::string title) {
    try {
        SQLite::Statement get_bookmark(database_, "SELECT id, url FROM bookmarks WHERE title = ?");
        get_bookmark.bind(1, title);
        if (!get_bookmark.executeStep())
            return std::nullopt;
        int bookmark_id = get_bookmark.getColumn(0).getInt();
        std::string url = get_bookmark.getColumn(1).getString();

        std::vector<std::string> tags;
        SQLite::Statement get_tags(database_, 
                "SELECT name FROM tags "
                "JOIN bookmark_tags ON tags.id = bookmark_tags.tag_id "
                "JOIN bookmarks ON bookmarks.id = bookmark_tags.bookmark_id "
                "WHERE bookmarks.id = ?");
        get_tags.bind(1, bookmark_id);

        while (get_tags.executeStep()) {
            tags.push_back(get_tags.getColumn(0).getString());
        }

        return Bookmark::Builder()
                    .SetTitle(title)
                    .SetUrl(std::move(url))
                    .SetTags(std::move(tags))
                    .build();
    } catch (std::exception& e) {
        std::cerr << "Error getting bookmark: " << e.what() << std::endl;
    }
    return std::nullopt;
}

bool DBBookmarkStorage::SearchByTag(std::string tag) {
    try {
        SQLite::Statement search_by_tag(database_, 
                "SELECT title, url FROM bookmarks "
                "JOIN bookmark_tags ON bookmarks.id = bookmark_tags.bookmark_id "
                "JOIN tags ON tags.id = bookmark_tags.tag_id "
                "WHERE tags.name = ?");
        search_by_tag.bind(1, tag);
    
        std::cout << std::format("Bookmarks with tag \"{}\"", tag) << std::endl;
        while (search_by_tag.executeStep()) {
            std::string title = search_by_tag.getColumn(0).getString();
            std::string url = search_by_tag.getColumn(1).getString();
            std::cout << std::format("Title: {} | url: {}", title, url) << std::endl;
        }
        return true;
    } catch (std::exception& e) {
        std::cerr << "Error searching bookmarks: " << e.what() << std::endl;
    }
    return false;
}
