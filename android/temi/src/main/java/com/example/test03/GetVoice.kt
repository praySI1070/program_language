package com.example.test03

import android.app.Service
import android.content.Intent
import android.media.AudioFormat
import android.os.IBinder
import android.os.Binder
import android.util.Log // Log import
import com.robotemi.sdk.Robot
import java.lang.Object
import android.media.AudioRecord
import android.media.MediaRecorder
import android.media.MediaRecorder.AudioSource
import android.provider.MediaStore
import android.media.AudioRecordingMonitor
import android.media.AudioRouting
import android.media.MicrophoneDirection
import kotlinx.coroutines.*
import java.io.File
import java.io.FileOutputStream
import java.io.IOException
import android.util.Base64
import com.robotemi.sdk.BuildConfig
import org.json.JSONArray
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http. POST
import retrofit2.http. FormUrlEncoded
import retrofit2.http. FieldMap
import retrofit2.Call
import retrofit2.http. Header
import retrofit2.http. Body
import com.example.test03.Argument
import com.example.test03.RequestBody
import com.example.test03.SttResponse
import okhttp3.MediaType.Companion.toMediaType
import okhttp3.OkHttpClient
import okhttp3.Request
import okhttp3.RequestBody.Companion.toRequestBody
import org.json.JSONException
import org.json.JSONObject
import retrofit2.http. Headers



interface APIService {
    @Headers("Content-Type: application/json; charset=UTF-8")
    @POST("/WiseASR/Recognition")
    //@POST("SttService")
    fun sendRequest(
        @Header("Authorization") authorization: String,
        @Body body: RequestBody
    ): Call<SttResponse>
}

class GetVoice : Service() {
    //녹음할 헤르츠
    val recordHz:Int = 16_000;
    //최소 버퍼 사이즈
    var minumumBufferSize: Int =0
    //오디오 녹음 객체
    var audioRecord: AudioRecord? = null
    //녹음중
    var isRecording: Boolean = false
    //녹음 시간 (ms단위)
    val recordTime: Long = 10_000
    val byteArraySize = 128_000
    val originalPcm: ByteArray = ByteArray(byteArraySize)
    var pcmToBase64: String = ""
    var pivot : Int = 0
    var receiveString: String? = ""
    val authorization : String = com.example.test03.BuildConfig.STT_API_KEY
    val gptApiKey : String = com.example.test03.BuildConfig.GPT_API_KEY
    var language:String = Language.KOREAN.languageCode


    //처음 실행 되었을 떄, 사용
    override fun onCreate() {
        super.onCreate()
        Log.d("Getvoice", "GetVoice service start")



    }

    //서비스가 바인딩 될 떄 사용
    override fun onBind(intent: Intent?): IBinder? {
        Log.d("Getvoice", "GetVoice service Bind")



        return Record()
    }

    //바인드의 연결을 종료
    override fun onUnbind(intent: Intent?): Boolean {
        Log.d("Getvoice", "GetVoice service Unbind")
        return super.onUnbind(intent)
    }

    //서비스를 종료
    override fun onDestroy() {
        super.onDestroy()
        Log.d("Getvoice", "GetVoice service Destroy")
    }

    suspend fun sttApi(): String {
        Log.d("sttapi", "sttapi가 실행됨.")

        val Networkjob = CoroutineScope(Dispatchers.IO).launch {
            try {
                val retrofit = Retrofit.Builder()
                    .baseUrl("http://aiopen.etri.re.kr:8000/")
                    //.baseUrl("http://192.168.0.71:8000/")
                    .addConverterFactory(GsonConverterFactory.create())
                    .build()

                val apiService = retrofit.create(APIService::class.java)

                // originalPcm 배열에서 pivot-1 인덱스까지 읽어와서 Base64로 인코딩
                val pcmSubArray = originalPcm.copyOfRange(0, pivot)  // 0부터 pivot-1까지 읽음

                pcmToBase64 = Base64.encodeToString(pcmSubArray,Base64.NO_WRAP)

                for(i in originalPcm.indices) {
                    originalPcm[i] = 0
                }
                pivot = 0

                val argument = Argument(language,pcmToBase64)
                val requestBody = RequestBody(argument)

                val response = apiService.sendRequest("$authorization", requestBody).execute()
                if(response.isSuccessful) {
                    val sttRespon = response.body()
                    Log.d("stt", "결과: $sttRespon")
                    receiveString = sttRespon?.return_object?.recognized
                } else {
                    Log.d("stt오류", "오류 $response")
                }
            } catch (e: Exception) {
                Log.d("sttAPI", "오류 : $e")
            }
        }

        Networkjob.join()
        Networkjob.cancel()

        return receiveString ?: "stt오류"
    }


    suspend fun test(languageCode: String) :String {
        Log.d("Getvoice", "test용함수")

        Language.values().forEach { languagetype ->
            if(languagetype.language == languageCode) {
                language = languagetype.languageCode
            }
        }

        try {
            if(minumumBufferSize == 0) {
                Log.d("test-1","최소 버퍼 설정")
                minumumBufferSize = AudioRecord.getMinBufferSize(recordHz, AudioFormat.CHANNEL_IN_MONO,
                    AudioFormat.ENCODING_PCM_16BIT)
            }

            if(minumumBufferSize < AudioRecord.SUCCESS) {
                Log.e("test-onCreate", "잘못된 크기: $minumumBufferSize")
                return "apoktmwodoso"
            }

            if(audioRecord == null) {
                Log.d("test-1","오디오 레코드 객체 생성")
                audioRecord = AudioRecord(MediaRecorder.AudioSource.MIC,recordHz, AudioFormat.CHANNEL_IN_MONO,
                    AudioFormat.ENCODING_PCM_16BIT,minumumBufferSize)
            }

            if(audioRecord?.state == AudioRecord.STATE_INITIALIZED) {
                //1이 정상
                Log.d("test-1","오디오 객체 정상 생성 - ${audioRecord?.state}")

                var result:String = ""

                var buffer = ByteArray(minumumBufferSize)
                Log.d("debug","buffer사이즈 : ${buffer.size}")

                Log.d("debug", "buffer최적화 사이즈 : ${AudioRecord.getMinBufferSize(recordHz,AudioFormat.CHANNEL_IN_MONO,AudioFormat.ENCODING_PCM_16BIT)}")


                //val file = File(filePath)

                val job = GlobalScope.launch {
                    launch {
                        try {
                            Log.d("debug","시작")
                            //val fos = FileOutputStream(file)
                            audioRecord?.startRecording()
                            isRecording = true
                            while(isRecording) {
                                if(pivot + minumumBufferSize >= byteArraySize) {
                                    Log.d("Getvoice","딜레이 전에 배열이 가득 참")
                                    break
                                }
                                //반환값 확인

                                audioRecord?.read(buffer, 0, minumumBufferSize)
                                //fos.write(buffer)
                                System.arraycopy(buffer,0,originalPcm,pivot,minumumBufferSize)
                                pivot += minumumBufferSize
                            }
                            Log.d("debug","끝")
                        } catch (e : IOException) {
                            Log.e("test-Globalscope","IO 오류: $e")
                        } catch (e: Exception) {
                            Log.e("test-GlobalScope", "오류: $e")
                        }
                    }
                    delay(recordTime)
                    Log.d("debug", "pivot : $pivot")
                    isRecording = false
                    Log.d("debug","2")

                    if(audioRecord?.state != AudioRecord.STATE_UNINITIALIZED) {
                        audioRecord?.stop()
                        audioRecord?.release()
                        audioRecord = null
                        Log.d("test-오디오초기화","오디오 초기화 완")
                    }

                    if(!isRecording) {
                        result = async {
                            sttApi()
                        }.await()


                    }
                }

                job.join()
                job.cancel()

                return result
            }



        } catch (e: SecurityException) {
            Log.e("test-onCreate", "오디오 권한없음: $e")
        } catch (e: Exception) {
            Log.e("test-onCreate", "오류: $e")
        }

        return "test"
    }

    fun stopTest() {
        isRecording = true
    }

    suspend fun callGptAndGetResponse(userInputText: String,inputLanguage : String): String = withContext(Dispatchers.IO) {
        val arr = JSONArray() // API 전송 메세지
        val aiAnswer = JSONObject() // GPT 응답
        val userMsg = JSONObject() // STT 처리된 텍스트
        val client = OkHttpClient()
        var ptOutputText: String = "없음"
        var languange:String = "ko"

        Language.values().forEach { languagetype ->
            if(languagetype.language == inputLanguage) {
                languange = languagetype.gptLanguageCode
            }
        }
        
        Log.d("gptService", "gptService 시작")
        Log.d("gptService","userInputText : $userInputText")

        // 참고 데이터
        val jsonData = JSONObject().apply {
            put("laugunage", languange)
            put("title", "2025 AI INFINITY")
            put("location", JSONObject().apply {
                put("country", "대한민국")
                put("address", "강원도 춘천시 영서로 2260, 문화공간역 남춘천역 1층")
            })
            put("date", JSONObject().apply {
                put("start", "2025-06-20")
                put("end", "2025-06-25")
            })
            put("exhibition", JSONObject().apply {
                put("title", "2025 AI Infinite")
                put(
                    "description",
                    "A graduation exhibition by the Department of AI Software Convergence at Korea Polytechnics Chuncheon Campus, showcasing the creativity and technological capabilities of generative AI under the theme of the future society. The exhibition features projects from both first- and second-year students, including AI image generation, interactive content, autonomous driving, and VR experiences."
                )
                put("year1_project", JSONObject().apply {
                    put("name", "Generative AI Posters")
                    put("tools", JSONArray(listOf("Midjourney", "DALL·E", "Stable Diffusion")))
                    put(
                        "themes",
                        JSONArray(
                            listOf(
                                "Future Cities",
                                "Visualizing Emotions",
                                "Imaginary Creatures"
                            )
                        )
                    )
                    put(
                        "objective",
                        "To explore the visual imagination of AI and examine the potential for fusion between human creativity and machine learning."
                    )
                })
                put("year2_projects", JSONArray().apply {
                    put(JSONObject().apply {
                        put("title", "Tory (Temi-based Chatbot)")
                        put(
                            "description",
                            "A Temi-based chatbot capable of voice recognition and natural language responses. It analyzes users’ speech to provide natural conversations and animated reactions."
                        )
                        put(
                            "technologies",
                            JSONArray(
                                listOf(
                                    "STT",
                                    "GPT API",
                                    "TTS",
                                    "Python",
                                    "Temi",
                                    "Voice UI",
                                    "Animated Responses"
                                )
                            )
                        )
                        put(
                            "theme",
                            "Implementing human-machine interfaces in a futuristic exhibition environment."
                        )
                    })
                    put(JSONObject().apply {
                        put("title", "AnsimLink(안심링크)")
                        put(
                            "description",
                            "A system that detects and blocks phishing sites during online transactions, offering a secure environment for users."
                        )
                        put(
                            "technologies",
                            JSONArray(
                                listOf(
                                    "URL Analysis",
                                    "Server Data Lookup",
                                    "Phishing Detection System"
                                )
                            )
                        )
                        put("theme", "Cybercrime prevention and digital safety.")
                    })
                    put(JSONObject().apply {
                        put("title", "Smart Military Training Simulator")
                        put(
                            "description",
                            "A VR-based simulation for reserve force training, providing immersive and realistic training experiences."
                        )
                        put(
                            "technologies",
                            JSONArray(
                                listOf(
                                    "Unity 3D",
                                    "C++",
                                    "VR",
                                    "Virtual Battlefield Simulation"
                                )
                            )
                        )
                        put("theme", "Modernizing military education.")
                    })
                    put(JSONObject().apply {
                        put("title", "Air Drawing")
                        put(
                            "description",
                            "An interface that allows users to draw in the air using hand gesture recognition, presenting an intuitive application of AI."
                        )
                        put(
                            "technologies",
                            JSONArray(listOf("Mediapipe", "OpenCV", "Hand Gesture Recognition"))
                        )
                        put("theme", "Gesture-based drawing system.")
                    })
                })
                put("exhibition_format", JSONObject().apply {
                    put("online", "An online exhibition will be available...")
                    put("interaction", "Visitors can participate...")
                })
                put("vision", "Presenting a new direction...")
            })
        }

        // GPT 설정
        try {
            //AI 속성설정
            aiAnswer.put("role", "system")
            aiAnswer.put(
                "content",
                "You are Tori, the manager of an academic department exhibition that is currently in progress. You are playing the role of a chatbot that interacts naturally with visitors. Explanations should be delivered in a conversational tone. If the languange in the JSON is ko, respond in Korean; if ja, respond in Japanese; if zh, respond in Chinese; and if en, respond in English using polite language. Please speak naturally without using symbols or bullet points. Each response should be no longer than 500 characters. The exhibition has already started. Please do not use the phrase graduation project, as this exhibition does not feature graduation works." + jsonData.toString()
            ) // json 공백 제거(token 절약)
            //유저 메세지
            userMsg.put("role", "user")
            userMsg.put("content", userInputText)
            //array로 담아서 한번에 보낸다
            arr.put(aiAnswer)
            arr.put(userMsg)
        } catch (e: JSONException) {
            throw RuntimeException(e)
        }

        // 모델 설정 및 메세지 전달
        val `object` = JSONObject()
        try {
            `object`.put("model", "o4-mini")
            `object`.put("messages", arr)
        } catch (e: JSONException) {
            e.printStackTrace()
        }

        // API 전송 용도 문자열 처리
        val JSON = "application/json; charset=utf-8".toMediaType()
        val body = `object`.toString().toRequestBody(JSON)

        val request = Request.Builder()
            .url("https://api.openai.com/v1/chat/completions")
            .header("Authorization", "Bearer ${com.example.test03.BuildConfig.GPT_API_KEY}")
            .post(body)
            .build()

        // retrofit2.Call과 충돌
        ptOutputText = try {
            val response = client.newCall(request).execute()
            if (response.isSuccessful) {
                val json = JSONObject(response.body?.string() ?: "")
                val content = json.getJSONArray("choices")
                    .getJSONObject(0)
                    .getJSONObject("message")
                    .getString("content")
                Log.d("GPT_API", "GPT 응답: ${content.trim()}")
                content.trim()
            } else {
                Log.w("GPT_API", "API 실패: 코드 ${response.code}")
                "오류 발생: ${response.code}"
            }
        } catch (e: IOException) {
            Log.e("GPT_API", "API 요청 실패: ${e.message}")
            "네트워크 오류 발생"
        }

        return@withContext ptOutputText

    }

    suspend fun uiTest():String {
        Log.d("uiTest", "녹음 대기중")

        val Networkjob = CoroutineScope(Dispatchers.IO).launch {
            delay(5000)
        }

        Networkjob.join()
        Networkjob.cancel()

        Log.d("uiTest", "녹음 성공적")

        return "인생을 어떻게 사는게 좋을까?"
    }

    suspend fun uiTest02(test :String):String {
        Log.d("uiTest02", "gpt응답대기중!")

        val Networkjob = CoroutineScope(Dispatchers.IO).launch {
            delay(10_000)
        }

        Log.d("uiTest02", "gpt응답완료!")

        return "이 세상에는 수많은 사람들이 살아가고 있고, 각자의 인생에서 중요한 순간들을 맞이하며 끊임없이 변화하는 시간을 살아가고 있습니다. 우리는 매일 아침 일어나서 하루를 시작하고, 다양한 선택들을 하면서 하루를 마무리합니다. 때로는 힘든 일들이 우리의 앞길을 막기도 하지만, 그런 어려움을 극복하며 성장하는 과정에서 우리는 더 강해지고 더 나은 사람이 되어갑니다. 인생은 예측할 수 없는 일들이 많지만, 그 안에서 우리가 얼마나 진지하게 살아가느냐가 중요한 문제입니다. 결국 중요한 것은 우리가 지금 이 순간을 어떻게 살아가느냐에 달려 있습니다."
    }

    //서비스와 클라이언트 간의 통신을 담당
    //inner는 내부의 클래스라는 뜻 부모 객체의 함수를 사용할 수 있음.
    inner class Record : Binder() {
        fun getService(): GetVoice = this@GetVoice
    }
}
