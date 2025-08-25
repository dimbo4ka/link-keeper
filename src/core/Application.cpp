#include "core/Application.hpp"

#include <iostream>
#include <memory>

#include "storage/DBBookmarkStorage.hpp"

Application::Application() 
        : arg_parser_("")
        , tags_(arg_parser_.AddStringArgument('t', "tags", "boomark tags").
                            MultiValue().Default("")) {
    arg_parser_.AddFlag('r', "rm", "delete bookmark");
    arg_parser_.AddFlag('a', "add", "add bookmark");
    arg_parser_.AddFlag('g', "get", "get bookmark");
    arg_parser_.AddFlag('s', "search", "search bookmarks by tag");
    arg_parser_.AddFlag('a', "all", "print all bookmarks");

    arg_parser_.AddStringArgument("title", "boomark title").Positional().Default("");
    arg_parser_.AddStringArgument("url", "boomark url").Default("");
    arg_parser_.AddHelp('h', "help", "parser description");
}

bool Application::Run(int argc, char** argv) {
    if (!arg_parser_.Parse(argc, argv))
        return false;
    if (arg_parser_.Help()) {
        std::cout << arg_parser_.HelpDescription() << '\n';
        return true;
    }

    auto bookmark_storage = std::make_unique<DBBookmarkStorage>();
    std::string title = arg_parser_.GetStringValue("title");
    std::string url = arg_parser_.GetStringValue("url");

    if (arg_parser_.GetFlag("rm")) {
        return bookmark_storage->DeleteBookmark(std::move(title));
    } else if (arg_parser_.GetFlag("add")) {
        std::vector<std::string> tags;
        std::size_t tag_count = tags_.GetArgCount();
        tags.reserve(tag_count);        
        for (std::size_t i = 0; i < tag_count; ++i) {
            tags.push_back(tags_.GetValue(i));
        }

        return bookmark_storage->AddBookMark(
            Bookmark::Builder()
                .SetTitle(std::move(title))
                .SetUrl(std::move(url))
                .SetTags(std::move(tags))
                .build()
        );
    } else if (arg_parser_.GetFlag("get")) {
        auto bookmark = bookmark_storage->GetBookmark(title);
        if (!bookmark.has_value()) {
            std::cerr << "Incorrect bookmark title : " << title << '\n';
            return false;
        }
        bookmark->Print();
        return true;
    } else if (arg_parser_.GetFlag("search")) {
        return bookmark_storage->SearchByTag(std::move(title));
    } else if (arg_parser_.GetFlag("all")) {
        return bookmark_storage->SearchAll();
    }
    std::cerr << "Please enter the option\n";
    return false;
}
