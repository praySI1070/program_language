import "./login-mini.css";
import {Link} from "react-router-dom";

export default function LoginMini() {
    return (
        <div className="loginmini-main">
            <div className="invisible-box"></div>
            <div className="id">로그인</div>
            <input type="text" placeholder="  ID" className="id-textbox"/>
            <input type="text" placeholder="  PASSWORD" className="password-textbox"/>
            <Link to="/signup"><div className="signup-link">회원가입</div></Link>
            <button className="login-button">로그인</button>
        </div>
    );
}