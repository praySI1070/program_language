import "./controll.css";
import magic from "../../img/c_ani.gif";
import keyboard from "../../img/keyboard.png";

export default function Controll() {
    return(
        <div className="controll-container">
            <div className="controll-title">조작법</div>
            <div className="detail-container">
                <img src= {magic} alt="magic" className="magic"/>
                <img src= {keyboard} alt="keyboard" className="key-container"/>
            </div>
        </div>
    );
}