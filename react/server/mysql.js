const mysql = require('mysql2');

require('dotenv').config();

const DB_HOST = process.env.DB_HOST;
const DB_PASSWORD = process.env.DB_PASSWORD;
const DB_USER = process.env.DB_USER;
const DB_DB = process.env.DB_DATABASE;
const DB_PORT = process.env.DB_PORT;

const pool = mysql.createPool({
  host : DB_HOST,
  user : DB_USER,
  password : DB_PASSWORD,
  database : DB_DB,
  port : DB_PORT,
  waitForConnections: true,   // 연결이 없을 경우 대기 설정
  connectionLimit: 10,        // 최대 연결 수 (여러 요청을 동시에 처리할 수 있도록)
  queueLimit: 0               // 대기열 크기 (0이면 무제한)
});

const promisePool = pool.promise();

function queryPromise(query, values = []) {
    return promisePool.query(query, values);
}

async function Login(id,password) {
    try {
        // 쿼리 실행
        const [rows, fields] = await queryPromise(
          `SELECT SERACH_ID(?,?) AS Login_result`, 
          [id, password]
        );
    
        // 로그인 성공 여부 반환
        return rows[0].Login_result; // 결과가 있으면 로그인 성공
      } catch (err) {
        console.error('Error in Login function: ', err);
        throw err;  // 오류 발생 시 예외 던지기
      }
}

async function CheckId(id) {
  try {
    const [rows, fields] = await queryPromise(
      `SELECT Check_Id(?) AS RESULT`,
      [id]
    );
    return rows[0].RESULT;
  } catch (err) {
    console.error('Error in CheckId function: ', err);
    throw err;  // 오류 발생 시 예외 던지기
  }
}

async function SignUp(id,name,ps,year,month,day,phone1,phone2,phone3) {
  try {
    const date = year + '-' + month + '-' + day;
    const phone = phone1 + phone2 + phone3;
    const [rows, fields] = await queryPromise(
      'SELECT SIGN_UP(?,?,?,?,?) AS RESULT',
      [id,name,ps,date,phone]
    );
    return rows[0].RESULT;
  } catch (err) {
    console.error('Error in SignUp function: ', err);
    throw err;  // 오류 발생 시 예외 던지기
  }
}

async function MemberOut(id) {
  try {
    const [rows, fields] = await queryPromise(
      'SELECT DELETE_ID(?) AS RESULT',
      [id]
    );
    return rows[0].RESULT;
  } catch(err) {
    console.error('Error in SignUp function: ', err);
    throw err;  // 오류 발생 시 예외 던지기
  }
}

async function SerachDiscuss() {
  try {
    const [rows,fields] = await queryPromise(
      'SELECT SERACH_FQA() AS RESULT'
    );
    return rows[0].RESULT;
  } catch (err) {
    console.error('Error in SerachDiscuss function: ', err);
    throw err;
  }
}

async function DiscussInput(id,detail) {
  try {
    const [rows,fields] = await queryPromise(
      'SELECT INSERT_FQA(?,?) AS RESULT',
      [id,detail]
    );
    return rows[0].RESULT;
  } catch (err) {
    console.error('Error in DiscussInput function: ', err);
    throw err;
  }
}

module.exports = {
    Login,
    CheckId,
    SignUp,
    MemberOut,
    SerachDiscuss,
    DiscussInput
};