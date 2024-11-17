import "./discuss.css";
import {HeaderNoIndex} from "../../components/Header";
import Footer from "../../components/Footer";

export default function Discuss() {
    

    const ccc = () => {
        const idd = document.getElementById('write-button') as HTMLButtonElement;
        const id = idd?.value;

        fetch('http://localhost:5000/discuss')
    };

    return(
        <div className="discuss">
            <HeaderNoIndex/>
            <div className="discuss-container">
                <div className="title">FQA</div>
                <div className="read-discuss-container">
                    11
                </div>
                <div className="read-discuss-container"/>
                <div className="read-discuss-container"/>
                <div className="read-discuss-container"/>
                <div className="read-discuss-container"/>
                <div className="read-discuss-container"/>
                <div className="read-discuss-container"/>
                <div className="read-discuss-container"/>
                <div className="count-container">
                    <div className="count-container-box">&lt;&lt;</div>
                    <div className="count-container-box">&lt;</div>
                    <div className="count-container-box">1</div>
                    <div className="count-container-box"/>
                    <div className="count-container-box">1</div>
                    <div className="count-container-box"/>
                    <div className="count-container-box">1</div>
                    <div className="count-container-box"/>
                    <div className="count-container-box">1</div>
                    <div className="count-container-box"/>
                    <div className="count-container-box">1</div>
                    <div className="count-container-box"/>
                    <div className="count-container-box">&gt;</div>
                    <div className="count-container-box">&gt;&gt;</div>
                </div>
                <div className="write-discuss-container">
                    <textarea placeholder="내용을 입력해주세요." className="write-textbox"/>
                    <button className="write-button" id="write-button" onClick={ccc}>입력</button>
                </div>
            </div>
            <Footer/>
        </div>
    );
}