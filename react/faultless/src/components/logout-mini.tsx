import "./logout-mini.css";
import { useLogIn } from "./logincontext"; // useLogIn 훅을 가져옵니다.

export default function LogOutMini() {
    const { userId, userRank, userSignDate, setLogIn, setUserId } = useLogIn(); // 로그인 상태 및 정보 가져오기

    // 로그아웃 처리
    const Logout = async () => {
        try {
            console.log(userRank);
            const response = await fetch("http://localhost:6500/logout", {
              method: "POST",
              credentials: "include", // 쿠키 포함
            });
      
            const data = await response.json();
      
            if (data.message === 'Logged out successfully') {
              // 로그인 상태를 false로 설정
              setLogIn(false);
              setUserId(''); // 로그아웃 후 userId도 초기화
      
              
            } else {
              console.error('로그아웃 실패:', data.error);
            }
          } catch (error) {
            console.error('로그아웃 중 오류 발생:', error);
          }
    };

    // 회원탈퇴 처리 (추가 구현 필요)
    const MemberOut = async () => {
        // 회원탈퇴 API 호출
        const response = await fetch("http://localhost:7000/member-out", {
            method: "DELETE",  // 회원탈퇴는 DELETE 요청으로 처리할 수 있습니다.
            credentials: "include",
        });

        if (response.ok) {
            setLogIn(false); // 로그인 상태를 false로 설정
            window.location.href = "/"; // 홈으로 이동
        }
    };

    return (
        <div className="logoutmini-main">
            <div className="invisible-box"></div>
            <div className="id-container">
                <span>ID</span>
                <div className="id-text">{userId}</div> {/* 로그인된 사용자 아이디 표시 */}
            </div>
            <div className="ranking-container">
                <span>랭킹</span>
                <div className="ranking">{userRank}</div> {/* 로그인된 사용자 랭킹 표시 */}
            </div>
            <div className="sign-date-container">
                <span>가입일</span>
                <div className="sign-date">{userSignDate}</div> {/* 로그인된 사용자 가입일 표시 */}
            </div>
            <div className="button-container">
                <button className="logout-button" onClick={Logout}>로그아웃</button>
                <button className="logout-button" onClick={MemberOut}>회원탈퇴</button>
            </div>
        </div>
    );
}