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

constexpr const Color aliceblue = rgb8_to_color(240,248,255);
constexpr const Color antiquewhite = rgb8_to_color(250,235,215);
constexpr const Color aqua = rgb8_to_color(0,255,255);
constexpr const Color aquamarine = rgb8_to_color(127,255,212);
constexpr const Color azure = rgb8_to_color(240,255,255);
constexpr const Color beige = rgb8_to_color(245,245,220);
constexpr const Color bisque = rgb8_to_color(255,228,196);
constexpr const Color black = rgb8_to_color(0,0,0);
constexpr const Color blanchedalmond = rgb8_to_color(255,235,205);
constexpr const Color blue = rgb8_to_color(0,0,255);
constexpr const Color blueviolet = rgb8_to_color(138,43,226);
constexpr const Color brown = rgb8_to_color(165,42,42);
constexpr const Color burlywood = rgb8_to_color(222,184,135);
constexpr const Color cadetblue = rgb8_to_color(95,158,160);
constexpr const Color chartreuse = rgb8_to_color(127,255,0);
constexpr const Color chocolate = rgb8_to_color(210,105,30);
constexpr const Color coral = rgb8_to_color(255,127,80);
constexpr const Color cornflowerblue = rgb8_to_color(100,149,237);
constexpr const Color cornsilk = rgb8_to_color(255,248,220);
constexpr const Color crimson = rgb8_to_color(220,20,60);
constexpr const Color cyan = rgb8_to_color(0,255,255);
constexpr const Color darkblue = rgb8_to_color(0,0,139);
constexpr const Color darkcyan = rgb8_to_color(0,139,139);
constexpr const Color darkgoldenrod = rgb8_to_color(184,134,11);
constexpr const Color darkgray = rgb8_to_color(169,169,169);
constexpr const Color darkgreen = rgb8_to_color(0,100,0);
constexpr const Color darkgrey = rgb8_to_color(169,169,169);
constexpr const Color darkkhaki = rgb8_to_color(189,183,107);
constexpr const Color darkmagenta = rgb8_to_color(139,0,139);
constexpr const Color darkolivegreen = rgb8_to_color(85,107,47);
constexpr const Color darkorange = rgb8_to_color(255,140,0);
constexpr const Color darkorchid = rgb8_to_color(153,50,204);
constexpr const Color darkred = rgb8_to_color(139,0,0);
constexpr const Color darksalmon = rgb8_to_color(233,150,122);
constexpr const Color darkseagreen = rgb8_to_color(143,188,143);
constexpr const Color darkslateblue = rgb8_to_color(72,61,139);
constexpr const Color darkslategray = rgb8_to_color(47,79,79);
constexpr const Color darkslategrey = rgb8_to_color(47,79,79);
constexpr const Color darkturquoise = rgb8_to_color(0,206,209);
constexpr const Color darkviolet = rgb8_to_color(148,0,211);
constexpr const Color deeppink = rgb8_to_color(255,20,147);
constexpr const Color deepskyblue = rgb8_to_color(0,191,255);
constexpr const Color dimgray = rgb8_to_color(105,105,105);
constexpr const Color dimgrey = rgb8_to_color(105,105,105);
constexpr const Color dodgerblue = rgb8_to_color(30,144,255);
constexpr const Color firebrick = rgb8_to_color(178,34,34);
constexpr const Color floralwhite = rgb8_to_color(255,250,240);
constexpr const Color forestgreen = rgb8_to_color(34,139,34);
constexpr const Color fuchsia = rgb8_to_color(255,0,255);
constexpr const Color gainsboro = rgb8_to_color(220,220,220);
constexpr const Color ghostwhite = rgb8_to_color(248,248,255);
constexpr const Color gold = rgb8_to_color(255,215,0);
constexpr const Color goldenrod = rgb8_to_color(218,165,32);
constexpr const Color gray = rgb8_to_color(128,128,128);
constexpr const Color green = rgb8_to_color(0,128,0);
constexpr const Color greenyellow = rgb8_to_color(173,255,47);
constexpr const Color grey = rgb8_to_color(128,128,128);
constexpr const Color honeydew = rgb8_to_color(240,255,240);
constexpr const Color hotpink = rgb8_to_color(255,105,180);
constexpr const Color indianred = rgb8_to_color(205,92,92);
constexpr const Color indigo = rgb8_to_color(75,0,130);
constexpr const Color ivory = rgb8_to_color(255,255,240);
constexpr const Color khaki = rgb8_to_color(240,230,140);
constexpr const Color lavender = rgb8_to_color(230,230,250);
constexpr const Color lavenderblush = rgb8_to_color(255,240,245);
constexpr const Color lawngreen = rgb8_to_color(124,252,0);
constexpr const Color lemonchiffon = rgb8_to_color(255,250,205);
constexpr const Color lightblue = rgb8_to_color(173,216,230);
constexpr const Color lightcoral = rgb8_to_color(240,128,128);
constexpr const Color lightcyan = rgb8_to_color(224,255,255);
constexpr const Color lightgoldenrodyellow = rgb8_to_color(250,250,210);
constexpr const Color lightgray = rgb8_to_color(211,211,211);
constexpr const Color lightgreen = rgb8_to_color(144,238,144);
constexpr const Color lightgrey = rgb8_to_color(211,211,211);
constexpr const Color lightpink = rgb8_to_color(255,182,193);
constexpr const Color lightsalmon = rgb8_to_color(255,160,122);
constexpr const Color lightseagreen = rgb8_to_color(32,178,170);
constexpr const Color lightskyblue = rgb8_to_color(135,206,250);
constexpr const Color lightslategray = rgb8_to_color(119,136,153);
constexpr const Color lightslategrey = rgb8_to_color(119,136,153);
constexpr const Color lightsteelblue = rgb8_to_color(176,196,222);
constexpr const Color lightyellow = rgb8_to_color(255,255,224);
constexpr const Color lime = rgb8_to_color(0,255,0);
constexpr const Color limegreen = rgb8_to_color(50,205,50);
constexpr const Color linen = rgb8_to_color(250,240,230);
constexpr const Color magenta = rgb8_to_color(255,0,255);
constexpr const Color maroon = rgb8_to_color(128,0,0);
constexpr const Color mediumaquamarine = rgb8_to_color(102,205,170);
constexpr const Color mediumblue = rgb8_to_color(0,0,205);
constexpr const Color mediumorchid = rgb8_to_color(186,85,211);
constexpr const Color mediumpurple = rgb8_to_color(147,112,219);
constexpr const Color mediumseagreen = rgb8_to_color(60,179,113);
constexpr const Color mediumslateblue = rgb8_to_color(123,104,238);
constexpr const Color mediumspringgreen = rgb8_to_color(0,250,154);
constexpr const Color mediumturquoise = rgb8_to_color(72,209,204);
constexpr const Color mediumvioletred = rgb8_to_color(199,21,133);
constexpr const Color midnightblue = rgb8_to_color(25,25,112);
constexpr const Color mintcream = rgb8_to_color(245,255,250);
constexpr const Color mistyrose = rgb8_to_color(255,228,225);
constexpr const Color moccasin = rgb8_to_color(255,228,181);
constexpr const Color navajowhite = rgb8_to_color(255,222,173);
constexpr const Color navy = rgb8_to_color(0,0,128);
constexpr const Color oldlace = rgb8_to_color(253,245,230);
constexpr const Color olive = rgb8_to_color(128,128,0);
constexpr const Color olivedrab = rgb8_to_color(107,142,35);
constexpr const Color orange = rgb8_to_color(255,165,0);
constexpr const Color orangered = rgb8_to_color(255,69,0);
constexpr const Color orchid = rgb8_to_color(218,112,214);
constexpr const Color palegoldenrod = rgb8_to_color(238,232,170);
constexpr const Color palegreen = rgb8_to_color(152,251,152);
constexpr const Color paleturquoise = rgb8_to_color(175,238,238);
constexpr const Color palevioletred = rgb8_to_color(219,112,147);
constexpr const Color papayawhip = rgb8_to_color(255,239,213);
constexpr const Color peachpuff = rgb8_to_color(255,218,185);
constexpr const Color peru = rgb8_to_color(205,133,63);
constexpr const Color pink = rgb8_to_color(255,192,203);
constexpr const Color plum = rgb8_to_color(221,160,221);
constexpr const Color powderblue = rgb8_to_color(176,224,230);
constexpr const Color purple = rgb8_to_color(128,0,128);
constexpr const Color red = rgb8_to_color(255,0,0);
constexpr const Color rosybrown = rgb8_to_color(188,143,143);
constexpr const Color royalblue = rgb8_to_color(65,105,225);
constexpr const Color saddlebrown = rgb8_to_color(139,69,19);
constexpr const Color salmon = rgb8_to_color(250,128,114);
constexpr const Color sandybrown = rgb8_to_color(244,164,96);
constexpr const Color seagreen = rgb8_to_color(46,139,87);
constexpr const Color seashell = rgb8_to_color(255,245,238);
constexpr const Color sienna = rgb8_to_color(160,82,45);
constexpr const Color silver = rgb8_to_color(192,192,192);
constexpr const Color skyblue = rgb8_to_color(135,206,235);
constexpr const Color slateblue = rgb8_to_color(106,90,205);
constexpr const Color slategray = rgb8_to_color(112,128,144);
constexpr const Color slategrey = rgb8_to_color(112,128,144);
constexpr const Color snow = rgb8_to_color(255,250,250);
constexpr const Color springgreen = rgb8_to_color(0,255,127);
constexpr const Color steelblue = rgb8_to_color(70,130,180);
constexpr const Color tan = rgb8_to_color(210,180,140);
constexpr const Color teal = rgb8_to_color(0,128,128);
constexpr const Color thistle = rgb8_to_color(216,191,216);
constexpr const Color tomato = rgb8_to_color(255,99,71);
constexpr const Color turquoise = rgb8_to_color(64,224,208);
constexpr const Color violet = rgb8_to_color(238,130,238);
constexpr const Color wheat = rgb8_to_color(245,222,179);
constexpr const Color white = rgb8_to_color(255,255,255);
constexpr const Color whitesmoke = rgb8_to_color(245,245,245);
constexpr const Color yellow = rgb8_to_color(255,255,0);
constexpr const Color yellowgreen = rgb8_to_color(154,205,50);

} //namespace::color

} //namespace engine::graphics