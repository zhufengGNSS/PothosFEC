// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <type_traits>

template <typename T, typename U = void>
using EnableIfNotFloatingPoint = typename std::enable_if<!std::is_floating_point<T>::value, U>::type;

template <typename T, typename U = void>
using EnableIfFloatingPoint = typename std::enable_if<std::is_floating_point<T>::value, U>::type;

void throwOnErrCode(int errCode);
