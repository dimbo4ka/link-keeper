add_library(application STATIC Application.cpp)
target_link_libraries(application PRIVATE argparser db-storage json-storage)
target_include_directories(application PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(bookmark STATIC Bookmark.cpp)
target_include_directories(bookmark PUBLIC ${CMAKE_SOURCE_DIR}/include)
