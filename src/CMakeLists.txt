add_executable(day1 day1.cpp)
target_link_libraries(day1 fmt::fmt)

add_executable(day2 day2.cpp)
target_link_libraries(day2 fmt::fmt)

add_executable(day3 day3.cpp)
target_link_libraries(day3 fmt::fmt)

install(TARGETS day1 day2 day3
)
