import "./signup.css"
import Footer from "../../components/Footer";
import {Link} from "react-router-dom";
import mainicon from '../../img/test01-Remove.png';

export default function Signup() {
    return (
        <div className="signup">
                <Link to="/" className="home-link-box">
                    <img src={mainicon} alt="mainicon" className="test"/>
                </Link>
            <div className="signup-container">
                <div className="sign-title">회원가입</div>
                <div className="sign-id-container">
                    <input type="text" placeholder="  ID를 입력해주세요" className="sign-id-textbox"/>
                    <button className="check-id">중복확인</button>
                </div>
            </div>
            <Footer/>
        </div>
    );
}