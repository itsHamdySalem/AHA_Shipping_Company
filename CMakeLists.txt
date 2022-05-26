cmake_minimum_required(VERSION 3.22)
project(AHA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AHA
        CancellationEvent.cpp
        CancellationEvent.h
        cargo.cpp
        cargo.h
        Company.cpp
        Company.h
        Event.cpp
        Event.h
        list.h
        node.h
        PreparationEvent.cpp
        PreparationEvent.h
        priority_queue.h
        PromotionEvent.cpp
        PromotionEvent.h
        queue.h
        Source.cpp
        stack.h
        Time.cpp
        Time.h
        truck.cpp
        truck.h
        Types.h
        UI.cpp
        UI.h ReadWrite.h)
