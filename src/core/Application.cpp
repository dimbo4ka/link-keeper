#include "core/Application.hpp"

#include <iostream>
#include <memory>

#include "storage/DBBookmarkStorage.hpp"
#include "storage/JSONBookmarkStorage.hpp"

Application::Application() 
        : arg_parser_("") {
    arg_parser_.AddFlag('r', "rm", "delete bookmark");
    arg_parser_.AddFlag('a', "add", "add bookmark");
    arg_parser_.AddFlag('u', "upd", "update bookmark");
    arg_parser_.AddFlag('g', "get", "get bookmark");
    arg_parser_.AddFlag("db", "choose a database for storing bookmarks");

    arg_parser_.AddStringArgument("title", "boomark title").Default("");
    arg_parser_.AddStringArgument("url", "boomark url").Default("");
    arg_parser_.AddStringArgument('t', "tags", "boomark tags").MultiValue();
    arg_parser_.AddHelp('h', "--help", "parser description");
}

bool Application::Run(int argc, char** argv) {
    if (!arg_parser_.Parse(argc, argv))
        return false;
    if (arg_parser_.Help()) {
        std::cout << arg_parser_.HelpDescription() << '\n';
        return true;
    }

    std::unique_ptr<IBookmarkStorage> bookmark_storage;
    if (arg_parser_.GetFlag("db")) {
        bookmark_storage = std::make_unique<DBBookmarkStorage>();
    } else {
        std::cerr << "Don't support storing in json\n";
        return false;
    }

    std::string title = arg_parser_.GetStringValue("title");
    std::string url = arg_parser_.GetStringValue("url");
    if (arg_parser_.GetFlag("rm")) {
        return bookmark_storage->DeleteBookmark(std::move(title));
    } else if (arg_parser_.GetFlag("add")) {
        return bookmark_storage->AddBookMark(
            Bookmark::Builder()
                .SetTitle(std::move(title))
                .SetUrl(std::move(url))
                .build()
        );
    } else if (arg_parser_.GetFlag("upd")) {
        return bookmark_storage->UpdateBookmark(std::move(title));
    } else if (arg_parser_.GetFlag("get")) {
        auto bookmark = bookmark_storage->GetBookmark(title);
        if (!bookmark.has_value()) {
            std::cerr << "Incorrect bookmark title : " << title << '\n';
            return false;
        }
        bookmark->Print();
        return true;
    }
    std::cerr << "Please enter the option\n";
    return false;
}
