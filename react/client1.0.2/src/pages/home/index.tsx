import "./index.css";
import {useState, useCallback, useEffect, useRef} from "react";
import Header from "../../components/Header";
import Start1 from "./start1";
import Summary from "./summary";
import New from "./new";
import Controll from "./controll";
import Modal from "../../components/Modal";
import Footer from "../../components/Footer";


type Data = {
    title: string;
    text : string;
};

export default function Home() {
    const [openModal,setOpenModal] = useState<boolean>(false);
    const [data, setData] = useState<Data>({ title: '', text: '' });
    const modalRef = useRef<HTMLDivElement>(null);

    const dataUpdate = (dataTitle : string, dataText : string) => {
        setData({ title: dataTitle, text: dataText });
    };

    // 모달 밖의 영역을 클릭하면 모달을 닫는 함수
    const handleOutsideClick = (event: MouseEvent) => {
        if (modalRef.current && !modalRef.current.contains(event.target as Node)) {
            setOpenModal(false);  // 모달 바깥을 클릭하면 closeModal 실행
        }
    };
    
    useEffect(() => {
        console.log(openModal);
        console.log(data);
        if (openModal) {
            // 문서 전체에 클릭 이벤트 리스너 추가
            document.addEventListener('mousedown', handleOutsideClick);
        } else {
            // 모달이 닫혔을 때 클릭 이벤트 리스너 제거
            document.removeEventListener('mousedown', handleOutsideClick);
        }
        return () => {
            document.removeEventListener('mousedown', handleOutsideClick);  // 컴포넌트 언마운트 시에도 이벤트 리스너 제거
        };
    }, [openModal]);

    useEffect(() => {

    }, [data]);

    return (
        <div className="Home" id="home">
            <Header/>
            {
                openModal
                ? <Modal data={data} modalRef = {modalRef} />
                : <div/>
            }
            <Start1/>
            <div className="reverse">
                <Start1/>
            </div>
            <div id="summary">
                <Summary/>
            </div>
            <div id="new">
                <New setOpenModal = {setOpenModal} dataUpdate = {dataUpdate}/>
            </div>
            <div id="controll">
                <Controll/>
            </div>
            <Footer/>
        </div>
    );
}