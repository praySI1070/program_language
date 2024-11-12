import "./index.css";
import {useState, useCallback} from "react";
import Header from "../../components/Header";
import Start1 from "./start1";
import Summary from "./summary";
import New from "./new";
import Controll from "./controll";
import Footer from "../../components/Footer";



export default function Home() {
    const [isOpenModal, setOpenModal] = useState<boolean>(false);



    return (
        <div className="Home">
            <Header/>
            <Start1/>
            <div className="reverse">
                <Start1/>
            </div>
            <Summary/>
            <New/>
            <Controll/>
            <Footer/>
        </div>
    );
}