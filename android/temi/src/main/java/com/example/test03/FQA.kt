package com.example.test03

enum class FQA(val ko : String,val ja:String,val zh:String,val en:String) {
    FQA1("이 전시회는 무슨 전시회야?","この展覧会はどんな展示会ですか？","这是什么样的展览？","What kind of exhibition is this?"),
    FQA2("너는 누구야?","あなたは誰ですか？","你的角色是什么","what is your role"),
    FQA3("오늘 날씨는 어때?","今日の天気はどうですか？","今天的天气如何？","How is the weather today?"),
    FQA4("전시회를 관람할 수 있는 시간은 언제인가요?","展示会を観覧できる時間はいつですか？","今天展览几点结束？","What time does the exhibition end today?"),
    FQA5("전시회 기간은 언제까지인가요?","展示会はどのくらい行われますか？","展览持续多长时间","How long does the exhibition run?"),
    FQA6("전시회에서는 어떤 종류의 작품을 볼 수 있나요?","展覧会ではどのような作品を見ることができますか？","在展览中我可以看到什么样的作品？","What kind of works can I see at the exhibition?"),
    FQA7("전시회에서 사진을 찍을 수 있나요?","展示会で写真を撮ることはできますか？","我可以在展览会上拍照吗？","Can I take photos at the exhibition?");

    fun getParams(language : String) : List<String> {
        return when(language) {
            "한국어" -> listOf(ko)
            "日本語" -> listOf(ja)
            "中国人" -> listOf(zh)
            "English" -> listOf(en)
            else -> listOf("없음")
        }
    }
}

//안녕하세요! 저는 이 전시회의 설명을 맡고 있는 토리입니다! 궁금한게 있으시면 저를 클릭해서 물어보세요! 질문이 고민되신다면 말풍선 아래의 FQA버튼을 클릭해주세요.