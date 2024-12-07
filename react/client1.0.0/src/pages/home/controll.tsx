import "./controll.css";
import magic from "../../img/c_ani.gif";
import keyboardLeft from "../../img/keyboard_left.png";
import keyboardRight from "../../img/keyboard_right.png"

export default function Controll() {
    return(
        <div className="controll-container">
            <div className="controll-title">조작법</div>
            <div className="detail-container">
                <div className="player-text">1P</div>
                <div className="battle-container">
                    <div className="battle-container-1p">
                        <img src= {keyboardRight} alt="keyboard" className="key-container"/>
                        <img src= {magic} alt="magic" className="magic"/>
                    </div>
                    <div className="VS">VS</div>
                    <div className="battle-container-2p">
                        <img src= {keyboardLeft} alt="keyboard" className="key-container-2p"/>
                        <img src= {magic} alt="magic" className="magic-2p"/>
                    </div>
                </div>
                <div className="player-text-2">2P</div>
            </div>
        </div>
    );
}