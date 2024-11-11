import "./Header.css";
import {Link} from "react-router-dom";
import { useState } from "react";
import mainicon from '../img/test01-Remove.png';

export default function Header() {
    const [menuOpen, setMenuOpen] = useState(false);


    return (
        <div className="Header-container">
            <div className="left-container">
                <Link to="/" className="HomeLinkIcon">
                    <img src={mainicon} alt="mainicon"/>
                </Link>
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
                        직업
                    </div>
                </Link>
            </div>
            <div className="right-container">
                <Link to="/#start" className="outline-Block">
                    <div className="Head-font">
                        시작하기
                    </div>
                </Link>
            </div>
        </div>
    );
}