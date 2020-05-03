#include <exception>

class FileIOException : public std::exception
{
private:
    std::string m_message;

public:
    FileIOException(std::string msg) : m_message(msg){};
    const char *what() const throw()
    {
        return m_message.c_str();
    }
};