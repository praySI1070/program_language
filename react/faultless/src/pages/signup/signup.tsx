import "./signup.css"
import Footer from "../../components/Footer";
import {Link} from "react-router-dom";
import mainicon from '../../img/test01-Remove.png';
import { useState, useEffect } from "react";
import DropBox from "../../components/DropBox";

export default function Signup() {
    //아이디
    const [id,setId] = useState<string>('');

    //비밀번호
    const [ps, setPs] = useState<string>('');
    const [rePs, setRePs] = useState<string>('');
    const [psCheck, setPsCheck] = useState<boolean>(false);

    //드롭박스
    const [selectedYear, setSelectedYear] = useState<string>('');
    const [selectedMonth, setSelectedMonth] = useState<string>('');
    const [selectedDay, setSelectedDay] = useState<string>('');
    const [selectedPhone, setSelectedPhone] = useState<string>('');

    //핸드폰 중간,뒷자리
    const [middlePhone,setMiddlePhone] = useState<string>('');
    const [lastPhone,setLastPhone] = useState<string>('');

    //아이디 입력
    const handleIdChange = (e : React.ChangeEvent<HTMLInputElement>) => {
        setId(e.target.value);
    };

    //비밀번호 입력
    const handlePasswordChange = (e : React.ChangeEvent<HTMLInputElement>) => {
        setPs(e.target.value);
        setPsCheck(ps !== rePs);
    };

    const handleConfirmPasswordChange = (e : React.ChangeEvent<HTMLInputElement>) => {
        setRePs(e.target.value);
        setPsCheck(ps !== rePs);
    };

    //핸드폰 번호
    const handlePhoneChange1 = (e : React.ChangeEvent<HTMLInputElement>) => {
        setMiddlePhone(e.target.value);
    };

    const handlePhoneChange2 = (e : React.ChangeEvent<HTMLInputElement>) => {
        setLastPhone(e.target.value);
    };



    useEffect(() => {
        setPsCheck(ps !== rePs);
    }, [ps, rePs]);

    
    //드롭박스
    // 부모가 받을 콜백 함수
    const handleYearSelectionChange = (selected: string) => {
        setSelectedYear(selected);
    };
    const handleMonthSelectionChange = (selected: string) => {
        setSelectedMonth(selected);
    };
    const handleDaySelectionChange = (selected: string) => {
        setSelectedDay(selected);
    };
    const handlePhoneSelectionChange = (selected: string) => {
        setSelectedPhone(selected);
    };

    //년도 생성
    const generateYear = () => {
        const currentYear = new Date().getFullYear();
        const years: string[] = [];

        for(let year = currentYear;year>=1900;year--) {
            years.push(String(year));
        }

        return years;
    };

    const yearOptions = generateYear();
    const MonthOptions = [1,2,3,4,5,6,7,8,9,10,11,12];
    const PhoneOptions = ['010','011','012','013','015','016','017','018','019'];

    //일 생성
    const generateDay = () => {
        let day_last = 0;
        const days: string[] = [];
        let month = Number(selectedMonth)
        let year = Number(selectedYear)

        if(year === 0) {
            return days;
        }

        if(month % 2 === 1) {
            day_last = 31;
        }
        else {
            if(month !== 2) {
                day_last = 30;
            }
            else {
                if(year % 400 === 0) {
                    day_last = 29;
                }
                else if(year % 100 === 0) {
                    day_last = 28;
                }
                else if(year % 4 === 0) {
                    day_last = 29;
                }
                else {
                    day_last = 28;
                }
            }
        }

        for(let day = 1;day <= day_last;day++) {
            days.push(String(day));
        }

        return days;
    };

    const dayOptions = generateDay();

    //아이디 중복확인 버튼 함수
    const CheckId = () => {
        console.log('중복확인 버튼');
        fetch("http://localhost:6500/Check-id", {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({id})
        })
         .then(res=>res.json())
         .then(data=> {
            console.log(data);
         });
    };

    //회원가입 버튼 함수
    const CheckSignUp = () => {
        console.log('회원가입 버튼');
    };


    return (
        <div className="signup">
                <Link to="/" className="home-link-box">
                    <img src={mainicon} alt="mainicon" className="test"/>
                </Link>
            <div className="signup-container">
                <div className="sign-title">회원가입</div>
                <div className="input-container">
                    <div className="sign-detail-container">
                    <div className="ps-guide">아이디는 8~20자 / 영어소문자+숫자 </div>
                        <input type="text" placeholder="  ID를 입력해주세요" className="sign-id-textbox"
                        value={id} onChange={handleIdChange} maxLength={20}/>
                        
                    </div>
                    <button className="check-id" onClick={CheckId}>중복확인</button>
                </div>
                <div className="input-container">
                    <div className="sign-detail-container">
                        <div className="ps-guide">비밀번호는 8~20자 / 영어대소문자+숫자+특수문자 </div>
                        <input type="text" placeholder="  PASSWORD를 입력해주세요" className="sign-id-textbox"
                        value={ps} onChange={handlePasswordChange} maxLength={20}/>
                    </div>
                    <div className="check-ps-length">{ps.length}</div>
                </div>
                <div className="input-container">
                    <div className="sign-detail-container">
                        {
                            psCheck
                            ?<div className="re-ps-true">비밀번호가 일치하지 않습니다. 다시 입력해주세요.</div>
                            :<div className="re-ps">비밀번호가 일치하지 않습니다. 다시 입력해주세요.</div>
                        }
                        <input type="text" placeholder="  PASSWORD를 다시 입력해주세요" className="sign-id-textbox"
                        value={rePs} onChange={handleConfirmPasswordChange} maxLength={20}/>
                    </div>
                    <div className="check-ps-length">{rePs.length}</div>
                </div>
                <div className="margin-up"></div>
                <div className="sign-detail-container2">
                    <DropBox option={yearOptions}
                        onSelectionChange={handleYearSelectionChange}
                        startDropDetail = "출생연도"
                        Z ={5}
                    />
                    <div className="ss">:::</div>
                    <DropBox option={MonthOptions}
                        onSelectionChange={handleMonthSelectionChange}
                        startDropDetail = "월"
                        Z ={5}
                    />
                    <div className="ss">:::</div>
                    <DropBox option={dayOptions}
                        onSelectionChange={handleDaySelectionChange}
                        startDropDetail = "일"
                    />
                </div>
                <div className="sign-detail-container2">
                    <DropBox option={PhoneOptions}
                            onSelectionChange={handlePhoneSelectionChange}
                            startDropDetail = "핸드폰 번호"
                    />
                    <div className="ss2">-</div>
                    <input type="text" className="phone-box" maxLength={4}
                    pattern="\d*" inputMode="numeric" onChange={handlePhoneChange1}/>
                    <div className="ss2">-</div>
                    <input type="text" className="phone-box" maxLength={4}
                    pattern="\d*" inputMode="numeric" onChange={handlePhoneChange2}/>
                </div>
                <button className="sign-up-buttom" onClick={CheckSignUp}>회원가입</button>
            </div>
            <Footer/>
        </div>
    );
}