cmake_minimum_required(VERSION 3.5.2)

project(HowToVisualize3DScenes)

add_executable(image_test image_driver.cpp)

add_executable(sky_render sky_color_driver.cpp)

add_executable(sphere_hit sphere_hit_driver.cpp)
