import React, { createContext, useContext, useState, useEffect, ReactNode } from 'react';

// 1. Context에서 사용할 상태와 관련된 타입 정의
interface LogInContextType {
  logIn: boolean;
  userId: string;
  userRank: string;
  userSignDate: string;
  setLogIn: React.Dispatch<React.SetStateAction<boolean>>; // 상태를 변경하는 함수
  setUserId: React.Dispatch<React.SetStateAction<string>>;
  setUserRank: React.Dispatch<React.SetStateAction<string>>; // rank 상태 변경 함수
  setUserSignDate: React.Dispatch<React.SetStateAction<string>>; // 가입일 상태 변경 함수
}

// 2. 기본값 설정 (만약 LogInContext.Provider가 없을 때)
const defaultContextValue: LogInContextType = {
  logIn: false,
  userId: '',
  userRank: '',
  userSignDate: '',
  setLogIn: () => {}, // 기본값을 빈 함수로 설정
  setUserId: () => {},
  setUserRank: () => {}, // 기본값을 빈 함수로 설정
  setUserSignDate: () => {}, // 기본값을 빈 함수로 설정
};

// 3. LogInContext 생성
const LogInContext = createContext<LogInContextType>(defaultContextValue);

// 4. Custom Hook을 통해 Context 값 사용
export const useLogIn = () => {
  return useContext(LogInContext);
};

// 5. LogInProvider 컴포넌트 타입 정의
interface LogInProviderProps {
  children: ReactNode;  // children이 React 노드 타입임을 정의
}

export const LogInProvider: React.FC<LogInProviderProps> = ({ children }) => {
  // 6. 상태 정의
  const [logIn, setLogIn] = useState<boolean>(false);
  const [userId, setUserId] = useState<string>('');
  const [userRank, setUserRank] = useState<string>('');  // rank 상태
  const [userSignDate, setUserSignDate] = useState<string>('');  // 가입일 상태

  const checkSession = async () => {
    const response = await fetch('http://localhost:6500/check-session', {
      method: 'GET',
      credentials: 'include', // 쿠키 포함
    });
    
    const result = await response.json();
    if (result.loggedIn) {
      setLogIn(true);
      setUserId(result.user);
      setUserRank(result.rank);  // rank 설정
      setUserSignDate(result.signDate);  // 가입일 설정
    }
  };

  useEffect(() => {
    checkSession();
  }, []);

  return (
    <LogInContext.Provider value={{ 
      logIn, 
      userId, 
      userRank, 
      userSignDate, 
      setLogIn, 
      setUserId, 
      setUserRank, 
      setUserSignDate 
    }}>
      {children}
    </LogInContext.Provider>
  );
};
