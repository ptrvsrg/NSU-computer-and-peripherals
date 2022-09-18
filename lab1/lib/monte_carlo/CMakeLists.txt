set(LIBRARY_NAME monte_carlo)
set(LIBRARY_HEADERS_DIR include)
set(LIBRARY_HEADERS ${LIBRARY_HEADERS_DIR}/monte_carlo.h)
set(LIBRARY_SOURCE_DIR src)
set(LIBRARY_SOURCE ${LIBRARY_SOURCE_DIR}/monte_carlo.cpp)
set(LINK_LIBRARY point random)

project(${PROJECT_NAME})

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCE})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR}/)
target_link_libraries(${LIBRARY_NAME} PUBLIC ${LINK_LIBRARY})