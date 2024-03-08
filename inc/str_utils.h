#pragma once

struct formatted_str {
    int char_cnt;
    const char buf[4096];
};

struct formatted_str format_string(const char* format, ...);