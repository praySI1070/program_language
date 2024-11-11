import React, { useState, useEffect } from 'react';
import ReactDOM from 'react-dom/client';
import { Routes, BrowserRouter as Router } from 'react-router-dom';
import './index.css';
import App from './App';
import reportWebVitals from './reportWebVitals';
import Header from "../src/components/Header";
import Loading from '../src/components/Loading';

const Index = () => {
  const [loading, setLoading] = useState<boolean>(true); // 로딩 상태 관리

  useEffect(() => {
    const timer = setTimeout(() => {
      setLoading(false); // 2초 후 로딩 상태 변경
    }, 4000);

    return () => clearTimeout(timer); // 타이머 정리
  }, []);

  return (
    <div>
      {loading ? (
        <Loading /> // 로딩 중일 때 Loading 컴포넌트를 렌더링
      ) : (
        <App /> // 로딩이 끝나면 App 컴포넌트를 렌더링
      )}
    </div>
  );
};


const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);
root.render(
  <Router>
    <React.StrictMode>
      <Index />
    </React.StrictMode>
  </Router>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
