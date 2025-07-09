package com.example.test03

import androidx.compose.ui.graphics.Color

enum class RGBColor(val red: Int, val green:Int, val blue:Int) {
    BLACK(0,0,0),
    RED(255,0,0),
    WHITE(255,255,255),
    BLUE(0,0,255),
    GREEN(0,255,0),
    ACTVATEBUTTON(47, 93, 255),
    ACTVATEBUTTONTEXT(255, 87, 34),
    DEACTIVATEBUTTON(73, 93, 146),
    Text(255,255,255),
    BACKGROUND(132, 202, 205),
    FQABACKGROUND (102, 172, 175),
    TEXTBOX(0,0,0);

    fun toColor() : Color {
        return Color(red = red, green = green, blue = blue)
    }
}