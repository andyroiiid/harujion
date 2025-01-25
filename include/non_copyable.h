// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

class NonCopyable
{
public:
    NonCopyable() = default;

    NonCopyable(const NonCopyable &) = delete;

    NonCopyable &operator=(const NonCopyable &) = delete;
};
