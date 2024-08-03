#pragma once

#include <utility>

// TODO : Switch both to long double
typedef double operand_t;
typedef double result_t;

using Operand = operand_t;
using Result = result_t;

namespace evaluator::util
{
	constexpr const double PI = 3.14159265358979323846264338327950288419716939937510;
    constexpr const double E = 2.71828182845904523536028747135266249775724709369995;

	constexpr double ConvertDegToRad(Operand deg) { return deg * (PI / 180); }
	constexpr double ConvertRadToDeg(Operand rad) { return rad * (180 / PI); }

template <typename T, typename = std::enable_if_t<std::is_default_constructible<T>::value>>
class Singleton
{
public:
    Singleton() = default;
    ~Singleton() = default;

    static T& GetInstance()
    {
        static T instance;
        return instance;
    }
    T* operator->() const
    {
        return std::addressof(GetInstance());
    }
    T& operator*() const
    {
        return GetInstance();
    }
    T& operator()() const
    {
        return GetInstance();
    }

private:
    static inline T *const p = nullptr;
};

}

#define EMIT(msg) \
do { \
std::cerr << msg; \
} while(false)

#ifndef NDEBUG
#define DEBUG_EMIT(msg) EMIT(msg)
#else
#define DEBUG_EMIT(...)
#endif

#define ABORT(msg) EMIT(msg); std::abort()

#define SYNTAX_ERROR(msg) EMIT((std::string("Syntax Error: ") + msg))

#define EVALUATOR_DEPRECATED [[deprecated]]
#define EVALUATOR_UNUSED [[maybe_unused]]
