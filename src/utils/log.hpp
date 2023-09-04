#ifndef ZREST_LOG_HPP
#define ZREST_LOG_HPP
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
namespace zrestlog
{
    template <typename... Args>
    auto format(std::string_view fmt, Args&&... args) {
        return fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...));
    }
class Log final
{
    public:
        static Log* getInstance(void);
        
        std::shared_ptr<spdlog::logger> getLogger(void);    

    private:
        Log();
        std::shared_ptr<spdlog::logger> logger;
};
}
#endif
