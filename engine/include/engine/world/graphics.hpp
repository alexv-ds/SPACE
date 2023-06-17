#pragma once
#include <string>

namespace engine::world {

struct Renderable {};

struct Icon {
  std::string icon;
  std::string icon_state;
};

struct Layer {
  float layer = 0.0f;
};

struct Color {
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
};

struct Transparency {
  float alpha = 1.0f;
};

//color types
//https://www.w3.org/wiki/CSS/Properties/color/keywords
namespace color {

#define ENGINE_WORLD_RGB8_TO_RGB32(red,geen,blue)\
  {                                              \
    .r = static_cast<float>(red) / 255.0f,       \
    .g = static_cast<float>(geen) / 255.0f,      \
    .b = static_cast<float>(blue) / 255.0f       \
  }

[[maybe_unused]] constexpr const Color aliceblue = ENGINE_WORLD_RGB8_TO_RGB32(240,248,255);
[[maybe_unused]] constexpr const Color antiquewhite = ENGINE_WORLD_RGB8_TO_RGB32(250,235,215);
[[maybe_unused]] constexpr const Color aqua = ENGINE_WORLD_RGB8_TO_RGB32(0,255,255);
[[maybe_unused]] constexpr const Color aquamarine = ENGINE_WORLD_RGB8_TO_RGB32(127,255,212);
[[maybe_unused]] constexpr const Color azure = ENGINE_WORLD_RGB8_TO_RGB32(240,255,255);
[[maybe_unused]] constexpr const Color beige = ENGINE_WORLD_RGB8_TO_RGB32(245,245,220);
[[maybe_unused]] constexpr const Color bisque = ENGINE_WORLD_RGB8_TO_RGB32(255,228,196);
[[maybe_unused]] constexpr const Color black = ENGINE_WORLD_RGB8_TO_RGB32(0,0,0);
[[maybe_unused]] constexpr const Color blanchedalmond = ENGINE_WORLD_RGB8_TO_RGB32(255,235,205);
[[maybe_unused]] constexpr const Color blue = ENGINE_WORLD_RGB8_TO_RGB32(0,0,255);
[[maybe_unused]] constexpr const Color blueviolet = ENGINE_WORLD_RGB8_TO_RGB32(138,43,226);
[[maybe_unused]] constexpr const Color brown = ENGINE_WORLD_RGB8_TO_RGB32(165,42,42);
[[maybe_unused]] constexpr const Color burlywood = ENGINE_WORLD_RGB8_TO_RGB32(222,184,135);
[[maybe_unused]] constexpr const Color cadetblue = ENGINE_WORLD_RGB8_TO_RGB32(95,158,160);
[[maybe_unused]] constexpr const Color chartreuse = ENGINE_WORLD_RGB8_TO_RGB32(127,255,0);
[[maybe_unused]] constexpr const Color chocolate = ENGINE_WORLD_RGB8_TO_RGB32(210,105,30);
[[maybe_unused]] constexpr const Color coral = ENGINE_WORLD_RGB8_TO_RGB32(255,127,80);
[[maybe_unused]] constexpr const Color cornflowerblue = ENGINE_WORLD_RGB8_TO_RGB32(100,149,237);
[[maybe_unused]] constexpr const Color cornsilk = ENGINE_WORLD_RGB8_TO_RGB32(255,248,220);
[[maybe_unused]] constexpr const Color crimson = ENGINE_WORLD_RGB8_TO_RGB32(220,20,60);
[[maybe_unused]] constexpr const Color cyan = ENGINE_WORLD_RGB8_TO_RGB32(0,255,255);
[[maybe_unused]] constexpr const Color darkblue = ENGINE_WORLD_RGB8_TO_RGB32(0,0,139);
[[maybe_unused]] constexpr const Color darkcyan = ENGINE_WORLD_RGB8_TO_RGB32(0,139,139);
[[maybe_unused]] constexpr const Color darkgoldenrod = ENGINE_WORLD_RGB8_TO_RGB32(184,134,11);
[[maybe_unused]] constexpr const Color darkgray = ENGINE_WORLD_RGB8_TO_RGB32(169,169,169);
[[maybe_unused]] constexpr const Color darkgreen = ENGINE_WORLD_RGB8_TO_RGB32(0,100,0);
[[maybe_unused]] constexpr const Color darkgrey = ENGINE_WORLD_RGB8_TO_RGB32(169,169,169);
[[maybe_unused]] constexpr const Color darkkhaki = ENGINE_WORLD_RGB8_TO_RGB32(189,183,107);
[[maybe_unused]] constexpr const Color darkmagenta = ENGINE_WORLD_RGB8_TO_RGB32(139,0,139);
[[maybe_unused]] constexpr const Color darkolivegreen = ENGINE_WORLD_RGB8_TO_RGB32(85,107,47);
[[maybe_unused]] constexpr const Color darkorange = ENGINE_WORLD_RGB8_TO_RGB32(255,140,0);
[[maybe_unused]] constexpr const Color darkorchid = ENGINE_WORLD_RGB8_TO_RGB32(153,50,204);
[[maybe_unused]] constexpr const Color darkred = ENGINE_WORLD_RGB8_TO_RGB32(139,0,0);
[[maybe_unused]] constexpr const Color darksalmon = ENGINE_WORLD_RGB8_TO_RGB32(233,150,122);
[[maybe_unused]] constexpr const Color darkseagreen = ENGINE_WORLD_RGB8_TO_RGB32(143,188,143);
[[maybe_unused]] constexpr const Color darkslateblue = ENGINE_WORLD_RGB8_TO_RGB32(72,61,139);
[[maybe_unused]] constexpr const Color darkslategray = ENGINE_WORLD_RGB8_TO_RGB32(47,79,79);
[[maybe_unused]] constexpr const Color darkslategrey = ENGINE_WORLD_RGB8_TO_RGB32(47,79,79);
[[maybe_unused]] constexpr const Color darkturquoise = ENGINE_WORLD_RGB8_TO_RGB32(0,206,209);
[[maybe_unused]] constexpr const Color darkviolet = ENGINE_WORLD_RGB8_TO_RGB32(148,0,211);
[[maybe_unused]] constexpr const Color deeppink = ENGINE_WORLD_RGB8_TO_RGB32(255,20,147);
[[maybe_unused]] constexpr const Color deepskyblue = ENGINE_WORLD_RGB8_TO_RGB32(0,191,255);
[[maybe_unused]] constexpr const Color dimgray = ENGINE_WORLD_RGB8_TO_RGB32(105,105,105);
[[maybe_unused]] constexpr const Color dimgrey = ENGINE_WORLD_RGB8_TO_RGB32(105,105,105);
[[maybe_unused]] constexpr const Color dodgerblue = ENGINE_WORLD_RGB8_TO_RGB32(30,144,255);
[[maybe_unused]] constexpr const Color firebrick = ENGINE_WORLD_RGB8_TO_RGB32(178,34,34);
[[maybe_unused]] constexpr const Color floralwhite = ENGINE_WORLD_RGB8_TO_RGB32(255,250,240);
[[maybe_unused]] constexpr const Color forestgreen = ENGINE_WORLD_RGB8_TO_RGB32(34,139,34);
[[maybe_unused]] constexpr const Color fuchsia = ENGINE_WORLD_RGB8_TO_RGB32(255,0,255);
[[maybe_unused]] constexpr const Color gainsboro = ENGINE_WORLD_RGB8_TO_RGB32(220,220,220);
[[maybe_unused]] constexpr const Color ghostwhite = ENGINE_WORLD_RGB8_TO_RGB32(248,248,255);
[[maybe_unused]] constexpr const Color gold = ENGINE_WORLD_RGB8_TO_RGB32(255,215,0);
[[maybe_unused]] constexpr const Color goldenrod = ENGINE_WORLD_RGB8_TO_RGB32(218,165,32);
[[maybe_unused]] constexpr const Color gray = ENGINE_WORLD_RGB8_TO_RGB32(128,128,128);
[[maybe_unused]] constexpr const Color green = ENGINE_WORLD_RGB8_TO_RGB32(0,128,0);
[[maybe_unused]] constexpr const Color greenyellow = ENGINE_WORLD_RGB8_TO_RGB32(173,255,47);
[[maybe_unused]] constexpr const Color grey = ENGINE_WORLD_RGB8_TO_RGB32(128,128,128);
[[maybe_unused]] constexpr const Color honeydew = ENGINE_WORLD_RGB8_TO_RGB32(240,255,240);
[[maybe_unused]] constexpr const Color hotpink = ENGINE_WORLD_RGB8_TO_RGB32(255,105,180);
[[maybe_unused]] constexpr const Color indianred = ENGINE_WORLD_RGB8_TO_RGB32(205,92,92);
[[maybe_unused]] constexpr const Color indigo = ENGINE_WORLD_RGB8_TO_RGB32(75,0,130);
[[maybe_unused]] constexpr const Color ivory = ENGINE_WORLD_RGB8_TO_RGB32(255,255,240);
[[maybe_unused]] constexpr const Color khaki = ENGINE_WORLD_RGB8_TO_RGB32(240,230,140);
[[maybe_unused]] constexpr const Color lavender = ENGINE_WORLD_RGB8_TO_RGB32(230,230,250);
[[maybe_unused]] constexpr const Color lavenderblush = ENGINE_WORLD_RGB8_TO_RGB32(255,240,245);
[[maybe_unused]] constexpr const Color lawngreen = ENGINE_WORLD_RGB8_TO_RGB32(124,252,0);
[[maybe_unused]] constexpr const Color lemonchiffon = ENGINE_WORLD_RGB8_TO_RGB32(255,250,205);
[[maybe_unused]] constexpr const Color lightblue = ENGINE_WORLD_RGB8_TO_RGB32(173,216,230);
[[maybe_unused]] constexpr const Color lightcoral = ENGINE_WORLD_RGB8_TO_RGB32(240,128,128);
[[maybe_unused]] constexpr const Color lightcyan = ENGINE_WORLD_RGB8_TO_RGB32(224,255,255);
[[maybe_unused]] constexpr const Color lightgoldenrodyellow = ENGINE_WORLD_RGB8_TO_RGB32(250,250,210);
[[maybe_unused]] constexpr const Color lightgray = ENGINE_WORLD_RGB8_TO_RGB32(211,211,211);
[[maybe_unused]] constexpr const Color lightgreen = ENGINE_WORLD_RGB8_TO_RGB32(144,238,144);
[[maybe_unused]] constexpr const Color lightgrey = ENGINE_WORLD_RGB8_TO_RGB32(211,211,211);
[[maybe_unused]] constexpr const Color lightpink = ENGINE_WORLD_RGB8_TO_RGB32(255,182,193);
[[maybe_unused]] constexpr const Color lightsalmon = ENGINE_WORLD_RGB8_TO_RGB32(255,160,122);
[[maybe_unused]] constexpr const Color lightseagreen = ENGINE_WORLD_RGB8_TO_RGB32(32,178,170);
[[maybe_unused]] constexpr const Color lightskyblue = ENGINE_WORLD_RGB8_TO_RGB32(135,206,250);
[[maybe_unused]] constexpr const Color lightslategray = ENGINE_WORLD_RGB8_TO_RGB32(119,136,153);
[[maybe_unused]] constexpr const Color lightslategrey = ENGINE_WORLD_RGB8_TO_RGB32(119,136,153);
[[maybe_unused]] constexpr const Color lightsteelblue = ENGINE_WORLD_RGB8_TO_RGB32(176,196,222);
[[maybe_unused]] constexpr const Color lightyellow = ENGINE_WORLD_RGB8_TO_RGB32(255,255,224);
[[maybe_unused]] constexpr const Color lime = ENGINE_WORLD_RGB8_TO_RGB32(0,255,0);
[[maybe_unused]] constexpr const Color limegreen = ENGINE_WORLD_RGB8_TO_RGB32(50,205,50);
[[maybe_unused]] constexpr const Color linen = ENGINE_WORLD_RGB8_TO_RGB32(250,240,230);
[[maybe_unused]] constexpr const Color magenta = ENGINE_WORLD_RGB8_TO_RGB32(255,0,255);
[[maybe_unused]] constexpr const Color maroon = ENGINE_WORLD_RGB8_TO_RGB32(128,0,0);
[[maybe_unused]] constexpr const Color mediumaquamarine = ENGINE_WORLD_RGB8_TO_RGB32(102,205,170);
[[maybe_unused]] constexpr const Color mediumblue = ENGINE_WORLD_RGB8_TO_RGB32(0,0,205);
[[maybe_unused]] constexpr const Color mediumorchid = ENGINE_WORLD_RGB8_TO_RGB32(186,85,211);
[[maybe_unused]] constexpr const Color mediumpurple = ENGINE_WORLD_RGB8_TO_RGB32(147,112,219);
[[maybe_unused]] constexpr const Color mediumseagreen = ENGINE_WORLD_RGB8_TO_RGB32(60,179,113);
[[maybe_unused]] constexpr const Color mediumslateblue = ENGINE_WORLD_RGB8_TO_RGB32(123,104,238);
[[maybe_unused]] constexpr const Color mediumspringgreen = ENGINE_WORLD_RGB8_TO_RGB32(0,250,154);
[[maybe_unused]] constexpr const Color mediumturquoise = ENGINE_WORLD_RGB8_TO_RGB32(72,209,204);
[[maybe_unused]] constexpr const Color mediumvioletred = ENGINE_WORLD_RGB8_TO_RGB32(199,21,133);
[[maybe_unused]] constexpr const Color midnightblue = ENGINE_WORLD_RGB8_TO_RGB32(25,25,112);
[[maybe_unused]] constexpr const Color mintcream = ENGINE_WORLD_RGB8_TO_RGB32(245,255,250);
[[maybe_unused]] constexpr const Color mistyrose = ENGINE_WORLD_RGB8_TO_RGB32(255,228,225);
[[maybe_unused]] constexpr const Color moccasin = ENGINE_WORLD_RGB8_TO_RGB32(255,228,181);
[[maybe_unused]] constexpr const Color navajowhite = ENGINE_WORLD_RGB8_TO_RGB32(255,222,173);
[[maybe_unused]] constexpr const Color navy = ENGINE_WORLD_RGB8_TO_RGB32(0,0,128);
[[maybe_unused]] constexpr const Color oldlace = ENGINE_WORLD_RGB8_TO_RGB32(253,245,230);
[[maybe_unused]] constexpr const Color olive = ENGINE_WORLD_RGB8_TO_RGB32(128,128,0);
[[maybe_unused]] constexpr const Color olivedrab = ENGINE_WORLD_RGB8_TO_RGB32(107,142,35);
[[maybe_unused]] constexpr const Color orange = ENGINE_WORLD_RGB8_TO_RGB32(255,165,0);
[[maybe_unused]] constexpr const Color orangered = ENGINE_WORLD_RGB8_TO_RGB32(255,69,0);
[[maybe_unused]] constexpr const Color orchid = ENGINE_WORLD_RGB8_TO_RGB32(218,112,214);
[[maybe_unused]] constexpr const Color palegoldenrod = ENGINE_WORLD_RGB8_TO_RGB32(238,232,170);
[[maybe_unused]] constexpr const Color palegreen = ENGINE_WORLD_RGB8_TO_RGB32(152,251,152);
[[maybe_unused]] constexpr const Color paleturquoise = ENGINE_WORLD_RGB8_TO_RGB32(175,238,238);
[[maybe_unused]] constexpr const Color palevioletred = ENGINE_WORLD_RGB8_TO_RGB32(219,112,147);
[[maybe_unused]] constexpr const Color papayawhip = ENGINE_WORLD_RGB8_TO_RGB32(255,239,213);
[[maybe_unused]] constexpr const Color peachpuff = ENGINE_WORLD_RGB8_TO_RGB32(255,218,185);
[[maybe_unused]] constexpr const Color peru = ENGINE_WORLD_RGB8_TO_RGB32(205,133,63);
[[maybe_unused]] constexpr const Color pink = ENGINE_WORLD_RGB8_TO_RGB32(255,192,203);
[[maybe_unused]] constexpr const Color plum = ENGINE_WORLD_RGB8_TO_RGB32(221,160,221);
[[maybe_unused]] constexpr const Color powderblue = ENGINE_WORLD_RGB8_TO_RGB32(176,224,230);
[[maybe_unused]] constexpr const Color purple = ENGINE_WORLD_RGB8_TO_RGB32(128,0,128);
[[maybe_unused]] constexpr const Color red = ENGINE_WORLD_RGB8_TO_RGB32(255,0,0);
[[maybe_unused]] constexpr const Color rosybrown = ENGINE_WORLD_RGB8_TO_RGB32(188,143,143);
[[maybe_unused]] constexpr const Color royalblue = ENGINE_WORLD_RGB8_TO_RGB32(65,105,225);
[[maybe_unused]] constexpr const Color saddlebrown = ENGINE_WORLD_RGB8_TO_RGB32(139,69,19);
[[maybe_unused]] constexpr const Color salmon = ENGINE_WORLD_RGB8_TO_RGB32(250,128,114);
[[maybe_unused]] constexpr const Color sandybrown = ENGINE_WORLD_RGB8_TO_RGB32(244,164,96);
[[maybe_unused]] constexpr const Color seagreen = ENGINE_WORLD_RGB8_TO_RGB32(46,139,87);
[[maybe_unused]] constexpr const Color seashell = ENGINE_WORLD_RGB8_TO_RGB32(255,245,238);
[[maybe_unused]] constexpr const Color sienna = ENGINE_WORLD_RGB8_TO_RGB32(160,82,45);
[[maybe_unused]] constexpr const Color silver = ENGINE_WORLD_RGB8_TO_RGB32(192,192,192);
[[maybe_unused]] constexpr const Color skyblue = ENGINE_WORLD_RGB8_TO_RGB32(135,206,235);
[[maybe_unused]] constexpr const Color slateblue = ENGINE_WORLD_RGB8_TO_RGB32(106,90,205);
[[maybe_unused]] constexpr const Color slategray = ENGINE_WORLD_RGB8_TO_RGB32(112,128,144);
[[maybe_unused]] constexpr const Color slategrey = ENGINE_WORLD_RGB8_TO_RGB32(112,128,144);
[[maybe_unused]] constexpr const Color snow = ENGINE_WORLD_RGB8_TO_RGB32(255,250,250);
[[maybe_unused]] constexpr const Color springgreen = ENGINE_WORLD_RGB8_TO_RGB32(0,255,127);
[[maybe_unused]] constexpr const Color steelblue = ENGINE_WORLD_RGB8_TO_RGB32(70,130,180);
[[maybe_unused]] constexpr const Color tan = ENGINE_WORLD_RGB8_TO_RGB32(210,180,140);
[[maybe_unused]] constexpr const Color teal = ENGINE_WORLD_RGB8_TO_RGB32(0,128,128);
[[maybe_unused]] constexpr const Color thistle = ENGINE_WORLD_RGB8_TO_RGB32(216,191,216);
[[maybe_unused]] constexpr const Color tomato = ENGINE_WORLD_RGB8_TO_RGB32(255,99,71);
[[maybe_unused]] constexpr const Color turquoise = ENGINE_WORLD_RGB8_TO_RGB32(64,224,208);
[[maybe_unused]] constexpr const Color violet = ENGINE_WORLD_RGB8_TO_RGB32(238,130,238);
[[maybe_unused]] constexpr const Color wheat = ENGINE_WORLD_RGB8_TO_RGB32(245,222,179);
[[maybe_unused]] constexpr const Color white = ENGINE_WORLD_RGB8_TO_RGB32(255,255,255);
[[maybe_unused]] constexpr const Color whitesmoke = ENGINE_WORLD_RGB8_TO_RGB32(245,245,245);
[[maybe_unused]] constexpr const Color yellow = ENGINE_WORLD_RGB8_TO_RGB32(255,255,0);
[[maybe_unused]] constexpr const Color yellowgreen = ENGINE_WORLD_RGB8_TO_RGB32(154,205,50);

#undef ENGINE_WORLD_RGB8_TO_RGB32

} //namespace::color

} //end of namespace engine