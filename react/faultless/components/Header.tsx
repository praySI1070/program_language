import "./Header.css";
import { useState, useEffect } from "react";
import {Link} from "react-router-dom";
import mainicon from '../img/test01-Remove.png';
import loginicon from '../img/login.png';
import LoginMini from "./login-mini";
import { Link as SLink, scroller } from 'react-scroll';



export default function Header() {
    

    return (
        <div className="Header-container">
            <div className="left-container">
                <SLink to="home" smooth={true} duration={500} className="HomeLinkIcon">
                    <img src={mainicon} alt="mainicon"/>
                </SLink>
                <SLink to="summary" smooth={true} duration={500} offset={-70} className="outline-Block">
                    <div className="Head-font">
                        개요
                    </div>
                </SLink>
                <SLink to="new" smooth={true} duration={500} offset={-70} className="outline-Block">
                    <div className="Head-font">
                        새소식
                    </div>
                </SLink>
                <SLink to="controll" smooth={true} duration={500} className="outline-Block">
                    <div className="Head-font">
                        조작법
                    </div>
                </SLink>
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

export function HeaderNoIndex() {
    
    const handleScroll = (e: React.MouseEvent, pos: string) => {
        // 페이지 이동 후 스크롤을 실행하려면 setTimeout 사용
        setTimeout(() => {
            scroller.scrollTo(pos, {
                smooth: true,  // 부드럽게 스크롤
                duration: 500, // 스크롤에 걸리는 시간 (ms)
                offset: -70,   // 상단의 여백을 70px 만큼 조정
            });
        }, 100); // 100ms 후에 스크롤 실행
    };

    return (
        <div className="Header-container">
            <div className="left-container">
                <Link to="/"  className="HomeLinkIcon">
                    <img src={mainicon} alt="mainicon"/>
                </Link>
                
                <Link to="/" className="outline-Block" onClick={(e) =>handleScroll(e,'summary')}>
                    <div className="Head-font">
                        개요
                    </div>
                </Link>
                <Link to="/" className="outline-Block" onClick={(e) =>handleScroll(e,'new')}>
                    <div className="Head-font">
                        새소식
                    </div>
                </Link>
                <Link to="/" className="outline-Block" onClick={(e) =>handleScroll(e,'controll')}>
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