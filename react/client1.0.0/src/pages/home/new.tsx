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

const images:any[] = [rel0_00,rel1_01, rel1_02, rel1_03, rel1_04, rel1_05, rel1_06, rel1_07,rel999_99];

export default function New() {
    const [page,setPage] = useState<number>(1);
    const [openModal,setOpenModal] = useState<boolean>(false);
    const modalRef = useRef<HTMLDivElement>(null);

    const lastpage:number = data.length-2;
    
    // 모달 밖의 영역을 클릭하면 모달을 닫는 함수
    const handleOutsideClick = (event: MouseEvent) => {
        if (modalRef.current && !modalRef.current.contains(event.target as Node)) {
            setOpenModal(false);  // 모달 바깥을 클릭하면 closeModal 실행
        }
    };

    useEffect(() => {
        if (openModal) {
            // 문서 전체에 클릭 이벤트 리스너 추가
            document.addEventListener('mousedown', handleOutsideClick);
        } else {
            // 모달이 닫혔을 때 클릭 이벤트 리스너 제거
            document.removeEventListener('mousedown', handleOutsideClick);
        }
        return () => {
            document.removeEventListener('mousedown', handleOutsideClick);  // 컴포넌트 언마운트 시에도 이벤트 리스너 제거
        };
    }, [openModal]);

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

    const handleOpenModal = () => {
        setOpenModal(true);
    };

    const handleCloseModal = () => {
        setOpenModal(false);
    };

    return(
        <div className='new-container'>
            <div className='new-title'>새소식</div>

            { openModal
                ?<div className="text-modal" ref={modalRef}>
                    <div className='title-contaier'>
                        <div className='modal-title'>{data[page]['title']}</div>
                        <button className='close-modal' onClick={handleCloseModal}>X</button>
                    </div>
                    <div className='modal-detail'>
                        <div className='modal-detail-text'>
                            {data[page]['text'].split('<').map((word,index) => {
                                const wordSplit = word.split('>');
                                const abcd = wordSplit[0].split(':');
                                let fontWeight = 100;
                                let fontSize = 15;
                                if(abcd[0] === "we") {
                                    fontWeight = Number(abcd[1]);
                                }
                                else if(abcd[0] === "si") {
                                    fontSize = Number(abcd[1]);
                                }
                                

                                return(
                                    <span key={index} style={{ fontWeight,fontSize }}>
                                        {wordSplit[1]} 
                                    </span>
                                );
                            })}
                        </div>
                    </div>
                </div>
            :<div className='new-title-detail-container'>
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
            }
        </div>
    );
}