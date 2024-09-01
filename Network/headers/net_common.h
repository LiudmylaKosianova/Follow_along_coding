#pragma once

#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iostream>

#define ASIO_STANDALONE
#include "../libs/asio-1.30.2/include/asio.hpp"
#include "../libs/asio-1.30.2/include/asio/ts/buffer.hpp"
#include "../libs/asio-1.30.2/include/asio/ts/internet.hpp"