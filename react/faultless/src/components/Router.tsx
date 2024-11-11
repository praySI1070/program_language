import {Route, Routes,Navigate, Link} from "react-router-dom";
import Home from "../pages/home/index";

export default function Router() {
    return (
        <>
            <Routes>
                <Route path='/' element={<Home/>}/>
            </Routes>
        </>
    )
}