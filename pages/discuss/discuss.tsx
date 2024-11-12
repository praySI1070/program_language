import "./discuss.css";
import Header from "../../components/Header";
import Footer from "../../components/Footer";

export default function Discuss() {
    return(
        <div className="discuss">
            <Header/>
            <div className="discuss-container">
                <div className="title">FQA</div>
                <div className="write-discuss-container">
                    <textarea placeholder="내용을 입력해주세요." className="write-textbox"/>
                    <button className="write-button">입력</button>
                </div>
            </div>
            <Footer/>
        </div>
    );
}