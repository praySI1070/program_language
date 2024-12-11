import './new.css';
import data from "../../newdata.json"
import rel0_00 from "../../img/0.00.png";
import rel1_01 from "../../img/1.01.png";
import rel1_02 from "../../img/1.02.png";
import rel1_03 from "../../img/1.03.png";
import rel1_04 from "../../img/1.04.png";
import rel1_05 from "../../img/1.05.png";
import rel1_06 from "../../img/1.06.png";
import rel1_07 from "../../img/1.07.png";
import rel999_99 from "../../img/999.99.png";
import { useState, useEffect, useRef } from 'react';

interface NewProps {
    setOpenModal: (isopenmodal : boolean) => void;
    dataUpdate: (title : string,text : string) => void;
};

const images:any[] = [rel0_00,rel1_01, rel1_02, rel1_03, rel1_04, rel1_05, rel1_06, rel1_07,rel999_99];

export default function New({setOpenModal, dataUpdate} : NewProps) {
    const [page,setPage] = useState<number>(1);

    const lastpage:number = data.length-2;

    useEffect(() => {
    }, [page]);

    const handleChangePage = (pivot:number) => {
        if(page+pivot > lastpage) {
            return;
        }
        else if(page+pivot < 1) {
            return;
        }
        setPage(page+pivot);
    };


    //index.tsx의 변수 바꾸기
    const handleOpenModal = async() => {
        await dataUpdate(data[page].title,data[page].text);
        setOpenModal(true);
    };
    //

    return(
        <div className='new-container'>
            <div className='new-title'>새소식</div>
            <div className='new-title-detail-container'>
                <div className={page>1 ? "left" : "left-hide"} onClick={() => handleChangePage(-1)}>
                    <img src={images[page-1]} alt='left' className='left-img'/>
                    <div className='left-text'>{data[page-1]['detail']}</div>
                </div>
                <div className={lastpage >= 1 ? "center" : "center-hide"} onClick={handleOpenModal}>
                    <img src={images[page]} alt='center' className='center-img'/>
                    <div className='center-text'>{data[page]['detail']}</div>
                </div>
                <div className={page<lastpage ? "right" : "right-hide"} onClick={() => handleChangePage(1)}>
                    <img src={images[page+1]} alt='right' className='right-img'/>
                    <div className='right-text'>{data[page+1]['detail']}</div>
                </div>
            </div>
        </div>
    );
}