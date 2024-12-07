import React, { useEffect, useState } from "react";
import Router from "./components/Router";
import { LogInProvider, useLogIn  } from "./components/logincontext";
import Loading from '../src/components/Loading';



function App() {
  const { checkSession } = useLogIn();  // LogInContext에서 checkSession 사용
  const { logIn } = useLogIn();  // 로그인 상태 가져오기
  const [loading, setLoading] = useState<boolean>(true); // 로딩 상태 관리

  // 컴포넌트가 로딩될 때 로그인 상태를 확인하는 API 호출
  useEffect(() => {
    checkSession();
    const timer = setTimeout(() => {
      setLoading(false); // 2초 후 로딩 상태 변경
    }, 2000);

    return () => clearTimeout(timer); // 타이머 정리
  }, []);

  return (
    <LogInProvider>
      <div>
        {loading ? (
          <Loading /> // 로딩 중일 때 Loading 컴포넌트를 렌더링
        ) : (
          <Router/> // 로딩이 끝나면 App 컴포넌트를 렌더링
        )}
      </div>
    </LogInProvider>
  );
}

export default App;
