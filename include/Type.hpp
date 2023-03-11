#ifndef __PPM_MATRIX_HPP__
#define __PPM_MATRIX_HPP__
#include <cmath>
#include <complex>
#include <limits>
#include <type_traits>
namespace ppm
{
    namespace details
    {
        constexpr double c = 3.e8;                                      ///< speed of light
        constexpr double e = 2.718281828459045;                         ///< eulers number
        constexpr double inf = std::numeric_limits<double>::infinity(); ///< infinity
        constexpr double pi = 3.141592653589793238462643383279502884;   ///< Pi
        const double nan = std::nan("1");                               ///< NaN
        constexpr auto j = std::complex<double>(0, 1);                  // sqrt(-1) unit imaginary number
        constexpr size_t matrix_memory_limit = 260;

        constexpr double DAYS_PER_WEEK = 7;                                        ///< Number of days in a week
        constexpr double MINUTES_PER_HOUR = 60;                                    ///< Number of minutes in an hour
        constexpr double SECONDS_PER_MINUTE = 60;                                  ///< Number of seconds in a minute
        constexpr double MILLISECONDS_PER_SECOND = 1000;                           ///< Number of milliseconds in a second
        constexpr double SECONDS_PER_HOUR = MINUTES_PER_HOUR * SECONDS_PER_MINUTE; ///< Number of seconds in an hour
        constexpr double HOURS_PER_DAY = 24;                                       ///< Number of hours in a day
        constexpr double MINUTES_PER_DAY = HOURS_PER_DAY * MINUTES_PER_HOUR;       ///< Number of minutes in a day
        constexpr double SECONDS_PER_DAY = MINUTES_PER_DAY * SECONDS_PER_MINUTE;   ///< Number of seconds in a day
        constexpr double MILLISECONDS_PER_DAY =
            SECONDS_PER_DAY * MILLISECONDS_PER_SECOND;                       ///< Number of milliseconds in a day
        constexpr double SECONDS_PER_WEEK = SECONDS_PER_DAY * DAYS_PER_WEEK; ///< Number of seconds in a week
    }

    //======================================Typedef======================================
    using int64 = std::int64_t;
    using int32 = std::int32_t;
    using int16 = std::int16_t;
    using int8 = std::int8_t;
    using uint64 = std::uint64_t;
    using uint32 = std::uint32_t;
    using uint16 = std::uint16_t;
    using uint8 = std::uint8_t;

    //=====================================Functions=====================================
    // Memory Type such as heap and stack memory.
    constexpr size_t MT(size_t A, size_t B)
    {
        return A * B < details::matrix_memory_limit ? 1 : 0;
    }

    constexpr size_t Less(size_t A, size_t B)
    {
        return A < B ? A : B;
    }

    constexpr size_t More(size_t A, size_t B)
    {
        return A < B ? B : A;
    }

    constexpr bool LessThen(size_t A, size_t B)
    {
        return A < B;
    }
    //====================================Typetraits=====================================
    template <typename T, typename RT = void>
    using enable_arithmetic_type_t = typename std::enable_if<std::is_arithmetic<T>::value, RT>::type;
    template <typename T, typename RT = void>
    using disable_arithmetic_type_t = typename std::enable_if<!std::is_arithmetic<T>::value, RT>::type;

    /// Alias template for enable_if
    template <bool _Cond, typename _Tp = void>
    using enable_if_t = typename std::enable_if<_Cond, _Tp>::type;

}
#endif // __PPM_MATRIX_HPP__