import {useState,useRef} from 'react';
import './Modal.css';

interface ModalProps {
    data : {
        title : string;
        text : string;
    };
    modalRef : React.RefObject<HTMLDivElement>;
}



export default function Modal ({data, modalRef} :ModalProps) {

    let fontWeight = 800;
    let fontSize = 100;

    return(
        <div>
            <div className='test-modal-side'/>
            <div className="text-modal" ref={modalRef}>
                <div className='title-contaier'>
                    <div className='modal-title'>{data['title']}</div>
                    
                </div>
                <div className='modal-detail'>
                    <div className='modal-detail-text'>
                        {data['text'].split('<').map((word,index) => {
                            console.log("word : ",index,":",word);
                            const wordSplit = word.split('>');
                            const abcd = wordSplit[0].split(':');
                            if(abcd[0] === "we") {
                                fontWeight = Number(abcd[1]);
                            }
                            else if(abcd[0] === "si") {
                                fontSize = Number(abcd[1]);
                            }
                            else if(abcd[0] === "m" && abcd[1] === "1") {
                                fontSize = 20;
                                fontWeight = 700;
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
        </div>
    );
}