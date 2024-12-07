import "./login-mini.css";
import {Link} from "react-router-dom";
import { useLogIn } from "./logincontext";
const REACT_APP_API_URL = process.env.REACT_APP_API_URL;

export default function LoginMini() {
    const {setLogIn,setUserId,setUserRank,setUserSignDate} = useLogIn();

    const onSubmitEnter = (e: React.KeyboardEvent) => {
        if(e.key === 'Enter') {
            CheckLogin();
        }
    };

    const CheckLogin = () => {
        const inputIdElement = document.querySelector('.id-textbox') as HTMLInputElement; // 타입 단언
        const id = inputIdElement?.value;

        const inputPwElement = document.querySelector('.password-textbox') as HTMLInputElement;
        const pw = inputPwElement?.value;

        fetch(`http://${REACT_APP_API_URL}/Login`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({id, pw}),
            credentials: 'include'
        })
         .then(res=>res.json())
         .then(data=> {
            if(data.userIsLogin) {
                setLogIn(true);
                setUserId(id);
                setUserRank(data.userRank);
                setUserSignDate(data.userSign);
            }
            else {
                alert("아이디 혹은 비밀번호가 틀립니다.")
            }
        });
    };

    return (
        <div className="loginmini-main">
            <div className="invisible-box"></div>
            <div className="id">로그인</div>
            <input 
                type="text" 
                placeholder="  ID" 
                className="id-textbox"
                onKeyDown={onSubmitEnter}  // Enter 키 감지
            />
            <input 
                type="password" 
                placeholder="  PASSWORD" 
                className="password-textbox"
                onKeyDown={onSubmitEnter}  // Enter 키 감지
                />
            <Link to="/signup">
                <div className="signup-link">회원가입</div>
            </Link>
            <button className="login-button" onClick={CheckLogin}>로그인</button>
        </div>
    );
}