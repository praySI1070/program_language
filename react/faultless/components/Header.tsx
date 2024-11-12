import "./Header.css";
import {Link} from "react-router-dom";
import { useState } from "react";
import mainicon from '../img/test01-Remove.png';
import loginicon from '../img/login.png';
import LoginMini from "./login-mini";


export default function Header() {
    const [menuOpen, setMenuOpen] = useState(false);

    

    return (
        <div className="Header-container">
            <div className="left-container">
                <a href="/" className="HomeLinkIcon">
                    <img src={mainicon} alt="mainicon"/>
                </a>
                <Link to="/#summary" className="outline-Block">
                    <div className="Head-font">
                        개요
                    </div>
                </Link>
                <Link to="/#new" className="outline-Block">
                    <div className="Head-font">
                        새소식
                    </div>
                </Link>
                <Link to="/#class" className="outline-Block">
                    <div className="Head-font">
                        조작법
                    </div>
                </Link>
                <Link to="/discuss" className="outline-Block">
                    <div className="Head-font">
                        FQA
                    </div>
                </Link>
            </div>
            <div className="right-container">
                <Link to="/#start" className="outline-Block">
                    <div className="Head-font">
                        시작하기
                    </div>
                </Link>
                
                    <div className="outline-Block login-mini-on">
                        <img src={loginicon} alt="loginicon" className="loginicon"/>
                        <div className="login-font">계정</div>
                        <div className="login-font-hover">계정</div>
                        <div className="arrow">＜</div>
                        <div className="arrow-hover">-</div>
                        <div className="LoginMini-container">
                            <LoginMini />
                        </div>
                    </div>
                
            </div>
        </div>
    );
}