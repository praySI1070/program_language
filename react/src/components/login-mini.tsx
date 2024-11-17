import "./login-mini.css";
import {Link} from "react-router-dom";
import { useLogIn } from "./logincontext";

export default function LoginMini() {
    const {setLogIn,setUserId,setUserRank,setUserSignDate} = useLogIn();

    const CheckLogin = () => {
        const inputIdElement = document.querySelector('.id-textbox') as HTMLInputElement; // 타입 단언
        const id = inputIdElement?.value;

        const inputPwElement = document.querySelector('.password-textbox') as HTMLInputElement;
        const pw = inputPwElement?.value;

        console.log("test성공!");
        fetch("http://localhost:7000/Login", {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({id, pw})
        })
         .then(res=>res.json())
         .then(data=> {
            if(data.userIsLogin) {
                setLogIn(true);
                setUserId(id);
                setUserRank(data.userRank);
                setUserSignDate(data.userSign);
            }
        });
    };

    return (
        <div className="loginmini-main">
            <div className="invisible-box"></div>
            <div className="id">로그인</div>
            <input type="text" placeholder="  ID" className="id-textbox"/>
            <input type="text" placeholder="  PASSWORD" className="password-textbox"/>
            <Link to="/signup"><div className="signup-link">회원가입</div></Link>
            <button className="login-button" onClick={CheckLogin}>로그인</button>
        </div>
    );
}