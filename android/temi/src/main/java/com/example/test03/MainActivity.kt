package com.example.test03


import android.content.ComponentName
import android.content.ServiceConnection
import androidx.core.content.ContextCompat
import android.content.pm.PackageManager
import androidx.core.app.ActivityCompat
import android.os.Bundle
import android.os.IBinder
import android.util.Log
//앱 내에서 컴포넌트 간의 작업을 요청하는 데 사용되는 객체
import android.content.Intent
//앱의 환경에 대한 정보를 제공하는 객체
import android.content.Context
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.getValue // mutableStateOf를 by키워드를 사용
import androidx.compose.runtime.setValue // mutableStateOf를 by키워드를 사용
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.foundation.gestures.detectTapGestures
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import coil3.ImageLoader
import com.example.test03.ui.theme.Test03Theme
import kotlinx.coroutines.*
import coil3.compose.rememberAsyncImagePainter
import coil3.request.ImageRequest
import coil3.request.CachePolicy
import androidx.compose.runtime.LaunchedEffect
import android.Manifest
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.runtime.rememberUpdatedState
import androidx.compose.ui.draw.alpha
import androidx.compose.ui.zIndex
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.ui.res.painterResource
import coil3.gif.GifDecoder
import androidx.compose.ui.text.TextStyle
import androidx. compose. ui. unit. sp
import androidx.compose.foundation.verticalScroll
import androidx.compose.foundation.rememberScrollState
import androidx. compose. foundation. layout. height
import androidx.compose.ui.text.style.TextAlign
import androidx. compose. ui. text. TextLayoutResult
import androidx. compose. ui. draw. clipToBounds
import androidx. compose. material3.ButtonDefaults
import androidx. compose. ui. layout. ContentScale
import androidx. compose. foundation. layout. Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.width
import androidx.compose.ui.text.font.FontWeight
import androidx. compose. material3.MaterialTheme
import androidx. compose. ui. draw. clip
import androidx. compose. foundation. shape. RoundedCornerShape
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.horizontalScroll
import androidx. compose. foundation. layout. offset
import androidx. compose. foundation. layout. size
import androidx.compose.ui.graphics.Path
import androidx.compose.ui.graphics.drawscope.DrawScope
import androidx. compose. ui. graphics. nativeCanvas
import androidx.compose.ui.tooling.preview.Preview
import androidx. compose. ui. graphics. graphicsLayer
import androidx. compose. ui. unit. IntSize
import androidx. compose. ui. layout. onSizeChanged


class MainActivity : ComponentActivity() {
    private var RecordService: GetVoice?=null
    private var isRecordServiceBound = false
    private var ttsService: TtsService? = null
    private var isTtsServiceBound = false
    private var speeachFinish = ""

    private val RecordServiceConnect = object:ServiceConnection {
        override fun onServiceConnected(p0: ComponentName?, p1: IBinder?) {
            val binder = p1 as GetVoice.Record
            RecordService = binder.getService()
            isRecordServiceBound = true
            Log.d("Main", "레코드 서비스 연결완료")
        }

        //서비스와의 연결이 종료되면 자동으로 호출되는 서비스
        //예기치 않게 종료되었거나, 바인딩이 끊어졌을 떄 호출
        override fun onServiceDisconnected(p0: ComponentName?) {
            isRecordServiceBound = false
            Log.d("Main", "레코드 서비스 연결해제")
        }
    }

    private val ttsServiceConnection = object : ServiceConnection {
        override fun onServiceConnected(name: ComponentName?, service: IBinder?) {
            val binder = service as TtsService.Tts
            ttsService = binder.getTtsService()
            isTtsServiceBound = true
            Log.d("Main", "TTS 서비스 연결완료")
        }

        override fun onServiceDisconnected(name: ComponentName?) {
            isTtsServiceBound = false
            Log.d("Main", "TTS 서비스 연결해제")
        }
    }

    /*
    compose에서는 기존의 view를 상속받는게아니라서 애초에 안되요.
    override fun onTouchEvent(event: MotionEvent?): Boolean*/



    suspend fun callbackMainframe(point:String, languageCode : String): String {
        var recordVoice : String = ""
        Log.d("callback Mainframe", "callbackMainframe 시작")

        if(point == "speeachscreen") {
            //그 작업이 끝날 때까지 현재 코루틴을 일시 정지시키는 역할
            //withContext 내에서 실행된 코드가 모두 완료된 후에 그 결과를 반환하고,
            //코루틴이 자동으로 종료됩니다.
            speeachFinish = withContext(Dispatchers.IO) {
                // test() 함수에서 반환값이 있다고 가정
                //실재 사용 함수
                RecordService?.test(languageCode) ?: "녹음 작업 실패"

                //디버그용 테스트 함수
                //RecordService?.uiTest() ?: "녹음작업실패"
            }

            withContext(Dispatchers.IO) {
                ttsService?.ttsStart(speeachFinish,languageCode)
            }

            if(speeachFinish == "apoktmwodoso") {
                Log.d("서비스 버퍼 설정 이상함.","버퍼 설정이상함")
                exitApp()
            }

            recordVoice = speeachFinish
            Log.d("callbackMainframe", "recordVoice : $recordVoice")

        } else if(point == "loadingScreen") {
            Log.d("loadingScreen", "gpt작업 시작")
            speeachFinish = withContext(Dispatchers.IO) {
                // test() 함수에서 반환값이 있다고 가정
                //실제 사용 함수
                RecordService?.callGptAndGetResponse(speeachFinish,languageCode) ?: "gpt해석 작업 실패"

                //테스트 디버그용 함수
                //RecordService?.uiTest02(speeachFinish)?:"gpt 해석작업실패"
            }
            withContext(Dispatchers.IO) {
                ttsService?.ttsStart(speeachFinish,languageCode)
            }
            Log.d("loadingScreen", "gpt작업 완료")
        } else if(point == "FQAcallBack") {
            val test = languageCode.split("-")
            Log.d("loadingScreen", "FQAcallBack 시작")
            Log.d("FQAcallBack","test : ${test[0]}, ${test[1]}")
            speeachFinish = withContext(Dispatchers.IO) {
                // test() 함수에서 반환값이 있다고 가정
                //실제 사용 함수
                RecordService?.callGptAndGetResponse(test[0],test[1]) ?: "gpt해석 작업 실패"

                //테스트 디버그용 함수
                //RecordService?.uiTest02(speeachFinish)?:"gpt 해석작업실패"
            }
            withContext(Dispatchers.IO) {
                ttsService?.ttsStart(speeachFinish,languageCode)
            }
            Log.d("loadingScreen", "FQAcallBack 완료")

        } else if(point == "stop") {
            ttsService?.ttsStop()
            return "true"
        } else if(point == "appExit") {
            exitApp()
        } else if(point == "stoptest") {
            withContext(Dispatchers.IO) {
                RecordService?.stopTest()
            }
        }
        Log.d("callbackMainframe", "speeachFinish : $speeachFinish")

        return speeachFinish
    }

    private fun exitApp() {
        RecordService?.onDestroy()
        ttsService?.onDestroy()
        finish()
    }

    fun checkpermission() {
        // 권한 요청
        val permissionsToRequest = mutableListOf<String>()

        // RECORD_AUDIO 권한 확인
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
            permissionsToRequest.add(Manifest.permission.RECORD_AUDIO)
        }

        // WRITE_EXTERNAL_STORAGE 권한 확인
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            permissionsToRequest.add(Manifest.permission.WRITE_EXTERNAL_STORAGE)
        }

        // 권한이 부족하다면 요청
        if (permissionsToRequest.isNotEmpty()) {
            ActivityCompat.requestPermissions(
                this,
                permissionsToRequest.toTypedArray(),
                100 // 요청 코드
            )
        } else {
            Log.d("Main", "모든 권한 확인됨")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        checkpermission()

        val recordServiceIntent = Intent(this, GetVoice::class.java)
        /*bindService의 3번쨰 인자의 종류
        1. Context.BIND_AUTO_CREATE
            서비스가 자동으로 실행되게 함. 끊겨있으면 다시연결, 아니면 연결
        2. Context.BIND_ABOVE_CLIENT
            바인딩 될 때 우선순위가 높은 작업을 요구
        3. Context.BIND_ADJUST_WITH_ACTIVITY
            바인딩된 서비스가 액티비티 상태에 따라 적절히 조정되게 설정
        4. Context.BIND_NOT_FOREGROUND
            서비스가 백그라운드에서 실행될 수 있게 함 / 포그라운드서비스로 시작x
        */
        bindService(recordServiceIntent, RecordServiceConnect, Context.BIND_AUTO_CREATE)
        val ttsServiceIntent = Intent(this, TtsService::class.java)
        bindService(ttsServiceIntent, ttsServiceConnection,Context.BIND_AUTO_CREATE)



        enableEdgeToEdge()
        setContent {
            Test03Theme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    // mainFrame 함수 호출
                    mainFrame(
                        modifier = Modifier,
                        innerPadding,
                        ::callbackMainframe
                    )
                }
            }
        }
    }
}

@Composable
fun mainFrame(
    modifier: Modifier = Modifier,
    innerPadding: PaddingValues,
    callbackMainframe: suspend (String,String)->String) {
    //remember는 재구성이 되어도 값을 저장해줌
    //mutableStateOf는 읽기와 쓰기를 관찰하기 위해 사용.
    //그냥 값을 넣으면 변경할 때는 .value를 통해서 넣어야함.
    //1 : 대기, 2 : 녹음, 3 : 로딩, 4 : 대답 , 5 : 정지
    var nowScreen by remember { mutableIntStateOf(temiLook.WAIT.order) }
    //by를 사용하면 직접적으로 값을 넣을 수 있음.
    var checkLoadGifMainFrame : Int  = 0
    var isStop by remember { mutableStateOf("") }
    var showGif by remember { mutableIntStateOf(R.drawable.temi_wait) }
    var showText by remember { mutableStateOf(false) }
    var showExitButton by remember { mutableStateOf(true) }
    var languageMode by remember { mutableStateOf(Language.KOREAN.language) }
    var callbackMainframeString by remember {mutableStateOf("aiosdjflsdjf")}
    var showBubble by remember { mutableStateOf(true) }
    var bubbleText by remember { mutableStateOf(LanguageBubble.KOREAN) }
    var showFQA by remember { mutableStateOf(false) }

    LaunchedEffect(callbackMainframeString) {
        Log.d("mainFrame", "callbackMainframeString변화 : $callbackMainframeString")
        if(callbackMainframeString == "aiosdjflsdjf") {
            callbackMainframeString = ""
        }
        else if(callbackMainframeString == "") {

        }
        else if(nowScreen == temiLook.LOADING.order) {
            showText = true
            showFQA = false
            nowScreen = temiLook.RESPONSE.order
        }
        else {
            showText = true
            showFQA = false
            nowScreen = temiLook.RESPONSE.order
        }

    }


    fun gifLoadCallback(checkLoadGif:Int) {
        if(checkLoadGif != checkLoadGifMainFrame) {
            checkLoadGifMainFrame = checkLoadGif
            Log.d("gifLoadCallback", "checkLoadGifMainFrame : $checkLoadGifMainFrame")
        }
    }

    fun languageModeCallback(Mode:String) {
        if(languageMode != Mode) {
            languageMode = Mode
            Log.d("languageModeCallback","languageMode : $languageMode")

            when(languageMode) {
                "한국어" -> {
                    bubbleText = LanguageBubble.KOREAN
                }
                "日本語" -> {
                    bubbleText = LanguageBubble.JAPANESE
                }
                "中国人" -> {
                    bubbleText = LanguageBubble.CHINESE
                }
                "English" -> {
                    bubbleText = LanguageBubble.ENGLISH
                }
            }
        }
    }

    fun FQAcallBack(message:String) {
        CoroutineScope(Dispatchers.IO).launch {
            Log.d("FQAcallBack","FQA로 실행")
            showBubble = false
            nowScreen = temiLook.LOADING.order
            
            callbackMainframeString = async {
                callbackMainframe("FQAcallBack", message+"-"+languageMode)
            }.await()

            showBubble = true

            Log.d("FQAcallBack","FQA로 실행 완료")
        }
    }

    // Column을 수평, 수직으로 중앙 정렬
    Column(
        modifier = modifier
            .fillMaxSize()
            .background(color = RGBColor.BACKGROUND.toColor())
            //화면 터치
            .pointerInput(Unit) {
                detectTapGestures(
                    onTap = { offset ->
                        Log.d("ClickableBox", "Tapped at: $offset")
                        Log.d("스크린 상태", "nowScreen : $nowScreen")
                        if (showFQA) {
                            showFQA = false
                        } else if (nowScreen == temiLook.WAIT.order) {
                            Log.d("touch - waitscreen", "시작")
                            showExitButton = false
                            nowScreen = temiLook.SPPECH.order



                            CoroutineScope(Dispatchers.IO).launch {
                                Log.d("Touch - globalscope", "1개 실행.")
                                callbackMainframeString = async {
                                    callbackMainframe("speeachscreen", languageMode)
                                }.await()
                                showBubble = false


                                var delaytime: Long =
                                    (((callbackMainframeString.length) / 3) * 1000).toLong()
                                if (delaytime <= 5000) {
                                    delaytime = 5000
                                }
                                delay(delaytime)
                                Log.d("Touch - globalscope", "1개 실행 완 다음꺼 실행.")


                                showText = false
                                nowScreen = temiLook.LOADING.order

                                callbackMainframeString = async {
                                    callbackMainframe("loadingScreen", languageMode)
                                }.await()

                                showBubble = true

                                Log.d("Touch - globalscope", "2개 실행 완.")
                            }
                        } else if (nowScreen == temiLook.RESPONSE.order && isStop == "") {
                            Log.d("touch - RESPONSE", "다시 돌리기")
                            CoroutineScope(Dispatchers.IO).launch {
                                isStop = async {
                                    callbackMainframe("stop", "")
                                }.await()
                                if (isStop == "true") {
                                    showText = false
                                    nowScreen = temiLook.WAIT.order
                                    isStop = ""
                                }
                            }
                        }
                    }
                )
            }
            .padding(innerPadding)      // innerPadding을 Modifier.padding으로 변경
        ,
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        when (nowScreen + checkLoadGifMainFrame) {
            temiLook.WAIT.order  -> {
                Log.d("when - nowScreen","대기스크린")
                showExitButton = true
                showGif = temiLook.WAIT.drawableId
            }
            temiLook.SPPECH.order -> {
                Log.d("when - nowScreen","마이크스크린")
                showGif = temiLook.SPPECH.drawableId
            }
            temiLook.LOADING.order -> {
                showText = false
                Log.d("when - nowScreen","로딩스크린")
                Image(
                    painter = painterResource(id = R.drawable.temi_loadingimg),  // 배경 이미지 설정
                    contentDescription = null,
                    modifier = Modifier
                        .fillMaxSize()  // 배경 이미지가 화면을 가득 채우도록 설정
                        .zIndex(0.7f),
                    contentScale = ContentScale.Crop
                )

            }
            temiLook.RESPONSE.order -> {
                Log.d("when - nowScreen","대답 스크린")
                showGif = temiLook.RESPONSE.drawableId
            }
            temiLook.STOP.order -> {
                Log.d("when - nowScreen","정지 스크린")
            }
        }


        Box(
            modifier = modifier
                .fillMaxWidth()
                .weight(0.8f)
                .background(RGBColor.BACKGROUND.toColor())
            ,
            contentAlignment = Alignment.BottomStart
        ) {
            // 백그라운드 이미지
            Image(
                painter = painterResource(id = R.drawable.temi_loadingimg),  // 배경 이미지 설정
                contentDescription = null,
                modifier = Modifier
                    .fillMaxSize()  // 배경 이미지가 화면을 가득 채우도록 설정
                    .zIndex(0f),
                contentScale = ContentScale.Crop
            )


            if(nowScreen == temiLook.SPPECH.order) {
                Row(
                    modifier = modifier
                        .fillMaxWidth(0.55f)
                        .fillMaxHeight(0.2f)
                        .background(RGBColor.RED.toColor())
                        .zIndex(1.2f)
                    ,
                    horizontalArrangement = Arrangement.End, // 가로는 끝으로 정렬
                    verticalAlignment = Alignment.Top // 세로는 위쪽으로 정렬
                ) {
                    Button(
                        onClick = {
                            CoroutineScope(Dispatchers.IO).launch {
                                callbackMainframe("stopTest","")
                            }
                        },
                        modifier = modifier
                            .fillMaxWidth(0.2f)
                            .fillMaxHeight(0.4f)
                    ) {
                        Text(
                            text = "완료",
                            fontWeight = FontWeight.Bold,
                            fontSize = 30.sp
                        )
                    }
                }
            }

            if(showFQA) {
                Row(
                    modifier = modifier
                        .fillMaxSize()
                        .background(RGBColor.BACKGROUND.toColor())
                        .zIndex(1.2f)
                        ,
                    horizontalArrangement = Arrangement.Center, // 수평 중앙 정렬
                    verticalAlignment = Alignment.CenterVertically // 수직 중앙 정렬
                ) {
                    FQA(modifier,languageMode,::FQAcallBack)
                }
            }

            if(showBubble) {
                Column(
                    modifier = modifier
                        .zIndex(0.9f)
                        .fillMaxHeight(0.85f)
                        .fillMaxWidth(0.35f)
                        ,
                    verticalArrangement = Arrangement.Top,
                    horizontalAlignment = Alignment.End
                ) {
                    Box(
                        modifier = modifier
                            .fillMaxWidth(0.8f)
                            .fillMaxHeight(0.5f)
                            .background(RGBColor.BLUE.toColor())
                    ) {


                        when(nowScreen) {
                            temiLook.WAIT.order -> {
                                SpeechBubbleWithRotatedTail(modifier = modifier.fillMaxSize(),bubbleText.getPhrase(0).first ,bubbleText.getPhrase(0).second)
                            }
                            temiLook.SPPECH.order -> {
                                SpeechBubbleWithRotatedTail(modifier = modifier.fillMaxSize(),bubbleText.getPhrase(1).first ,bubbleText.getPhrase(1).second)
                            }
                            temiLook.RESPONSE.order -> {
                                SpeechBubbleWithRotatedTail(modifier = modifier.fillMaxSize(),bubbleText.getPhrase(2).first ,bubbleText.getPhrase(2).second)
                            }
                        }
                    }

                    if(nowScreen == temiLook.WAIT.order) {
                        Row(
                            modifier = modifier
                                .fillMaxHeight(0.3f)
                                .fillMaxWidth(1.0f)
                                .zIndex(0.9f)
                                .background(RGBColor.BACKGROUND.toColor())
                            ,
                            horizontalArrangement = Arrangement.End,
                            verticalAlignment = Alignment.Top
                        ) {
                            Spacer(modifier = modifier
                                .weight(0.15f)
                            )
                            Button(
                                onClick = {
                                    showFQA = true
                                },
                                modifier = modifier
                                    .weight(0.1f)
                                    .fillMaxHeight(1.0f)
                            ) {
                                Text(
                                    text = "FQA",
                                    fontWeight = FontWeight.Bold,
                                    fontSize = 30.sp
                                )
                            }
                            Spacer(modifier = modifier
                                .weight(0.1f)
                            )
                        }
                    }
                }
            }


            OverlayImages(
                modifier = modifier,
                showGif,
                0.5f,
                ::gifLoadCallback
            )
            if(showText) {
                showTextBubble(
                    modifier = modifier,
                    zIndex = 0.8f,
                    text = callbackMainframeString
                )
            }
        }

        if(nowScreen == temiLook.WAIT.order) {
            Box(
                modifier = modifier
                    .fillMaxWidth()
                    .weight(0.2f)
                    .background(color = RGBColor.BACKGROUND.toColor())
                    .padding(start = 100.dp, end = 100.dp),
            ) {
                Row(
                    modifier = modifier
                        .fillMaxSize()
                        .background(color = RGBColor.BACKGROUND.toColor()),
                    horizontalArrangement = Arrangement.SpaceEvenly
                ) {
                    if(showExitButton) {
                        changeLanguage(
                            modifier = modifier.weight(0.1f),
                            ::languageModeCallback
                        )
                        exitAppButton(
                            modifier = modifier.weight(0.1f),
                            "EXIT",
                            callbackMainframe
                        )

                    }
                }
            }
        }
    }
}

@Composable
fun FQA(
    modifier: Modifier,
    languageMode:String,
    FQAcallBack: (String)->Unit
) {
    val scrollState = rememberScrollState()
    val Language = rememberUpdatedState(languageMode)

    Column(
        modifier = modifier
            .fillMaxSize(0.8f)
            .background(RGBColor.FQABACKGROUND.toColor())
            .verticalScroll(scrollState)  // 수직 스크롤
            ,
            verticalArrangement = Arrangement
                .spacedBy(15.dp)
        ,
            horizontalAlignment = Alignment.CenterHorizontally
    ) {
        FQA.values().forEach { fqas ->
            fqas.getParams(Language.value).forEach { fqa ->
                Button(
                    onClick = {
                        FQAcallBack(fqa)
                    },
                    modifier = modifier
                        .height(80.dp)
                        .fillMaxWidth(0.8f)
                    ,
                    colors = ButtonDefaults.buttonColors(
                        containerColor = RGBColor.WHITE.toColor(),  // 버튼 배경색
                        contentColor = RGBColor.BACKGROUND.toColor()    // 버튼 텍스트 색상
                    )
                ) {
                    Text(
                        text = fqa,
                        fontWeight = FontWeight.Bold,
                        fontSize = 30.sp
                    )
                }
            }

        }
    }
}

@Composable
fun SpeechBubbleWithRotatedTail(
    modifier: Modifier,
    Text1 : String,
    Text2 : String
) {
    var boxSize by remember { mutableStateOf(IntSize(0, 0)) }

    Box(
        modifier = modifier
            .onSizeChanged { size ->
                boxSize = size // Box의 크기를 state로 저장
            }
            .background(RGBColor.BACKGROUND.toColor())
            .fillMaxSize()
    )

    Canvas(modifier = modifier.fillMaxSize()) {
        // 타원형 본체 그리기
        drawOval(
            color = RGBColor.WHITE.toColor(),
            topLeft = androidx.compose.ui.geometry.Offset(0f, 0f),
            size = size.copy(width = size.width, height = size.height * 0.8f) // 타원의 크기
        )

        val path = Path().apply {
            // 경로 시작: 첫 번째 점 (86% 55%)
            moveTo(0.86f * size.width, 0.55f * size.height)

            // 두 번째 점 (89% 66%)
            lineTo(0.89f * size.width, 0.66f * size.height)

            // 세 번째 점 (100% 85%)
            lineTo(size.width, 0.85f * size.height)

            // 네 번째 점 (78% 75%)
            lineTo(0.78f * size.width, 0.75f * size.height)

            // 다섯 번째 점 (73% 63%)
            lineTo(0.73f * size.width, 0.63f * size.height)

            // 경로 닫기
            close()
        }

        drawPath(
            path = path,
            color = RGBColor.WHITE.toColor(),
        )

        // 텍스트 추가 (말풍선 안에 텍스트)
        drawContext.canvas.nativeCanvas.apply {
            drawText(
                Text1, // 텍스트 내용
                size.width / 2, // X 좌표 (가운데 정렬)
                size.height * 0.35f, // Y 좌표 (타원 중앙 근처)
                android.graphics.Paint().apply {
                    color = android.graphics.Color.BLACK
                    textSize = 40f
                    textAlign = android.graphics.Paint.Align.CENTER
                }
            )
            drawText(
                Text2, // 텍스트 내용
                size.width / 2, // X 좌표 (가운데 정렬)
                size.height * 0.55f, // Y 좌표 (타원 중앙 근처)
                android.graphics.Paint().apply {
                    color = android.graphics.Color.BLACK
                    textSize = 40f
                    textAlign = android.graphics.Paint.Align.CENTER
                }
            )
        }
    }
}

@Composable
fun exitAppButton(
    modifier: Modifier,
    text : String,
    callbackMainframe: suspend (String,String)->String
) {
    Button(
        onClick = {
            CoroutineScope(Dispatchers.Unconfined).launch {
                callbackMainframe("appExit","없음")
            }
        },
        modifier = modifier
            .fillMaxHeight(0.9f)
            ,
        colors = ButtonDefaults.buttonColors(
            containerColor = RGBColor.RED.toColor(),  // 버튼 배경색
            contentColor = RGBColor.BLACK.toColor()    // 버튼 텍스트 색상
        )
    ) {
        Text(
            text = text,
            fontWeight = FontWeight.Bold,
            fontSize = 30.sp
        ) // 버튼 텍스트
    }
}

@Composable
fun changeLanguage(
    modifier: Modifier,
    languageModeCallback : (languageMode:String) ->Unit
) {
    var onButton by remember { mutableStateOf(Language.KOREAN.language) }


    Language.values().forEach { button ->
        Button(
            onClick = {
                onButton = button.language
                languageModeCallback(onButton)
            },
            modifier = modifier
                .fillMaxHeight(0.9f)
            ,
            colors = ButtonDefaults.buttonColors(
                containerColor = if(onButton == button.language) RGBColor.ACTVATEBUTTON.toColor() else RGBColor.DEACTIVATEBUTTON.toColor(),  // 버튼 배경색
                contentColor = if(onButton == button.language) RGBColor.ACTVATEBUTTONTEXT.toColor() else RGBColor.WHITE.toColor()   // 버튼 텍스트 색상
            )
        ) {
            Text(
                text = button.language,
                fontWeight = FontWeight.Bold,
                fontSize = 30.sp
            )  // Enum의 label 값을 버튼 텍스트로 사용
        }
        Spacer(modifier = Modifier.width(50.dp))
    }
}

@Composable
fun OverlayImages(
    modifier: Modifier,
    showGif : Int,
    zIndex: Float,
    gifLoadCallback:(checkLoadGif:Int) -> Unit
) {
    val currentGif by rememberUpdatedState(showGif)
    var gifToShow by remember { mutableIntStateOf(temiLook.WAIT.drawableId) }

    LaunchedEffect(currentGif) {
        gifToShow = currentGif
        Log.d("currentGif", "currentGif : $currentGif")
    }

    Box(
        modifier = modifier
            .fillMaxSize()
            .zIndex(zIndex)
    ) {
        GifImage(
            modifier = modifier,
            drawableId = gifToShow,
            zIndex = zIndex,  // 텍스트 박스보다 아래에 배치
            gifLoadCallback = gifLoadCallback
        )
    }
}

@Composable
fun showTextBubble(
    modifier: Modifier,
    zIndex :Float,
    text :String
) {
    val currenttext by rememberUpdatedState(text)
    var displayedText by remember { mutableStateOf("") }
    val scrollState = rememberScrollState()
    var test by remember { mutableStateOf(0) }

    LaunchedEffect(currenttext) {
        // 텍스트가 하나씩 나타나는 애니메이션
        for (i in currenttext.indices) {
            displayedText = text.take(i + 1)
            delay(100)  // 글자가 나타날 시간 간격 (100ms)
        }
    }

    LaunchedEffect(test) {
        scrollState.scrollTo(test)
    }

    Box(
        modifier = modifier
            .fillMaxWidth()
            .fillMaxHeight(0.2f)
            .zIndex(zIndex),
            contentAlignment = Alignment.TopCenter
    ) {
        Box(
            modifier = modifier
                .fillMaxWidth()
                .height(10.dp)
                .background(color = RGBColor.WHITE.toColor())
                .zIndex(zIndex + 0.1f)
                .alpha(0.7f)
        )

        Box(
            modifier = modifier
                .fillMaxWidth()
                .fillMaxHeight()
                .background(color = RGBColor.BACKGROUND.toColor())
                .alpha(0.7f)
                .zIndex(zIndex)
                .clipToBounds() // 넘친 부분을 잘라내기
        ) {
            Text(
                text = displayedText,
                modifier = modifier
                    .fillMaxWidth()
                    .padding(start = 100.dp, end = 100.dp, top = 10.dp, bottom = 10.dp)
                    .align(Alignment.Center)
                    .verticalScroll(scrollState)
                ,
                textAlign = TextAlign.Center,
                style = TextStyle(color = RGBColor.Text.toColor(), fontSize = 40.sp,lineHeight = 80.sp),
                softWrap = true, // 줄 바꿈이 자동으로 되게 설정
                maxLines = Int.MAX_VALUE, // 줄 수에 제한 없이 텍스트가 늘어날 수 있도록 설정
                overflow = androidx.compose.ui.text.style.TextOverflow.Clip, // 텍스트가 넘칠 때 처리
                onTextLayout = { LayoutResult : TextLayoutResult ->
                    if(LayoutResult.lineCount > 2) {
                        test = 110 * LayoutResult.lineCount
                    }
                }
            )
        }

    }
}

@Composable
fun GifImage(
    modifier: Modifier,
    drawableId: Int,
    zIndex :Float,
    gifLoadCallback : (checkLoadGif: Int) -> Unit
) {
    val context = LocalContext.current
    val imageLoader = ImageLoader.Builder(context)
        .components {
            GifDecoder.Factory()
        }
        .diskCachePolicy(CachePolicy.ENABLED)  // 디스크 캐시 사용 설정
        .memoryCachePolicy(CachePolicy.DISABLED)  // 메모리 캐시 비활성화
        .build()

    val painter = rememberAsyncImagePainter(
        ImageRequest.Builder(context)
            .data(data = drawableId)
            .apply(block = {

            }).build()
        , imageLoader = imageLoader,
        onSuccess =  {
            Log.d("GifImage-rememberAsyncImagePainter", "GIF - ${drawableId} - Success")
            gifLoadCallback(0)
        },
        onError = {
            Log.d("GifImage-rememberAsyncImagePainter", "GIF - ${drawableId} - Error")
        },
        onLoading = {
            gifLoadCallback(1000)
        }
    )

    Image(
        painter = painter,
        contentDescription = null,
        modifier = modifier
            .fillMaxSize()
            .background(color = RGBColor.BACKGROUND.toColor())
            .zIndex(zIndex)
        ,contentScale = ContentScale.FillBounds
    )
}
