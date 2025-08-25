add_library(db-storage STATIC DBBookmarkStorage.cpp)
target_include_directories(db-storage PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(db-storage PUBLIC SQLiteCpp sqlite3)
