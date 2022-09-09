// strc-sp.cpp - simple string wrapper class (smart pointer version)
// Bill Weinman [bw.org]
// as of 2022-08-21

#include "strc-sp.h"
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
    // use data.get() to get the c-string
    if(data) print("{}: {} ({})\n", strc_class, s, data.get());
    else print("{}: {}\n", strc_class, s);
}

strc::strc() {
    msg("default ctor");
}

strc::strc(const char* s) {
    len = strnlen(s, strc_maxlen);

    // use make_unique to create a new unique pointer
    data = std::make_unique<char[]>(len + 1);

    data[len] = 0;  // terminate the string
    memcpy(data.get(), s, len);
    msg("c-string ctor");
}

strc::strc(const strc& o) {
    len = o.len;

    // use reset with new to allocate new object
    data.reset(new char[len + 1]);
    
    // use get() for memcpy
    memcpy(data.get(), o.data.get(), len);
    data[len] = 0;  // terminate the string
    msg("copy ctor");
}

strc::strc(strc&& o) noexcept {
    len = o.len;

    // use move on the smart pointer
    data = std::move(o.data);

    o.len = 0;
    msg("move ctor");
}

strc::~strc() {
    msg("dtor");
}

void strc::reset() {
    len = 0;

    // reset destroyes the object (frees the char[] memory)
    if(data) data.reset();
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
    return data.get();
}

strc::operator const char * () const {
    return c_str();
}

void strc::swap(strc & o) noexcept {
    // use std::move() to move unique pointers
    // three move() calls to swap
    auto tmpdata = std::move(o.data);
    auto tmplen = o.len;
    o.data = std::move(data);
    o.len = len;
    data = std::move(tmpdata);
    len = tmplen;
    msg("strc swap");
}

} // namespace bw
