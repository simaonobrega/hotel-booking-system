cmake_minimum_required(VERSION 3.24)
project(hotel_booking_system C)

set(CMAKE_C_STANDARD 11)

add_executable(hotel_booking_system main.c csv_reader.c hotel_manager.c main_menu.c booking.c reservation_manager.c recommend_hotel.c input_manager.c  export_data.c list.c edit_hotel_list.c)