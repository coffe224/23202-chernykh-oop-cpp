#include <ostream>
#include <tuple>

template <std::size_t M = 0, typename Ch, typename Tr, typename... Args>
typename std::enable_if_t<M == sizeof...(Args), std::basic_ostream<Ch, Tr>&>
    operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t)
{
    return os;
}


template <std::size_t M = 0, typename Ch, typename Tr, typename... Args>
typename std::enable_if_t<M < sizeof...(Args), std::basic_ostream<Ch, Tr>&>
    operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t)
{
    os << std::get<M>(t);
    if (M + 1 != sizeof...(Args)) {
        os << " | ";
    }
    return operator<<<M + 1, Ch, Tr, Args...>(os, t);
}

