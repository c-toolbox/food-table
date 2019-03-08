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

#include <string>
#include <vector>

std::string header() {
    return R"text(
<?xml version="1.0" encoding="UTF-8" standalone="no"?>

<svg xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:cc="http://creativecommons.org/ns#"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:svg="http://www.w3.org/2000/svg"
   xmlns="http://www.w3.org/2000/svg" xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
   xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
   width="210mm" height="297mm" viewBox="0 0 210 297" version="1.1" id="svg14165"
   sodipodi:docname="food-full2.svg" inkscape:version="0.92.4 (5da689c313, 2019-01-14)">
  <defs id="defs14159" />
  <sodipodi:namedview id="base" pagecolor="#ffffff" bordercolor="#666666" borderopacity="1.0"
     inkscape:pageopacity="0.0" inkscape:pageshadow="2" inkscape:zoom="1" inkscape:cx="-24.10575"
     inkscape:cy="78.163833" inkscape:document-units="mm" inkscape:current-layer="layer1"
     showgrid="false" inkscape:window-width="1920" inkscape:window-height="1017" inkscape:window-x="-8"
     inkscape:window-y="-8" inkscape:window-maximized="1" />
  <metadata id="metadata14162">
    <rdf:RDF>
      <cc:Work rdf:about="">
        <dc:format>image/svg+xml</dc:format>
        <dc:type rdf:resource="http://purl.org/dc/dcmitype/StillImage" />
        <dc:title />
      </cc:Work>
    </rdf:RDF>
  </metadata>
)text";
}

std::string group() {
    return "<g inkscape:label=\"boxes\" inkscape:groupmode=\"layer\" id=\"boxes\">";
}

std::string background(uint16_t number, float xOffset, float yOffset) {
    constexpr double BoxSize = 9.857142857142858;

    const std::string background = std::to_string(number) + "-background";
    const std::string backgroundInner = std::to_string(number) + "-background-inner";

    std::string outer = "  <rect id=\"" + background + "\" width = \"69\" height = \"69\" x=\"" + std::to_string(xOffset) + "\" y=\"" + std::to_string(yOffset) + "\"" + "style=\"stroke-width:2.64583325\" inkscape:label=\"" + background + "\" />";
    std::string inner = "  <rect id=\"" + backgroundInner + "\" width=\"49.285714285714285\" height=\"49.285714285714285\" x=\"" + std::to_string(xOffset + BoxSize) + "\" y=\"" + std::to_string(yOffset + BoxSize) + "\" style=\"fill:#ffffff;fill-opacity:1;stroke-width:13.24299145\" inkscape:label=\"" + backgroundInner + "\" />";

    return outer + '\n' + inner;
}


std::string rect(std::string id, int x, int y, float xOffset, float yOffset) {
    constexpr double BoxSize = 9.857142857142858;

    const double totalX = xOffset + (2 + x) * BoxSize;
    const double totalY = yOffset + (2 + y) * BoxSize;

    return "  <rect id=\"" + id + "\" width=\"" + std::to_string(BoxSize) + "\" height=\"" + std::to_string(BoxSize) + "\" x=\"" + std::to_string(totalX) + "\" y=\"" + std::to_string(totalY) + "\" style=\"display:inline; fill:#000000; " + "fill - opacity:1; stroke - width:2.65412712\" inkscape:label=\"" + id + "\" />";
}

std::string tag(uint16_t number, float xOffset, float yOffset) {
    //    -------------------------
    //    |       |       |       |
    //    |  64   |  128  |  256  |
    //    |       |       |       |
    //    -------------------------
    //    |       |       |       |
    //    |   8   |  16   |  32   |
    //    |       |       |       |
    //    -------------------------
    //    |       |       |       |
    //    |   1   |   2   |   4   |
    //    |       |       |       |
    //    -------------------------

    std::string res = background(number, xOffset, yOffset) + '\n';
    if (number & 1) {
        res += rect(std::to_string(number) + '-' + "1", 0, 2, xOffset, yOffset) + '\n';
    }
    if (number & 2) {
        res += rect(std::to_string(number) + '-' + "2", 1, 2, xOffset, yOffset) + '\n';
    }
    if (number & 4) {
        res += rect(std::to_string(number) + '-' + "4", 2, 2, xOffset, yOffset) + '\n';
    }
    if (number & 8) {
        res += rect(std::to_string(number) + '-' + "8", 0, 1, xOffset, yOffset) + '\n';
    }
    if (number & 16) {
        res += rect(std::to_string(number) + '-' + "16", 1, 1, xOffset, yOffset) + '\n';
    }
    if (number & 32) {
        res += rect(std::to_string(number) + '-' + "32", 2, 1, xOffset, yOffset) + '\n';
    }
    if (number & 64) {
        res += rect(std::to_string(number) + '-' + "64", 0, 0, xOffset, yOffset) + '\n';
    }
    if (number & 128) {
        res += rect(std::to_string(number) + '-' + "128", 1, 0, xOffset, yOffset) + '\n';
    }
    if (number & 256) {
        res += rect(std::to_string(number) + '-' + "256", 2, 0, xOffset, yOffset) + '\n';
    }

    return res;
}

std::string page(std::vector<uint16_t> numbers) {
    constexpr float Spacing = 70.f;
    constexpr float Offset = 0.8f;

    std::string res = header() + '\n';
    res += group() + '\n';
    for (size_t i = 0; i < numbers.size(); ++i) {
        const float xOffset = Spacing * (i % 3) + Offset;
        const float yOffset = Spacing * (i / 3) + Offset;

        res += tag(numbers[i], xOffset, yOffset) + '\n';
    }

    res += "</g>\n</svg>";
    return res;
}