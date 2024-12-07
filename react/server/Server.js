const express = require('express'); //express를 설치했기 때문에 가져올 수 있다.
const cors = require('cors');
const formidable = require('formidable');
const {Login,CheckId,SignUp,MemberOut,SerachDiscuss,DiscussInput} = require('./mysql.js');
const path = require('path');

const app = express();
const port = process.env.PORT || 6500;
const server = require('http').createServer(app);

const cookieParser = require('cookie-parser');
const expressSession = require('express-session');

//환경변수 .env파일읽기
require('dotenv').config();
const SK = process.env.SK || 'default_value';  // SK가 없으면 'default_value'를 사용


app.use(cors({
  origin: 'http://localhost:3000', // 리액트 클라이언트 주소
  credentials: true,  // 크로스 오리진 요청에서 쿠키를 전달
}));

// JSON 파싱을 위한 미들웨어
app.use(express.json());  // JSON 형식의 요청 본문을 파싱

app.use(cookieParser(SK));

// 세션세팅
app.use(
  expressSession({
    secret: SK,
    resave: false,
    saveUninitialized: true,
    cookie: { 
      secure: false,
      maxAge: 1000 * 60 * 60 * 24 ,
      sameSite: 'None',
      httpOnly: true,    // JavaScript에서 접근할 수 없도록
      },
  })
);

app.use(express.static(path.join(__dirname, 'build')));

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'build', 'index.html'));
});


app.post('/Login', async (req,res) => {
  try {
    const result = await Login(req.body['id'],req.body['pw']);
    let check = false;
    let message_de = "Login fail";

    if(Object.keys(result).length > 0) {
      check = true;
      message_de = "Login successful";
    }

     let signdate = result['sign_date'];
     // 세션에 사용자 정보를 저장
     req.session.userId = req.body['id'];  // 사용자의 ID
     req.session.userRank = result['rank'];  // 사용자 랭크
     req.session.userSign = signdate.split('.')[0];  // 사용자 가입일
     req.session.userIsLogin = check;  // 로그인 상태

      // 쿠키를 클라이언트에 전달 (자동으로 세션 ID는 'connect.sid'로 설정됨)
    res.cookie('userId', req.body['id'], {
      httpOnly: true, // JavaScript에서 접근할 수 없도록 설정 (보안)
      secure: process.env.NODE_ENV === 'production', // HTTPS 환경에서만 true
      sameSite: 'None', // CORS 요청 시 쿠키 전달 허용
      maxAge: 1000 * 60 * 60 * 24, // 쿠키 만료 시간 (1일)
    });

    res.json({
      message:message_de,
      userIsLogin: check,
      userRank : req.session.userRank,
      userSign:req.session.userSign,
    });
  } catch (error) {
    res.status(500).json({error : 'Login failed', detail:error})
  }


})

// 세션 확인 API (로그인 상태 체크)
app.get('/check-session', (req, res) => {
  if (req.session.userIsLogin) {
    res.json({
      loggedIn: true,
      user: req.session.userId,
      rank: req.session.userRank,
      signDate: req.session.userSign
    });
  } else {
    res.json({ loggedIn: false });
  }
});

// 로그아웃 처리 API
app.post('/logout', (req, res) => {
  try {
    // 세션에 저장된 사용자 정보를 모두 제거
    req.session.destroy((err) => {
      if (err) {
        return res.status(500).json({ error: 'Failed to log out', detail: err });
      }

      // 세션 쿠키를 클라이언트에서 삭제
      res.clearCookie('connect.sid'); // 기본적으로 express-session은 'connect.sid'라는 이름의 쿠키를 사용

      // 로그아웃 성공 메시지
      res.json({
        message: 'Logged out successfully',
        userIsLogin: false, // 로그아웃 후 로그인 상태는 false
      });
    });
  } catch (error) {
    res.status(500).json({ error: 'Logout failed', detail: error });
  }
});

app.post('/Check-id', async (req,res) => {
  try {
    const result = await CheckId(req.body['id']);
    let check = false;
    
    if(result) {
      check = true;
    }
    else {
      check = false;
    }
    res.json({
      check: check
    });
  } catch(error) {
    res.status(500).json({ error: 'Check-id failed', detail: error });
  }
});

app.post('/signup', async (req,res) => {
  const result = await SignUp(req.body['id'],req.body['name'],req.body['ps'],req.body['selectedYear'],
    req.body['selectedMonth'],req.body['selectedDay'],req.body['selectedPhone'],req.body['middlePhone'],
    req.body['lastPhone']);
  
  let check = false;
  if(result) {
    check = true;
  }
  else {
    check = false;
  }
  res.json({
    check: check
  });
})

app.post('/member-out', async (req,res) => {

  const result = await MemberOut(req.body['userId']);

  let check = false;
  if(result) {
    check = true;
  }
  else {
    check = false;
  }
  res.json({
    check: check
  });
})

app.post('/discuss', async (req, res) => {
  const result = await SerachDiscuss();
  res.json(result);
});

app.post('/discussInput', async (req,res) => {
  console.log("userId: ",req.body.userId)
  const result = await DiscussInput(req.body.userId,req.body['fqaDetail']);

  let check = false;
  if(result) {
    check = true;
  }
  else {
    check = false;
  }
  res.json({
    check: check
  });
});

app.get('/GameDownload', async (req,res) => {
  const filename = 'Fight_Wizard1.1.zip';
  res.setHeader('Content-Disposition', `attachment; filename=${filename}`); //  Content-Disposition 헤더를 브라우저가 읽고 다운로드라고 인식
  res.sendFile("D:\\praySI01\\1.2\\react\\faultless\\server\\GameFile\\Fight_Wizard1.1.zip"); //파일경로
});

server.listen(port, () =>{
    console.log("서버로 작동");
});