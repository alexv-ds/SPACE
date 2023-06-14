#pragma once
#include <cstdint>

namespace engine::graphics {

struct Color {
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
};

struct Transparency {
  float a = 1.0f;
};


//color types
//https://www.w3.org/wiki/CSS/Properties/color/keywords
namespace color {

constexpr Color rgb8_to_color(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
  return {
    .r = static_cast<float>(r) / 255.0f,
    .g = static_cast<float>(g) / 255.0f,
    .b = static_cast<float>(b) / 255.0f
  };
}

[[maybe_unused]] constexpr const Color aliceblue = rgb8_to_color(240,248,255);
[[maybe_unused]] constexpr const Color antiquewhite = rgb8_to_color(250,235,215);
[[maybe_unused]] constexpr const Color aqua = rgb8_to_color(0,255,255);
[[maybe_unused]] constexpr const Color aquamarine = rgb8_to_color(127,255,212);
[[maybe_unused]] constexpr const Color azure = rgb8_to_color(240,255,255);
[[maybe_unused]] constexpr const Color beige = rgb8_to_color(245,245,220);
[[maybe_unused]] constexpr const Color bisque = rgb8_to_color(255,228,196);
[[maybe_unused]] constexpr const Color black = rgb8_to_color(0,0,0);
[[maybe_unused]] constexpr const Color blanchedalmond = rgb8_to_color(255,235,205);
[[maybe_unused]] constexpr const Color blue = rgb8_to_color(0,0,255);
[[maybe_unused]] constexpr const Color blueviolet = rgb8_to_color(138,43,226);
[[maybe_unused]] constexpr const Color brown = rgb8_to_color(165,42,42);
[[maybe_unused]] constexpr const Color burlywood = rgb8_to_color(222,184,135);
[[maybe_unused]] constexpr const Color cadetblue = rgb8_to_color(95,158,160);
[[maybe_unused]] constexpr const Color chartreuse = rgb8_to_color(127,255,0);
[[maybe_unused]] constexpr const Color chocolate = rgb8_to_color(210,105,30);
[[maybe_unused]] constexpr const Color coral = rgb8_to_color(255,127,80);
[[maybe_unused]] constexpr const Color cornflowerblue = rgb8_to_color(100,149,237);
[[maybe_unused]] constexpr const Color cornsilk = rgb8_to_color(255,248,220);
[[maybe_unused]] constexpr const Color crimson = rgb8_to_color(220,20,60);
[[maybe_unused]] constexpr const Color cyan = rgb8_to_color(0,255,255);
[[maybe_unused]] constexpr const Color darkblue = rgb8_to_color(0,0,139);
[[maybe_unused]] constexpr const Color darkcyan = rgb8_to_color(0,139,139);
[[maybe_unused]] constexpr const Color darkgoldenrod = rgb8_to_color(184,134,11);
[[maybe_unused]] constexpr const Color darkgray = rgb8_to_color(169,169,169);
[[maybe_unused]] constexpr const Color darkgreen = rgb8_to_color(0,100,0);
[[maybe_unused]] constexpr const Color darkgrey = rgb8_to_color(169,169,169);
[[maybe_unused]] constexpr const Color darkkhaki = rgb8_to_color(189,183,107);
[[maybe_unused]] constexpr const Color darkmagenta = rgb8_to_color(139,0,139);
[[maybe_unused]] constexpr const Color darkolivegreen = rgb8_to_color(85,107,47);
[[maybe_unused]] constexpr const Color darkorange = rgb8_to_color(255,140,0);
[[maybe_unused]] constexpr const Color darkorchid = rgb8_to_color(153,50,204);
[[maybe_unused]] constexpr const Color darkred = rgb8_to_color(139,0,0);
[[maybe_unused]] constexpr const Color darksalmon = rgb8_to_color(233,150,122);
[[maybe_unused]] constexpr const Color darkseagreen = rgb8_to_color(143,188,143);
[[maybe_unused]] constexpr const Color darkslateblue = rgb8_to_color(72,61,139);
[[maybe_unused]] constexpr const Color darkslategray = rgb8_to_color(47,79,79);
[[maybe_unused]] constexpr const Color darkslategrey = rgb8_to_color(47,79,79);
[[maybe_unused]] constexpr const Color darkturquoise = rgb8_to_color(0,206,209);
[[maybe_unused]] constexpr const Color darkviolet = rgb8_to_color(148,0,211);
[[maybe_unused]] constexpr const Color deeppink = rgb8_to_color(255,20,147);
[[maybe_unused]] constexpr const Color deepskyblue = rgb8_to_color(0,191,255);
[[maybe_unused]] constexpr const Color dimgray = rgb8_to_color(105,105,105);
[[maybe_unused]] constexpr const Color dimgrey = rgb8_to_color(105,105,105);
[[maybe_unused]] constexpr const Color dodgerblue = rgb8_to_color(30,144,255);
[[maybe_unused]] constexpr const Color firebrick = rgb8_to_color(178,34,34);
[[maybe_unused]] constexpr const Color floralwhite = rgb8_to_color(255,250,240);
[[maybe_unused]] constexpr const Color forestgreen = rgb8_to_color(34,139,34);
[[maybe_unused]] constexpr const Color fuchsia = rgb8_to_color(255,0,255);
[[maybe_unused]] constexpr const Color gainsboro = rgb8_to_color(220,220,220);
[[maybe_unused]] constexpr const Color ghostwhite = rgb8_to_color(248,248,255);
[[maybe_unused]] constexpr const Color gold = rgb8_to_color(255,215,0);
[[maybe_unused]] constexpr const Color goldenrod = rgb8_to_color(218,165,32);
[[maybe_unused]] constexpr const Color gray = rgb8_to_color(128,128,128);
[[maybe_unused]] constexpr const Color green = rgb8_to_color(0,128,0);
[[maybe_unused]] constexpr const Color greenyellow = rgb8_to_color(173,255,47);
[[maybe_unused]] constexpr const Color grey = rgb8_to_color(128,128,128);
[[maybe_unused]] constexpr const Color honeydew = rgb8_to_color(240,255,240);
[[maybe_unused]] constexpr const Color hotpink = rgb8_to_color(255,105,180);
[[maybe_unused]] constexpr const Color indianred = rgb8_to_color(205,92,92);
[[maybe_unused]] constexpr const Color indigo = rgb8_to_color(75,0,130);
[[maybe_unused]] constexpr const Color ivory = rgb8_to_color(255,255,240);
[[maybe_unused]] constexpr const Color khaki = rgb8_to_color(240,230,140);
[[maybe_unused]] constexpr const Color lavender = rgb8_to_color(230,230,250);
[[maybe_unused]] constexpr const Color lavenderblush = rgb8_to_color(255,240,245);
[[maybe_unused]] constexpr const Color lawngreen = rgb8_to_color(124,252,0);
[[maybe_unused]] constexpr const Color lemonchiffon = rgb8_to_color(255,250,205);
[[maybe_unused]] constexpr const Color lightblue = rgb8_to_color(173,216,230);
[[maybe_unused]] constexpr const Color lightcoral = rgb8_to_color(240,128,128);
[[maybe_unused]] constexpr const Color lightcyan = rgb8_to_color(224,255,255);
[[maybe_unused]] constexpr const Color lightgoldenrodyellow = rgb8_to_color(250,250,210);
[[maybe_unused]] constexpr const Color lightgray = rgb8_to_color(211,211,211);
[[maybe_unused]] constexpr const Color lightgreen = rgb8_to_color(144,238,144);
[[maybe_unused]] constexpr const Color lightgrey = rgb8_to_color(211,211,211);
[[maybe_unused]] constexpr const Color lightpink = rgb8_to_color(255,182,193);
[[maybe_unused]] constexpr const Color lightsalmon = rgb8_to_color(255,160,122);
[[maybe_unused]] constexpr const Color lightseagreen = rgb8_to_color(32,178,170);
[[maybe_unused]] constexpr const Color lightskyblue = rgb8_to_color(135,206,250);
[[maybe_unused]] constexpr const Color lightslategray = rgb8_to_color(119,136,153);
[[maybe_unused]] constexpr const Color lightslategrey = rgb8_to_color(119,136,153);
[[maybe_unused]] constexpr const Color lightsteelblue = rgb8_to_color(176,196,222);
[[maybe_unused]] constexpr const Color lightyellow = rgb8_to_color(255,255,224);
[[maybe_unused]] constexpr const Color lime = rgb8_to_color(0,255,0);
[[maybe_unused]] constexpr const Color limegreen = rgb8_to_color(50,205,50);
[[maybe_unused]] constexpr const Color linen = rgb8_to_color(250,240,230);
[[maybe_unused]] constexpr const Color magenta = rgb8_to_color(255,0,255);
[[maybe_unused]] constexpr const Color maroon = rgb8_to_color(128,0,0);
[[maybe_unused]] constexpr const Color mediumaquamarine = rgb8_to_color(102,205,170);
[[maybe_unused]] constexpr const Color mediumblue = rgb8_to_color(0,0,205);
[[maybe_unused]] constexpr const Color mediumorchid = rgb8_to_color(186,85,211);
[[maybe_unused]] constexpr const Color mediumpurple = rgb8_to_color(147,112,219);
[[maybe_unused]] constexpr const Color mediumseagreen = rgb8_to_color(60,179,113);
[[maybe_unused]] constexpr const Color mediumslateblue = rgb8_to_color(123,104,238);
[[maybe_unused]] constexpr const Color mediumspringgreen = rgb8_to_color(0,250,154);
[[maybe_unused]] constexpr const Color mediumturquoise = rgb8_to_color(72,209,204);
[[maybe_unused]] constexpr const Color mediumvioletred = rgb8_to_color(199,21,133);
[[maybe_unused]] constexpr const Color midnightblue = rgb8_to_color(25,25,112);
[[maybe_unused]] constexpr const Color mintcream = rgb8_to_color(245,255,250);
[[maybe_unused]] constexpr const Color mistyrose = rgb8_to_color(255,228,225);
[[maybe_unused]] constexpr const Color moccasin = rgb8_to_color(255,228,181);
[[maybe_unused]] constexpr const Color navajowhite = rgb8_to_color(255,222,173);
[[maybe_unused]] constexpr const Color navy = rgb8_to_color(0,0,128);
[[maybe_unused]] constexpr const Color oldlace = rgb8_to_color(253,245,230);
[[maybe_unused]] constexpr const Color olive = rgb8_to_color(128,128,0);
[[maybe_unused]] constexpr const Color olivedrab = rgb8_to_color(107,142,35);
[[maybe_unused]] constexpr const Color orange = rgb8_to_color(255,165,0);
[[maybe_unused]] constexpr const Color orangered = rgb8_to_color(255,69,0);
[[maybe_unused]] constexpr const Color orchid = rgb8_to_color(218,112,214);
[[maybe_unused]] constexpr const Color palegoldenrod = rgb8_to_color(238,232,170);
[[maybe_unused]] constexpr const Color palegreen = rgb8_to_color(152,251,152);
[[maybe_unused]] constexpr const Color paleturquoise = rgb8_to_color(175,238,238);
[[maybe_unused]] constexpr const Color palevioletred = rgb8_to_color(219,112,147);
[[maybe_unused]] constexpr const Color papayawhip = rgb8_to_color(255,239,213);
[[maybe_unused]] constexpr const Color peachpuff = rgb8_to_color(255,218,185);
[[maybe_unused]] constexpr const Color peru = rgb8_to_color(205,133,63);
[[maybe_unused]] constexpr const Color pink = rgb8_to_color(255,192,203);
[[maybe_unused]] constexpr const Color plum = rgb8_to_color(221,160,221);
[[maybe_unused]] constexpr const Color powderblue = rgb8_to_color(176,224,230);
[[maybe_unused]] constexpr const Color purple = rgb8_to_color(128,0,128);
[[maybe_unused]] constexpr const Color red = rgb8_to_color(255,0,0);
[[maybe_unused]] constexpr const Color rosybrown = rgb8_to_color(188,143,143);
[[maybe_unused]] constexpr const Color royalblue = rgb8_to_color(65,105,225);
[[maybe_unused]] constexpr const Color saddlebrown = rgb8_to_color(139,69,19);
[[maybe_unused]] constexpr const Color salmon = rgb8_to_color(250,128,114);
[[maybe_unused]] constexpr const Color sandybrown = rgb8_to_color(244,164,96);
[[maybe_unused]] constexpr const Color seagreen = rgb8_to_color(46,139,87);
[[maybe_unused]] constexpr const Color seashell = rgb8_to_color(255,245,238);
[[maybe_unused]] constexpr const Color sienna = rgb8_to_color(160,82,45);
[[maybe_unused]] constexpr const Color silver = rgb8_to_color(192,192,192);
[[maybe_unused]] constexpr const Color skyblue = rgb8_to_color(135,206,235);
[[maybe_unused]] constexpr const Color slateblue = rgb8_to_color(106,90,205);
[[maybe_unused]] constexpr const Color slategray = rgb8_to_color(112,128,144);
[[maybe_unused]] constexpr const Color slategrey = rgb8_to_color(112,128,144);
[[maybe_unused]] constexpr const Color snow = rgb8_to_color(255,250,250);
[[maybe_unused]] constexpr const Color springgreen = rgb8_to_color(0,255,127);
[[maybe_unused]] constexpr const Color steelblue = rgb8_to_color(70,130,180);
[[maybe_unused]] constexpr const Color tan = rgb8_to_color(210,180,140);
[[maybe_unused]] constexpr const Color teal = rgb8_to_color(0,128,128);
[[maybe_unused]] constexpr const Color thistle = rgb8_to_color(216,191,216);
[[maybe_unused]] constexpr const Color tomato = rgb8_to_color(255,99,71);
[[maybe_unused]] constexpr const Color turquoise = rgb8_to_color(64,224,208);
[[maybe_unused]] constexpr const Color violet = rgb8_to_color(238,130,238);
[[maybe_unused]] constexpr const Color wheat = rgb8_to_color(245,222,179);
[[maybe_unused]] constexpr const Color white = rgb8_to_color(255,255,255);
[[maybe_unused]] constexpr const Color whitesmoke = rgb8_to_color(245,245,245);
[[maybe_unused]] constexpr const Color yellow = rgb8_to_color(255,255,0);
[[maybe_unused]] constexpr const Color yellowgreen = rgb8_to_color(154,205,50);

} //namespace::color

} //namespace engine::graphics