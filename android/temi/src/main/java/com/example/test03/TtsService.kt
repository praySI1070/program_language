package com.example.test03

import android.app.Service
import android.content.Intent
import android.os.Binder
import android.os.IBinder
import android.util.Log
import com.robotemi.sdk.Robot
import com.robotemi.sdk.TtsRequest

class TtsService : Service() {
    private lateinit var robot: Robot
    private var languange:com. robotemi.sdk.TtsRequest.Language = com. robotemi.sdk.TtsRequest.Language.KO_KR

    override fun onCreate() {
        super.onCreate()
        Log.d("TtsService", "TtsService service onCreate")
        robot = Robot.Companion.getInstance()
    }

    override fun onBind(intent: Intent?): IBinder? {
        Log.d("TtsService", "TtsService service onBind")
        return Tts()
    }

    override fun onUnbind(intent: Intent?): Boolean {
        Log.d("TtsService", "TtsService service onUnbind")
        return super.onUnbind(intent)
    }

    fun ttsStart(inputText: String,inputLanguage:String) {
        Language.values().forEach { languagetype ->
            if(languagetype.language == inputLanguage) {
                languange = languagetype.ttsLanguageCode
            }
        }

        val ttsRequest = TtsRequest.Companion.create(
            inputText,
            false,
            language = TtsRequest.Language.KO_KR,
            showAnimationOnly = false,
            cached = false
        ).apply {}
        robot.speak(ttsRequest)
    }

    fun ttsStop() {
        robot.cancelAllTtsRequests()
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.d("TtsService", "TtsService service Destroy")
    }

    inner class Tts: Binder() {
        fun getTtsService() : TtsService = this@TtsService
    }
}