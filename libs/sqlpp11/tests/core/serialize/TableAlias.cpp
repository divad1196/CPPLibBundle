/*
 * Copyright (c) 2016-2021, Roland Bock
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Sample.h"
#include "compare.h"
#include <sqlpp11/sqlpp11.h>

#include <iostream>

SQLPP_ALIAS_PROVIDER(sample)

int TableAlias(int, char* [])
{
  const auto foo = test::TabFoo{};
  const auto bar = test::TabBar{};

  // Individual values
  compare(__LINE__, foo.as(bar), "tab_foo AS tab_bar");
  compare(__LINE__, select(foo.omega).from(foo).unconditionally().as(bar),
          "(SELECT tab_foo.omega FROM tab_foo) AS tab_bar");

  // Table alias
  const auto tab = foo.as(sample);
  compare(__LINE__, select(tab.omega).from(tab).unconditionally(),
          "SELECT sample.omega FROM tab_foo AS sample");

  return 0;
}
