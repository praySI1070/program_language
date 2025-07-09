package com.example.test03

data class Argument(
    val language_code: String,
    val audio: String
)

data class RequestBody(
    val argument : Argument
)