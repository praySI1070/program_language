import "./Header.css";
import { useState, useEffect } from "react";
import {Link} from "react-router-dom";
import mainicon from '../img/test01-Remove.png';
import loginicon from '../img/login.png';
import LoginMini from "./login-mini";
import LogOutMini from "./logout-mini";
import Loading from "./Loading";
import { Link as SLink, scroller } from 'react-scroll';
import { useLogIn } from "./logincontext";
const REACT_APP_API_URL = process.env.REACT_APP_API_URL;

async function GameDownload(logIn:boolean,setLoading: React.Dispatch<React.SetStateAction<boolean>>) {

    if(!logIn) {
        alert("로그인 해주세요.");
        return;
    }

    setLoading(true);

    try {
        const response = await fetch(`http://${REACT_APP_API_URL}/GameDownload`, {
            method: 'GET',
            credentials: 'include'
        });

        if (!response.ok) {
            throw new Error("다운로드 요청이 실패했습니다.");
        }

        const blob = await response.blob();
        const url = window.URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = 'Fight_Wizard1.1.zip';
        document.body.appendChild(a);
        a.click();

        // 다운로드가 완료된 후 URL 해제
        setTimeout(() => {
            window.URL.revokeObjectURL(url);
        }, 1000);
        a.remove();

    } catch (error) {
        console.error("파일 다운로드 오류:", error);
    } finally {
        // 로딩 종료
        await new Promise(resolve => setTimeout(resolve, 2000));
        setLoading(false);
    }
};

export default function Header() {
    const {logIn,userId} = useLogIn();
    const [loading, setLoading] = useState<boolean>(false);

    return (
        <div>
        {loading && <Loading />}
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
                <div className="outline-Block">
                    <div className="Head-font" onClick={() => GameDownload(logIn,setLoading)}>
                        다운로드
                    </div>
                </div>
                
                    <div className="outline-Block login-mini-on">
                        <img src={loginicon} alt="loginicon" className="loginicon"/>
                        <div className="login-font">계정</div>
                        <div className="login-font-hover">계정</div>
                        <div className="arrow">＜</div>
                        <div className="arrow-hover">-</div>
                        <div className="LoginMini-container">
                            {
                                logIn === false
                                ? <LoginMini />
                                : <LogOutMini/>
                            }
                            
                        </div>
                    </div>
                
            </div>
        </div>
    </div>
    );
}

export function HeaderNoIndex() {
    const {logIn,userId} = useLogIn();
    const [loading, setLoading] = useState<boolean>(false);
    
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
        <div>
        {loading && <Loading />}
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
                <div className="outline-Block">
                    <div className="Head-font"  onClick={() => GameDownload(logIn,setLoading)}>
                        다운로드
                    </div>
                </div>
                
                    <div className="outline-Block login-mini-on">
                        <img src={loginicon} alt="loginicon" className="loginicon"/>
                        <div className="login-font">계정</div>
                        <div className="login-font-hover">계정</div>
                        <div className="arrow">＜</div>
                        <div className="arrow-hover">-</div>
                        <div className="LoginMini-container">
                            {
                                logIn === false
                                ? <LoginMini />
                                : <LogOutMini/>
                            }
                        </div>
                    </div>
            </div>
        </div>
    </div>
    );
}