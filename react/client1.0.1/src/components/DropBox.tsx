import './DropBox.css';
import { useState,useRef } from 'react';

interface Props {
    option : (string | number)[];
    startDropDetail : string;
    onSelectionChange: (selected: string) => void; // 부모로 값을 전달하는 콜백 함수
    Z ?: number;    //z-index수정
}

export default function DropBox({option,startDropDetail,onSelectionChange,Z = 0}:Props) {
    const [isOpen,setIsOpen] = useState<boolean>(false);
    const [selectedOption,setSelectedOption] = useState<string>('');



    const DropdownIsOpen = () => {
        setIsOpen((prev) => !prev); //prev는 useState에서 쓰는 콜백함수의 인자
    }

    const selectDropdown = (Selectoption : number|string, index:number) => {
        const input = String(Selectoption);
        setSelectedOption(input);
        setIsOpen(false);
        onSelectionChange(input);

    }



    return(
        <div className="dropdown-container" style={{ zIndex: Z }}>
            {/* 드롭다운 헤더 (클릭 시 드롭다운 열기/닫기) */}
            <div onClick={DropdownIsOpen} className="dropdown-header">
                {selectedOption || `${startDropDetail}`}  {/* 선택된 값이 없으면 기본 텍스트 */}
            </div>
            {/* 드롭다운 메뉴 (열려 있을 때만 표시) */}
            {isOpen && (
                    <div className="dropdown-menu">
                        {option.map((opt, index) => (
                            <div
                                key={index}
                                className="dropdown-item"
                                onClick={() => selectDropdown(opt,index)}  // 항목 선택 시 호출
                            >
                                {opt}
                            </div>
                        ))}
                    </div>
                )}
        </div>
    );
}