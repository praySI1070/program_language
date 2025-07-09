package com.example.test03

data class RecognitionResult(
    val recognized : String
)

data class SttResponse(
    val request_id : String,
    val result : Int,
    val return_object: RecognitionResult? = null,
    val reason: String? = null
)
