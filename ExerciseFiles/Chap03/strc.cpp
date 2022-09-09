// strc.cpp - simple string wrapper class
// Bill Weinman [bw.org]
// as of 2022-08-21

#include "strc.h"
#include <format>
#include <cstring>
#include <utility>
#include <memory>

namespace bw {

// C++23-style print() (stdout)
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void strc::msg(const char* s) {
    if(data) print("{}: {} ({})\n", strc_class, s, data);
    else print("{}: {}\n", strc_class, s);
}

strc::strc() {
    msg("default ctor");
}

strc::strc(const char* s) {
    len = strnlen(s, strc_maxlen);
    data = new char[len + 1];
    data[len] = 0;
    memcpy(data, s, len);
    msg("c-string ctor");
}

strc::strc(const strc& o) {
    len = o.len;
    data = new char[len + 1];
    data[len] = 0;
    memcpy(data, o.data, len);
    msg("copy ctor");
}

strc::strc(strc&& o) noexcept {
    len = o.len;
    data = o.data;
    o.len = 0;
    o.data = nullptr;
    msg("move ctor");
}

strc::~strc() {
    msg("dtor");
    reset();
}

void strc::reset() {
    len = 0;
    if(data) delete[] data;
}

size_t strc::size() const {
    return len;
}

size_t strc::length() const {
    return size();
}

strc & strc::operator = (strc o) {
    swap(o);
    msg("copy and swap");
    return *this;
}

const char * strc::c_str() const {
    return data;
}

strc::operator const char * () const {
    return c_str();
}

void strc::swap(strc & o) noexcept {
    auto tmpdata = o.data;
    auto tmplen = o.len;
    o.data = data;
    o.len = len;
    data = tmpdata;
    len = tmplen;
    msg("strc swap");
}

} // namespace bw
