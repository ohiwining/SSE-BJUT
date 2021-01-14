import requests
import time
import re
import json
import jieba
import pandas as pd

super_URL = 'https://bj.meituan.com/meishi/'
meituan_URL = 'https://www.meituan.com/meishi/'
categories = {'火锅': 'c17', '自助餐': 'c40', '小吃快餐': 'c36', '西餐': 'c35',
              '烧烤烤肉': 'c54', '川湘菜': 'c55', '香锅烤鱼': 'c20004', '西北菜': 'c58'
    , '素食': 'c217', '汤粥炖菜': 'c229'}
areas = {'朝阳区': 'b14', '东城区': 'b15', '西城区': 'b16', '海淀区': 'b17', '丰台区': 'b20', '石景山区': 'b172',
         '通州区': 'b4751', '顺义区': 'b708', '大兴区': 'b4752', '昌平区': 'b4750', '房山区': 'b710',
         '密云区': 'b2074', '门头沟区': 'b709', '平谷区': 'b2073', '延庆区': 'b2075', '怀柔区': 'b711'}
attributes = {'销量': 'sales', '价格': 'price_asc', '好评最多': 'rating'}


def get_page(url):
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:82.0) Gecko/20100101 Firefox/82.0',
    }
    res = requests.get(url=url, headers=headers)
    if res.status_code == 200:
        response = res.content.decode('utf-8')
        return response


def dishList(category='', area='', attribute='', page=1):
    div1 = '' if category == '' and area == '' else '/'
    div2 = '' if attribute == '' else '/'
    url = super_URL + category + area + div1 + attribute + div2 + 'pn' + str(page) + '/'
    response = get_page(url)
    response = re.findall(r'"poiInfos":(.*)},"comHeader"', response, re.S)[0]
    list = json.loads(response)
    return list


if __name__ == '__main__':
    # 注：一次只运行一个部分并将其他部分注释掉较好。因为数据量极大，会被
    # 美团防爬取程序检测到并实施IP封禁。其中4、5两部分需要进行多次分段运
    # 行，因为其本身的数据量就足以触发美团的防爬取机制。
    start_time = time.time()
    # 1.热销店名
    number_of_words = 1000  # 只保留出现最多的20个词
    filtered_words = ['（', '）']  # 过滤词汇
    titleName = []
    for page in range(1, 10):  # 爬取页码
        print("正在爬取第{}页。".format(page))
        dishlist = dishList(attribute=attributes['销量'], page=page)
        for i in dishlist:
            title = i['title']
            titleName.append(title)
    titleString = ''.join(titleName)
    titleWordList = list(jieba.cut(titleString))
    keywords = pd.Series(titleWordList)
    keywords = keywords[keywords.str.len() > 1]  # 筛选过短的词语
    crossed = keywords.str.contains('|'.join(filtered_words))  # 去除过滤词汇
    keywords = keywords[~crossed]
    keywords = keywords.value_counts()[:number_of_words]  # 去除频率较低的词
    keywords.to_csv('热销店名词.csv')  # 导出csv
    del keywords, title, filtered_words, dishlist, titleWordList, titleString, i, page, titleName


    # 2.北京各个区5星店的数量
    data = pd.DataFrame(columns=['区域', '数量'])
    for area in areas:
        print("正在爬取{}的店铺。".format(area))
        fiveStarNum = 0
        flag = True
        for page in range(1, 20):  # 低于4.8分的店一定会在20页内出现
            if not flag:
                break
            dishlist = dishList(area=areas[area], attribute=attributes['好评最多'], page=page)
            for i in dishlist:
                score = i['avgScore']  # 寻找评分标签
                if score <= 4.8:
                    flag = False
                else:
                    fiveStarNum += 1
        data = data.append({'区域': area, '数量': fiveStarNum}, ignore_index=True)  # 添加到表格中
    data.to_csv('各区5星店数量.csv')  # 导出数据
    del data, score, fiveStarNum, i, page, flag


    # 3.人均价格分布（30元一档）
    data = pd.DataFrame(columns=['价格', '数量'])
    priceLevel = {'30元以下': 0, '30-60元': 0, '60-90元': 0, '90-120元': 0, '120-150元': 0, '150-180元': 0, '180元以上': 0}
    for page in range(1, 20):
        print("正在爬取第{}页。".format(page))
        dishlist = dishList(attribute=attributes['好评最多'], page=page)
        for i in dishlist:
            price = i['avgPrice']  # 寻找价格标签
            if price < 30:
                priceLevel['30元以下'] += 1
            elif price >= 30 and price < 60:
                priceLevel['30-60元'] += 1
            elif price >= 60 and price < 90:
                priceLevel['60-90元'] += 1
            elif price >= 90 and price < 120:
                priceLevel['90-120元'] += 1
            elif price >= 120 and price < 150:
                priceLevel['120-150元'] += 1
            elif price >= 150 and price < 180:
                priceLevel['150-180元'] += 1
            elif price >= 180:
                priceLevel['180元以上'] += 1
    for item in priceLevel:
        data = data.append({'价格': item, '数量': priceLevel[item]}, ignore_index=True)  # 添加到表格中
    data.to_csv('人均价格分布.csv')  # 导出数据
    del data, item, priceLevel, price, page


    # 5.营业时间统计（数据过多 可能被美团识别到）
    data = {}
    shopId = []
    for page in range(1, 5):  # 爬取页码
        print("正在获取第{}页的ID。".format(page))
        dishlist = dishList(attribute=attributes['销量'], page=page)
        for i in dishlist:
            id = i['poiId']  # 获取店铺id
            shopId.append(id)
    print("正在获取营业时间...")
    num = 0
    for id in shopId:
        num += 1
        flag = True
        currentURL = '{}{}/'.format(meituan_URL, id)  # 店铺对应url
        html = str(get_page(currentURL))
        pattern = re.compile('"detailInfo":(.*?),"photos"', re.S)
        if re.search(pattern, html):
            detailInfos = re.search(pattern, html).group(1)
            detailInfo_dict = json.loads(detailInfos)
            openTimeStr = detailInfo_dict['openTime'].split()  # 找到店铺营业时间标签
            openTime = []
            for i in range(1, len(openTimeStr)):
                openTime.append(openTimeStr[i])
            for time in openTime:
                if time not in data.keys():  # 将数据存入表格
                    data[time] = 1
                else:
                    data[time] += 1
            del openTime
            print("进度：{}/{},正常。".format(num, len(shopId)))
        else:
            print("进度：{}/{},该店铺爬取失败。".format(num, len(shopId)))
    data = pd.DataFrame(pd.Series(data), columns=['数量'])
    data.to_csv('营业时间统计.csv')
    del data, shopId, openTimeStr, i, id, dishlist, detailInfos, num


    # 6.评论里什么词出现的最多
    number_of_words = 30  # 只保留出现最多的20个词
    filtered_words = ['（', '）', '「', '#', '」', '。', '：', '，', '的', '吃', '了', '也', '味道',
                      '好', '！', '很', '哈哈哈', '菜品', '都', '和', '是', '来', '小', '多', '有', '他们',
                      '不错', '比较', '以前', '觉得', '喜欢', '整体', '这个', '值得', '可以', '东西', '感觉',
                      '一家', '单人', '一般', '种类', '口味', '就餐', '各种', '孩子', '经常', '这家', '餐厅']  # 过滤词汇
    comments = []
    for page in range(11):
        print("正在爬取第{}页。".format(page + 1))
        url = 'https://www.meituan.com/meishi/api/poi/getMerchantComment?uuid=8689da73-fcaf-4dc4-bb68-cf477e0395b1&' \
              'platform=1&partner=126&originUrl=https%3A%2F%2Fwww.meituan.com%2Fmeishi%2F102918327%2F&riskLevel=1&optimus' \
              'Code=10&id=102918327&userId=&offset={}&pageSize=10&sortType=1'.format(page * 10)  # 具体一家店的评价链接
        html = get_page(url)
        content = json.loads(html)
        for item in content['data']['comments']:
            comments.append(item['comment'])
    print("爬取完成，正在处理...")
    commentString = ''.join(comments)
    commentWordList = list(jieba.cut(commentString))
    keywords = pd.Series(commentWordList)
    keywords = keywords[keywords.str.len() > 1]  # 筛选过短的词语
    crossed = keywords.str.contains('|'.join(filtered_words))  # 去除过滤词汇
    keywords = keywords[~crossed]
    keywords = keywords.value_counts()[:number_of_words]  # 去除频率较低的词
    keywords.to_csv('评论词语数量统计.csv')  # 导出csv
    del keywords, html, filtered_words, commentString, commentWordList, comments, item, page, filtered_words

    end_time = time.time()
    print("运行完成！共耗时{:.2f}秒".format(end_time - start_time))








