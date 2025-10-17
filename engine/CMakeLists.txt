add_library(orderbook STATIC
    src/OrderBook.cpp
)

target_include_directories(orderbook PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


