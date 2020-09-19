add_library(png INTERFACE)

find_library(LIBPNG "libpng" PATH ".")

target_link_libraries(png INTERFACE ${LIBPNG})

target_include_directories(png INTERFACE .)

target_link_libraries(png INTERFACE zlib)