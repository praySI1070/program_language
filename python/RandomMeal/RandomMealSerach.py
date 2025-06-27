import requests as re
from bs4 import BeautifulSoup
import json
import random
import math


def RandomMealSerach(url):
    header = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/134.0.0.0 Safari/537.36'}
    rep = re.get(url, headers=header)
    html = rep.text
    soup = BeautifulSoup(html,'html.parser')

    if rep.status_code == 200:
        print("접속 성공!")
    else:
        print(f"접속 실패. 상태 코드: {rep.status_code}")

    soup = BeautifulSoup(html, 'html.parser')
    dish_count = soup.select_one(f'#contents_area_full > ul > div > b').text.replace(",","")
    int_dish_count = int(dish_count)
    page = math.ceil(int_dish_count / 40.0)
    random_page = random.randint(1,page)

    url = url + "&page=" + str(random_page)

    header = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/134.0.0.0 Safari/537.36'}
    rep = re.get(url, headers=header)
    html = rep.text
    soup = BeautifulSoup(html,'html.parser')

    if rep.status_code == 200:
        print("접속 성공!")
        #파일로 저장
        with open('data3.json', 'w', encoding='utf-8') as f:
            json.dump(html, f, ensure_ascii=False, indent=4)
    else:
        print(f"접속 실패. 상태 코드: {rep.status_code}")

    serachList = []
    soup = BeautifulSoup(html, 'html.parser')

    # class가 'common_sp_caption_tit line2'인 모든 태그 찾기
    elements = soup.find_all(class_='common_sp_caption_tit line2')

    print(f"len_element : {len(elements)}")

    for element,count in zip(elements,range(1,41)):
        temp = {}
        temp['text'] = element.text
        link = soup.select_one(f'#contents_area_full > ul > ul > li:nth-child({count}) > div.common_sp_thumb > a')
        temp['url'] = 'https://www.10000recipe.com'+link.get('href')
        serachList.append(temp)
    
    len_serachList = len(serachList)
    print(f"len_serachList : {len_serachList}")

    random_selection = random.sample(serachList, len_serachList)
    print(random_selection)
    return random_selection



if __name__ == "__main__":
    #RandomMealSerach('https://www.10000recipe.com/recipe/list.html?q=&query=&cat1=&cat2=&cat3=&cat4=&fct=&order=reco&lastcate=cat3&dsearch=&copyshot=&scrap=&degree=&portion=&time=&niresource=?q=&query=&cat1=&cat2=&cat3=50&cat4=&fct=&order=reco&lastcate=cat3&dsearch=&copyshot=&scrap=&degree=&portion=&time=&niresource=')
    RandomMealSerach('https://www.10000recipe.com/recipe/list.html?q=&query=&cat1=&cat2=13&cat3=&cat4=&fct=&order=reco&lastcate=cat3&dsearch=&copyshot=&scrap=&degree=&portion=&time=&niresource=')