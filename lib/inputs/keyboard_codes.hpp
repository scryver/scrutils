#ifndef SCRYVER_INPUTS_KEYBOARD_KEYS_HPP
#define SCRYVER_INPUTS_KEYBOARD_KEYS_HPP

#include <cstdint>

// Based mostly on glfw

namespace Scryver {

namespace Keys {

const uint16_t Unknown = 0xFFFF;

const uint16_t A = 0x0041;
const uint16_t B = 0x0042;
const uint16_t C = 0x0043;
const uint16_t D = 0x0044;
const uint16_t E = 0x0045;
const uint16_t F = 0x0046;
const uint16_t G = 0x0047;
const uint16_t H = 0x0048;
const uint16_t I = 0x0049;
const uint16_t J = 0x004A;
const uint16_t K = 0x004B;
const uint16_t L = 0x004C;
const uint16_t M = 0x004D;
const uint16_t N = 0x004E;
const uint16_t O = 0x004F;
const uint16_t P = 0x0050;
const uint16_t Q = 0x0051;
const uint16_t R = 0x0052;
const uint16_t S = 0x0053;
const uint16_t T = 0x0054;
const uint16_t U = 0x0055;
const uint16_t V = 0x0056;
const uint16_t W = 0x0057;
const uint16_t X = 0x0058;
const uint16_t Y = 0x0059;
const uint16_t Z = 0x005A;

const uint16_t Number_0 = 0x0030;
const uint16_t Number_1 = 0x0031;
const uint16_t Number_2 = 0x0032;
const uint16_t Number_3 = 0x0033;
const uint16_t Number_4 = 0x0034;
const uint16_t Number_5 = 0x0035;
const uint16_t Number_6 = 0x0036;
const uint16_t Number_7 = 0x0037;
const uint16_t Number_8 = 0x0038;
const uint16_t Number_9 = 0x0039;

const uint16_t Escape = 0x0100;
const uint16_t Return = 0x0101;
const uint16_t Space = 0x0020;
const uint16_t BackSpace = 0x0103;
const uint16_t Tab = 0x0102;

const uint16_t LeftControl = 0x0155;
const uint16_t LeftShift = 0x0154;
const uint16_t LeftAlt = 0x0156;
const uint16_t LeftSuper = 0x0157;
const uint16_t RightControl = 0x0159;
const uint16_t RightShift = 0x0158;
const uint16_t RightAlt = 0x015A;
const uint16_t RightSuper = 0x015B;
const uint16_t Menu = 0x015C;

const uint16_t Tilde = 0x0060;
const uint16_t Dash = 0x002D;
const uint16_t Equal = 0x003D;
const uint16_t LeftBracket = 0x005B;
const uint16_t RightBracket = 0x005D;
const uint16_t BackSlash = 0x005C;
const uint16_t SemiColon = 0x003B;
const uint16_t Quote = 0x0027;
const uint16_t Comma = 0x002C;
const uint16_t Period = 0x002E;
const uint16_t Slash = 0x002F;

const uint16_t PageUp = 0x010A;
const uint16_t PageDown = 0x010B;
const uint16_t Home = 0x010C;
const uint16_t End = 0x010D;
const uint16_t Insert = 0x0104;
const uint16_t Delete = 0x0105;

const uint16_t Left = 0x0107;
const uint16_t Right = 0x0106;
const uint16_t Up = 0x0109;
const uint16_t Down = 0x0108;

const uint16_t Numpad0 = 0x0140;
const uint16_t Numpad1 = 0x0141;
const uint16_t Numpad2 = 0x0142;
const uint16_t Numpad3 = 0x0143;
const uint16_t Numpad4 = 0x0144;
const uint16_t Numpad5 = 0x0145;
const uint16_t Numpad6 = 0x0146;
const uint16_t Numpad7 = 0x0147;
const uint16_t Numpad8 = 0x0148;
const uint16_t Numpad9 = 0x0149;

// const uint16_t NumpadDecimal = 0x014A;

const uint16_t Add = 0x014E;
const uint16_t Subtract = 0x014D;
const uint16_t Multiply = 0x014C;
const uint16_t Divide = 0x014B;

const uint16_t F1 = 0x0122;
const uint16_t F2 = 0x0123;
const uint16_t F3 = 0x0124;
const uint16_t F4 = 0x0125;
const uint16_t F5 = 0x0126;
const uint16_t F6 = 0x0127;
const uint16_t F7 = 0x0128;
const uint16_t F8 = 0x0129;
const uint16_t F9 = 0x012A;
const uint16_t F10 = 0x012B;
const uint16_t F11 = 0x012C;
const uint16_t F12 = 0x012D;
const uint16_t F13 = 0x012E;
const uint16_t F14 = 0x012F;
const uint16_t F15 = 0x0130;

const uint16_t Pause = 0x011C;

const uint8_t NUM_KEYS = 102;
}  // namespace Keys

}  // namespace Scryver

#endif  // SCRYVER_INPUTS_KEYBOARD_KEYS_HPP
