import "./index.css";
import {useState, useCallback} from "react";
import Header from "../../components/Header";
import Start1 from "./start1";
import Summary from "./summary";
import New from "./new";
import Controll from "./controll";
import Footer from "../../components/Footer";



export default function Home() {
    


    return (
        <div className="Home" id="home">
            <Header/>
            <Start1/>
            <div className="reverse">
                <Start1/>
            </div>
            <div id="summary">
                <Summary/>
            </div>
            <div id="new">
                <New/>
            </div>
            <div id="controll">
                <Controll/>
            </div>
            <Footer/>
        </div>
    );
}