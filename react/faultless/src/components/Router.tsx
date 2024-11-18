import {Route, Routes,Navigate, Link} from "react-router-dom";
import Home from "../pages/home/index";
import Signup from "../pages/signup/signup";
import Discuss from "../pages/discuss/discuss";

export default function Router() {
    return (
        <>
            <Routes>
                <Route path='/' element={<Home/>}/>
                <Route path='/signup' element={<Signup/>}/>
                <Route path='/discuss' element={<Discuss/>}/>
            </Routes>
        </>
    )
}