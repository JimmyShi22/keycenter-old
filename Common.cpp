/*
    This file is part of cpp-ethereum.

    cpp-ethereum is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cpp-ethereum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @file Common.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 *
 * common stuff: common type definitions && timer && ScopeGuard && InvariantChecker
 */
#include "Common.h"
#include "Exceptions.h"

using namespace std;

namespace dev
{
// char const* Version = ETH_PROJECT_VERSION;
bytes const NullBytes;
std::string const EmptyString;

void InvariantChecker::checkInvariants(
    HasInvariants const* _this, char const* _fn, char const* _file, int _line, bool _pre)
{
    if (!_this->invariants())
    {
        ::boost::exception_detail::throw_exception_(FailedInvariant(), _fn, _file, _line);
    }
}

TimerHelper::~TimerHelper()
{
    auto e = std::chrono::high_resolution_clock::now() - m_t;
}

/// get utc time(ms)
uint64_t utcTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
}  // namespace dev
