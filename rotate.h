#define _USE_MATH_DEFINES
#include <cstdlib>
#include <cmath>
#include <vector>
#include <chrono>
#include <functional>
#include <fstream>
#include <cstdarg>
#include <string>


template<class F>
struct coord2d
{
    F x;
    F y;
};

/* math */

//Calculate the theta of the vector to the horizontal.
double_t dot_theta(const coord2d & vector)
{
    return std::acos(vector.x / std::hypot(vector.x, vector.y));
}

double_t dot_clamp(const double_t theta)
{
    return theta > M_PI ? (2 * M_PI) - theta : theta;
}

//Calculate the theta of the vector to the horizontal using atan2.
double_t trig_theta(const coord2d & line)
{
    return 	std::atan2(line.y, line.x);
}

double_t trig_clamp(const double_t theta)
{
    return theta > M_PI ? -((2 * M_PI) - theta) : theta;
}

/* iterate */
//std::chrono::nanoseconds polar_iteration
//        (const double_t increment, const func_def::iterable & iterable)
//{
//    using time = std::chrono::high_resolution_clock;
//    std::chrono::nanoseconds duration;
//
//    auto start = time::now();
//    double_t theta = 0;
//    for (size_t i = 0; (theta = i*increment) <= M_PI * 2; ++i)
//        iterable({ std::cos(theta), std::sin(theta) }, theta);
//    return time::now() - start;
//};

/* string conversion */

//convert double to string
std::string dts(double_t d)
{
    char buf[50];
    sprintf_s(buf, "%.16f", d);
    return buf;
}

//convert coord2d to string
std::string cts(const coord2d & vector)
{
    return dts(vector.x) + " , " + dts(vector.y);
}

////pass the theta to the func_def::iterate function so that the theta used to calculate the vector can be used for comparison
////output thetas and stats using iterate functon
//void calculation_block
//        (std::ofstream & outfile, const double_t increment, const func_def::iterate & iterate, const func_def::theta & calc_theta, const func_def::clamp & clamp)
//{
//    size_t count = 0;
//    double_t sumDelta = 0;
//    double_t minDelta = std::numeric_limits<double_t>::max();
//    double_t maxDelta = std::numeric_limits<double_t>::lowest();
//
//    auto duration = iterate(increment, [&](const coord2d & vector, const double_t theta)
//    {
//        double_t calced_theta = calc_theta(vector);
//        double_t clamped_theta = clamp(theta);
//
//        double_t delta = std::abs(clamped_theta - calced_theta);
//        if (count != 0)
//        {
//            sumDelta += delta;
//            if (minDelta > delta)
//                minDelta = delta;
//            if (maxDelta < delta)
//                maxDelta = delta;
//        }
//
//        table_row(outfile,
//                std::to_string(count).c_str(),
//                cts(vector).c_str(),
//                dts(calced_theta).c_str(),
//                dts(clamped_theta).c_str(),
//                dts(delta).c_str());
//        ++count;
//    }).count();
//
//    heading(outfile, 3, ("Duration: " + std::to_string(duration) + " ns").c_str());
//    heading(outfile, 3, ("Mean Delta: " + dts(sumDelta / count)).c_str());
//    heading(outfile, 3, ("Min Delta: " + dts(minDelta)).c_str());
//    heading(outfile, 3, ("Max Delta: " + dts(maxDelta)).c_str());
//}

template<class F>
struct results
{
    std::chrono::nanoseconds duration = 0;
    F min_delta = std::numeric_limits<double_t>::max();
    F max_delta = std::numeric_limits<double_t>::lowest();
    F mean_delta = 0;
    size_t steps = 0;
};

//perform comparison on 32 and 64bit float
//FType - floating point type
template<class F>
struct rotator
{
    //process and populate results
    results<F> ()
    {
        using time = std::chrono::high_resolution_clock;
        std::chrono::nanoseconds duration;

        size_t count = 0;
        auto start = time::now();
        double_t theta = 0;
        for (size_t i = 0; (theta = i*increment) <= M_PI * 2; ++i)
        {
            coord2d vector{std::cos(theta), std::sin(theta)};

            double_t calced_theta = calc_theta(vector);
            double_t clamped_theta = clamp(theta);

            double_t delta = std::abs(clamped_theta - calced_theta);
            if (count != 0)
            {
                sumDelta += delta;
                if (minDelta > delta)
                    minDelta = delta;
                if (maxDelta < delta)
                    maxDelta = delta;
            }
//            take a function that gets called each iteration
//            table_row(outfile,
//                    std::to_string(count).c_str(),
//                    cts(vector).c_str(),
//                    dts(calced_theta).c_str(),
//                    dts(clamped_theta).c_str(),
//                    dts(delta).c_str());

            ++count;
        }

//        return time::now() - start;

        return {minDelta, maxDelta, sumDelta / count, count};
    }

    F increment;
    std::function <F (const coord2d<F> &)> theta;
    std::function <F (const F)> clamp;
    std::function <void (const coord2d<F> &, const F)> iterable;
    std::function <std::chrono::nanoseconds (const F, const iterable &)> iterate;
};


