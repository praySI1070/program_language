import com.android.build.gradle.internal.cxx.configure.gradleLocalProperties

plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.jetbrains.kotlin.android)
    alias(libs.plugins.compose.compiler)
}

android {
    signingConfigs {
        create("release") {
            storeFile = file("D:\\praySI01\\2.1\\temi\\key\\TemiAppKey.jks")
            storePassword= "student1973!"
            keyAlias= "key0"
            keyPassword= "student1973!"
        }
    }
    fun getApiKey(propertyKey:String):String{
        //24년도 이전에는 providers를 안적어도 됬음.
        return gradleLocalProperties(rootDir,providers).getProperty(propertyKey)
    }

    namespace = "com.example.test03"
    compileSdk = 35

    defaultConfig {
        applicationId = "com.example.test03"
        minSdk = 23
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        vectorDrawables {
            useSupportLibrary = true
        }
        //build창에 출력
        println("STT_API_KEY is: ${getApiKey("sttApiKey")}")  // 콘솔에 값 출력
        println("GPT_API_KEY is: ${getApiKey("gptApiKey")}")
        buildConfigField("String", "STT_API_KEY", "\"${getApiKey("sttApiKey")}\"")
        buildConfigField("String", "GPT_API_KEY", "\"${getApiKey("gptApiKey")}\"")
        signingConfig = signingConfigs.getByName("release")
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }
    buildFeatures {
        buildConfig = true
        compose = true
        aidl = true  // AIDL 기능 활성화
    }
    composeOptions {
        kotlinCompilerExtensionVersion = "1.5.1"
    }
    packaging {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }
}

dependencies {

    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.lifecycle.runtime.ktx)
    implementation(libs.androidx.activity.compose)
    implementation(libs.androidx.ui)
    implementation(libs.androidx.ui.graphics)
    implementation(libs.androidx.ui.tooling.preview)
    implementation("androidx.compose.material3:material3:1.3.2")
    implementation("androidx.compose.material3:material3-window-size-class:1.3.2")
    implementation("androidx.compose.material3:material3-adaptive-navigation-suite:1.4.0-alpha15")
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)
    androidTestImplementation("androidx.compose.ui:ui-test-junit4:1.8.2")
    debugImplementation(libs.androidx.ui.tooling)
    debugImplementation(libs.androidx.ui.test.manifest)
    implementation(libs.kotlinx.coroutines.android)
    implementation("com.robotemi:sdk:1.135.1")  // robotemi-sdk
    implementation("io.coil-kt.coil3:coil-compose:3.2.0") //compose에서 사용 coil라이브러리
    implementation("io.coil-kt.coil3:coil-gif:3.2.0")     //gif coil라이브러리
    implementation("io.coil-kt.coil3:coil-video:3.2.0")   //video coil라이브러리
    implementation("com.squareup.retrofit2:retrofit:2.9.0") //retrofit : http통신 라이브러리
    implementation ("com.google.code.gson:gson:2.8.6") // Gson 라이브러리 - JSON변환
    implementation("com.squareup.retrofit2:converter-gson:2.9.0") // Gson 컨버터
    implementation("org.json:json:20240303") // json
    implementation("com.squareup.okhttp3:okhttp:4.7.2") // requestbody
}