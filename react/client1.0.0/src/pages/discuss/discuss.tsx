import "./discuss.css";
import {HeaderNoIndex} from "../../components/Header";
import Footer from "../../components/Footer";
import { useState,useEffect } from "react";
import {useLogIn} from "../../components/logincontext";
const REACT_APP_API_URL = process.env.REACT_APP_API_URL || "localhost:6500";

export default function Discuss() {
    const [json,setJson] = useState<any[]>([]);
    const [page,setPage] = useState<number>(1);
    const [indexPage,setIndexPage] = useState<number>(1);

    const con_num:number = 9;
    const max_index_num:number = 10;
    const [pages,setPages] = useState<number>(1);
    const [index_num,setIndex_num] = useState<number>(Math.ceil(pages / 8));
    const [last_index,setLast_index] = useState<number>(Math.ceil(pages / (con_num * max_index_num)));

    const [fqaDetail,setFqaDetail] = useState<string>('');

    const {logIn,userId} = useLogIn();

    const [reset,setReset] = useState<boolean>(false);

    const onSubmitEnter = (e: React.KeyboardEvent) => {
        if(e.key === 'Enter') {
            test1111();
        }
    };

    const GetFqa = async () => {
        const idd = document.getElementById('write-button') as HTMLButtonElement;
        const id = idd?.value;

        try {
            const response = await fetch(`http://${REACT_APP_API_URL}/discuss`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ id }),
                credentials: 'include'
            });
            if (!response.ok) {
                throw new Error('네트워크 응답에 실패했습니다.');
            }
            const data = await response.json();
            setJson(data); // json 상태 업데이트
        } catch (error) {
            console.error('데이터 요청 오류:', error);
        }
    };

    useEffect(() => {
        GetFqa(); // useEffect 안에서 함수 호출
        
    }, []); // 빈 배열로 useEffect가 한 번만 실행되도록 설정

    const updatePages = async () => {
        GetFqa();
        if (json.length > 0) {
            // 비동기 작업을 위한 await 사용
            await setPages(json.length);
            await setIndex_num(Math.ceil(json.length / con_num));
            await setLast_index(Math.ceil(json.length / (con_num * max_index_num)));
        }
    };

    useEffect( () => {
        updatePages();
    }, [json]); // json이 업데이트될 때마다 이 effect가 실행됨

    useEffect(() => {
        updatePages();
    }, [reset]);
    

    const test1111 = async () => {
        if(!logIn) {
            alert("로그인 해주세요.");
            return;
        }
        try {
            await fetch(`http://${REACT_APP_API_URL}/discussInput`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({fqaDetail}),
                credentials: 'include'
            })
             .then(res=>res.json())
             .then(data=> {
                if(data['check']) {
                    alert("저장되었습니다.");
                    setReset(!reset);
                }
                else {
                    alert("저장에 실패했습니다.");
                    console.log("11");
                }
             });
        } catch (error) {
            console.error('FQA input 오류:',error);
        }
    }

    const handlePage = (key : number) => {
        setPage(key);
    }

    const handleIndexPage = (pivot : number) => {

        if(pivot > 0) {
            if(indexPage >= last_index) {
                return;
            }
            setIndexPage(indexPage+1);
        }
        else {
            if(indexPage <=1) {
                return;
            }
            setIndexPage(indexPage-1);
        }
    }

    const handleFristIndexPage = () => {
        setIndexPage(1);
    }

    const handleLastIndexPage = () => {
        setIndexPage(last_index);
    }

    const handleFqaDetailChange = (e : React.ChangeEvent<HTMLTextAreaElement>) => {
        setFqaDetail(e.target.value);
    }

    return(
        <div className="discuss">
            <HeaderNoIndex/>
            <div className="discuss-container">
                <div className="title">FQA</div>

                {
                    <div className="read-discuss-container-list">
                        {json && json.length > 0 && Array.from({length:con_num}).map((_,index) => {
                            const nowPage = pages - (page-1) * con_num - (index+1);
                            if(nowPage <= -1) {
                                return;
                            }
                            const currentData = json[nowPage];
                            if (!currentData) return null;

                            const { id, date, count, detail } = currentData;
                            
                            const processedDate = typeof date === 'string' ? date.substring(0, 19) : 'none';

                            return(

                            <div key={index} className="read-discuss-container">
                                <div className="read-container1">
                                    <div className="read-count">{count}</div>
                                    <div className="read-id">{id}</div>
                                    <div className="read-date">{processedDate}</div>
                                </div>
                                <div className="read-detail">{detail}</div>
                            </div>
                            );
                        })}
                    </div>
                }

                <div className="count-container">
                    <div className="count-container-box" onClick={handleFristIndexPage}>&lt;&lt;</div>
                    <div className="count-container-box" onClick={() => handleIndexPage(-1)}>&lt;</div>

                    {json && json.length > 0 && Array.from({length:max_index_num}).map((_,index) => {
                        const nowIndexPage = (indexPage-1)*max_index_num + index;
                        if(nowIndexPage >= index_num) {
                            return;
                        }

                        return(
                            <div key={nowIndexPage} className={`count-container-box ${nowIndexPage===page-1?"select-count-container-box":""}`} onClick={() => handlePage(nowIndexPage + 1)}>{nowIndexPage+1}</div>

                        );
                    })}
                    
                    <div className="count-container-box" onClick={() => handleIndexPage(1)}>&gt;</div>
                    <div className="count-container-box" onClick={handleLastIndexPage}>&gt;&gt;</div>
                </div>
                <div className="write-discuss-container">
                    <textarea placeholder="FQA에 작성할 내용을 입력해주세요." className="write-textbox"
                    value={fqaDetail} onChange={handleFqaDetailChange}
                    onKeyDown={onSubmitEnter}
                    />
                    <button className="write-button" id="write-button" onClick={test1111}>입력</button>
                </div>
            </div>
            <Footer/>
            <div className="sss0"/>
        </div>
    );
}