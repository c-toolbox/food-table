/*****************************************************************************************
 *                                                                                       *
 * Food on the table                                                                     *
 *                                                                                       *
 * Copyright (c) 2019                                                                    *
 * Alexander Bock                                                                        *
 * mail@alexanderbock.eu                                                                 *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#include "svg.h"

#include <array>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <numeric>

// Returns the numbers that are represented by rotating the image corresponding to 'number'
// by 90, 180 and 270 degrees
std::array<uint16_t, 3> rotated(uint16_t number) {
    //    ------------------    ----------------    ------------------    ----------------
    //    | 64 | 128 | 256 |    | 256 | 32 | 4 |    |   4 |   2 |  1 |    | 1 |  8 |  64 |
    //    ------------------    ----------------    ------------------    ----------------
    //    |  8 |  16 |  32 | -> | 128 | 16 | 2 | -> |  32 |  16 |  8 | -> | 2 | 16 | 128 |
    //    ------------------    ----------------    ------------------    ----------------
    //    |  1 |   2 |   4 |    |  64 |  8 | 1 |    | 256 | 128 | 64 |    | 4 | 32 | 256 |
    //    ------------------    ----------------    ------------------    ----------------

    // 90 deg
    uint16_t rot90 = 0;
    if (number & 1)   { rot90 |= 64;  }
    if (number & 2)   { rot90 |= 8;   }
    if (number & 4)   { rot90 |= 1;   }
    if (number & 8)   { rot90 |= 128; }
    if (number & 16)  { rot90 |= 16;  }
    if (number & 32)  { rot90 |= 2;   }
    if (number & 64)  { rot90 |= 256; }
    if (number & 128) { rot90 |= 32;  }
    if (number & 256) { rot90 |= 4;   }

    // 180 deg
    uint16_t rot180 = 0;
    if (number & 1)   { rot180 |= 256; }
    if (number & 2)   { rot180 |= 128; }
    if (number & 4)   { rot180 |= 64;  }
    if (number & 8)   { rot180 |= 32;  }
    if (number & 16)  { rot180 |= 16;  }
    if (number & 32)  { rot180 |= 8;   }
    if (number & 64)  { rot180 |= 4;   }
    if (number & 128) { rot180 |= 2;   }
    if (number & 256) { rot180 |= 1;   }

    // 270 deg
    uint16_t rot270 = 0;
    if (number & 1)   { rot270 |= 4;   }
    if (number & 2)   { rot270 |= 32;  }
    if (number & 4)   { rot270 |= 256; }
    if (number & 8)   { rot270 |= 2;   }
    if (number & 16)  { rot270 |= 16;  }
    if (number & 32)  { rot270 |= 128; }
    if (number & 64)  { rot270 |= 1;   }
    if (number & 128) { rot270 |= 8;   }
    if (number & 256) { rot270 |= 64; }

    return { rot90, rot180, rot270 };
}

void savePage(std::string prefix, int idx, std::vector<uint16_t> numbers) {
    assert(numbers.size() <= 12);

    std::ofstream file(prefix + '-' + std::to_string(idx) + ".svg");
    file << page(numbers);
}

int main(int argc, char** argv) {
    // Generate all possible values
    std::vector<uint16_t> values(512);
    std::iota(values.begin(), values.end(), 0);

    std::vector<bool> duplicates(512, false);
    for (uint16_t v : values) {
        if (duplicates[v]) {
            // Ignore the duplicates or otherwise we would remove our original values, too
            continue;
        }

        std::array<uint16_t, 3> vs = rotated(v);

        // Mark the rotated values as duplicates
        duplicates[vs[0]] = true;
        duplicates[vs[1]] = true;
        duplicates[vs[2]] = true;
    }

    // Remove all duplicates
    auto filter = [&duplicates](uint16_t v) { return duplicates[v]; };
    values.erase(std::remove_if(values.begin(), values.end(), filter), values.end());


    for (size_t i = 0, j = 0; i < values.size(); i += 12, ++j) {
        savePage("food", static_cast<int>(j), std::vector<uint16_t>(values.begin() + i, values.begin() + i + 12));
    }

    //savePage("test", 0, { 105, 222, 2,   10, 12, 14,   221, 501, 32,   511, 168, 326 });
}