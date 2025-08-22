#include "core/Application.hpp"

#include <memory>

#include "storage/DBBookmarkStorage.hpp"
#include "storage/JSONBookmarkStorage.hpp"

Application::Application() 
        : arg_parser_("") {
    arg_parser_.AddStringArgument("rm", "delete bookmark");
    arg_parser_.AddStringArgument("add", "add bookmark");
    arg_parser_.AddStringArgument("upd", "update bookmark");
    arg_parser_.AddStringArgument("get", "get bookmark");
    arg_parser_.AddHelp('h', "--help", "parser description");
    arg_parser_.AddFlag("db", "choose a database for storing bookmarks");
}

bool Application::Run(int argc, char** argv) {
    if (!arg_parser_.Parse(argc, argv))
        return false;

    std::unique_ptr<IBookmarkStorage> bookmark_storage_;
    if (arg_parser_.GetFlag("db")) {
        bookmark_storage_ = std::make_unique<DBBookmarkStorage>();
    } else {
        bookmark_storage_ = std::make_unique<JSONBookmarkStorage>();
    }
}
