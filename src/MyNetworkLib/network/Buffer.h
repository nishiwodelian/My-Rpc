#pragma once
#include <string>

class Buffer{
    public:
     Buffer() = default;
     ~Buffer() = default;

     void Append(const char *_str, int _size);
     //void Append(const char *_str);
     void Append(std::string str);
     ssize_t Size();
     const char *ToStr();
     const std::string GetString();
     void Clear();
     void GetLine();
     void SetBuf(const char *buf);
     void SetBuf(std::string buf);

    private:
     std::string buf_;
};