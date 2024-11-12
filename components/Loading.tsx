import './Loading.css';
import Spinner from '../img/Loading.gif';

export default function Loading() {
    return (
        <div className = "Loading-container">
            <img src = {Spinner} alt="Spinner" className='Loading-img'/>
        </div>
    );
}