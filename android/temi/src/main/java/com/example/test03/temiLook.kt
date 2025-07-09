package com.example.test03

enum class temiLook(val drawableId: Int, val order: Int) {
    WAIT(R.drawable.temi_wait,1),
    SPPECH(R.drawable.temi_speech,2),
    LOADING(R.drawable.temi_loading,3),
    RESPONSE(R.drawable.temi_speaking,4),
    STOP(R.drawable.temi_stop,5),
    RESPONETEXT(R.drawable.temi_response_text,999),
}