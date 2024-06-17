#pragma once

#ifndef EVALUATOR_GLOBAL_HPP
#define EVALUATOR_GLOBAL_HPP

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define DECL_EXPORT __declspec(dllexport)
#  define DECL_IMPORT __declspec(dllimport)

#pragma warning (disable : 4251)
#else
#  define DECL_EXPORT     __attribute__((visibility("default")))
#  define DECL_IMPORT     __attribute__((visibility("default")))
#endif

#if defined(EVALUATOR_LIBRARY) || defined(EVALUATOR_EXPORTS)
#  define EVALUATOR_API DECL_EXPORT
#else
#  define EVALUATOR_API DECL_IMPORT
#endif

#endif // EVALUATOR_GLOBAL_HPP
