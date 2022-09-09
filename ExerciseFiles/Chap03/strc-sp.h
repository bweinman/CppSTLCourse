// strc-sp.h - simple string wrapper class  (smart pointer version)
// Bill Weinman [bw.org]
// as of 2022-08-21

#ifndef BW_STRC_H_
#define BW_STRC_H_

#include <cstddef>  // size_t
#include <memory>

namespace bw {

constexpr const char* strc_class {"strc"};
constexpr const char* strc_version {"2.0"};
constexpr size_t strc_maxlen {10240};

class strc {
    std::unique_ptr<char[]> data {};
    size_t len {};
    void msg(const char*);
public:
    strc();
    strc(const char*);
    strc(const strc&);
    strc(strc &&) noexcept;
    ~strc();
    void reset();
    size_t size() const;
    size_t length() const;
    strc& operator = (strc);
    const char* c_str() const;
    operator const char* () const;
    void swap(strc&) noexcept;
};

} // namespace bw

#endif // BW_STRC_H_
