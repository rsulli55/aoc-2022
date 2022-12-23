add_executable(day1 day1.cpp)
target_link_libraries(day1 fmt::fmt)

add_executable(day2 day2.cpp)
target_link_libraries(day2 fmt::fmt)

install(TARGETS day1 day2
)
