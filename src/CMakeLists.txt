add_executable(grayscale
main.cpp
iopng.cpp
file.cpp
image.cpp
image_info.cpp
iojpeg.cpp
string.cpp)

target_link_libraries(grayscale PUBLIC
png)

target_link_libraries(grayscale PUBLIC
jpeg)
