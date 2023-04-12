#pragma once

#include <string>

std::vector<std::string> split(const std::string& str, const std::string& delims = " ");
std::vector<std::string_view> splitSV(std::string_view strv, std::string_view delims = " ");