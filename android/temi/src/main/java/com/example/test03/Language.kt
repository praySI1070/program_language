package com.example.test03

import com.robotemi.sdk.TtsRequest.Language

enum class Language(val language: String,val languageCode: String,val ttsLanguageCode : Language,val gptLanguageCode:String) {
    KOREAN("한국어","korean", Language.KO_KR,"ko"),
    JAPANESE("日本語","japanese",Language.JA_JP,"ja"),
    CHINESE("中国人","chinese", Language.ZH_CN,"zh"),
    ENGLISH("English","english", Language.EN_US,"en");
}

enum class LanguageBubble(val phrases: Array<Pair<String, String>>) {
    KOREAN(
        arrayOf(
            "전시회에 대해서 질문하시려면" to "저를 클릭해주세요!",
            "궁금한 걸" to "음성으로 물어봐주세요!",
            "다시 질문하시려면" to "저를 클릭해주세요!"
        )
    ),
    JAPANESE(
        arrayOf(
            "展示会について質問したい場合は" to "私をクリック！",
            "質問音声で" to "教えてください！",
            "もう一度質問する" to "私をクリックしてください！"
        )
    ),
    CHINESE(
        arrayOf(
            "如果您对展览有任何问题" to "点击我！",
            "如果您有疑问" to "请通过语音提问！",
            "如果要重新提问" to "点击我！"
        )
    ),
    ENGLISH(
        arrayOf(
            "If you have questions about the exhibition" to "Please click me!",
            "If you're curious" to "Please ask via voice!",
            "If you'd like to ask again" to "Please click me!"
        )
    );

    fun getPhrase(index: Int): Pair<String, String> {
        return phrases.getOrElse(index) { "Unknown" to "Unknown" }
    }
}