from receive import rev_msg
import socket
import requests
import random
import datetime
import time
import urllib.request
from urllib.parse import quote
import string

qq_robot=eval(input('请输入机器人QQ号：'))

def send_msg(resp_dict):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    ip = '127.0.0.1'
    client.connect((ip, 5700))

    msg_type = resp_dict['msg_type']  # 回复类型（群聊/私聊）
    number = resp_dict['number']  # 回复账号（群号/好友号）
    msg = resp_dict['msg']  # 要回复的消息

    # 将字符中的特殊字符进行url编码
    msg = msg.replace(" ", "%20")
    msg = msg.replace("\n", "%0a")

    if msg_type == 'group':
        payload = "GET /send_group_msg?group_id=" + str(
            number) + "&message=" + msg + " HTTP/1.1\r\nHost:" + ip + ":5700\r\nConnection: close\r\n\r\n"
    elif msg_type == 'private':
        payload = "GET /send_private_msg?user_id=" + str(
            number) + "&message=" + msg + " HTTP/1.1\r\nHost:" + ip + ":5700\r\nConnection: close\r\n\r\n"
    print("发送" + payload)
    client.send(payload.encode("utf-8"))
    client.close()
    return 0

def horoscope(constellation):
    # 请求地址
    key='db1b32985a782773b2446c1e0b2cbac7'
    url = "http://web.juhe.cn/constellation/getAll?" + 'consName={}&type=today&key={}'.format(constellation,key)
    # 发送get请求
    r = requests.get(url)
    # 获取返回的json数据
    result = r.json()['summary']
    #print(result)
    return result

while True:
    qq_list=[] #输入要定时发送消息的QQ号
    now = datetime.datetime.now()
    if(now.hour==0 and now.minute==0):
        for qq in qq_list:
            send_msg({'msg_type': 'private', 'number': qq, 'msg': '晚安！'})
            send_msg({'msg_type': 'private', 'number': qq, 'msg':'[CQ:poke,qq={}]'.format(qq)})
        time.sleep(60)
        continue
    if (now.hour == 7 and now.minute == 0):
        for qq in qq_list:
            send_msg({'msg_type': 'private', 'number': qq, 'msg': '早安！'})
            send_msg({'msg_type': 'private', 'number': qq, 'msg': '[CQ:poke,qq={}]'.format(qq)})
        time.sleep(60)
        continue
    try:
        rev = rev_msg()
        print(rev)
        if rev == None:
            continue
    except:
        continue
    if rev["post_type"] == "message":
        #print(rev) #需要功能自己DIY
        if rev["message_type"] == "private": #私聊
            message=rev['raw_message']
            qq = rev['sender']['user_id']
            if 'face' in message:
                qq = rev['sender']['user_id']
                img = rev['raw_message']
                send_msg({'msg_type': 'private', 'number': qq, 'msg': img})
            elif 'image' in message:
                qq = rev['sender']['user_id']
                img=rev['raw_message']
                send_msg({'msg_type': 'private', 'number': qq, 'msg': img})
            elif '戳一戳' in message:
                qq = rev['sender']['user_id']
                send_msg({'msg_type': 'private', 'number': qq, 'msg': '别戳了'})
            elif '星座运势' in message:
                try:
                    constellation = message.split(' ')[1]

                    text = horoscope(constellation)
                    qq = rev['sender']['user_id']
                    send_msg({'msg_type': 'private', 'number': qq, 'msg': text})
                except:
                    qq = rev['sender']['user_id']
                    send_msg({'msg_type': 'private', 'number': qq, 'msg': '请在星座前面加上空格。'})
            else:
                url = 'http://api.qingyunke.com/api.php?key=free&appid=0&msg=' + message
                s = quote(url, safe=string.printable)
                try:
                    with urllib.request.urlopen(s) as response:
                        html = response.read()
                        # 将获取到的响应内容进行解码，并将json字符串内容转换为python字典格式
                        # 通过下标取到机器人回复的内容
                        qq = rev['sender']['user_id']
                        # print(eval(html.decode("utf-8"))["content"])
                        send_msg({'msg_type': 'private', 'number': qq,
                                  'msg': eval(html.decode("utf-8"))["content"].replace('{br}', '\n')})
                        # print(eval(html.decode("utf-8"))["content"])
                except:
                    qq = rev['sender']['user_id']
                    send_msg({'msg_type': 'private', 'number': qq, 'msg': '重新连接中。。。'})
        elif rev["message_type"] == "group":  # 群聊
            group = rev['group_id']
            if "[CQ:reply]" in rev["raw_message"] and "[CQ:at,qq={}]".format(qq_robot) in rev["raw_message"]:
                message = rev['raw_message'].split(' ')[2]
                #print(message)
                url = 'http://api.qingyunke.com/api.php?key=free&appid=0&msg=' + message
                s = quote(url, safe=string.printable)
                try:
                    with urllib.request.urlopen(s) as response:
                        html = response.read()
                        # 将获取到的响应内容进行解码，并将json字符串内容转换为python字典格式
                        # 通过下标取到机器人回复的内容
                        qq = rev['sender']['user_id']
                        # print(eval(html.decode("utf-8"))["content"])
                        send_msg({'msg_type': 'group', 'number': group,
                                  'msg': eval(html.decode("utf-8"))["content"].replace('{br}', '\n')})
                        # print(eval(html.decode("utf-8"))["content"])
                except:

                    send_msg({'msg_type': 'group', 'number': group, 'msg': '重新连接中。。。'})
            elif "[CQ:at,qq={}]".format(qq_robot) in rev["raw_message"]:
                try:
                    if rev['raw_message'].split(' ')[1] == '在吗':
                        qq = rev['sender']['user_id']
                        send_msg({'msg_type': 'group', 'number': group, 'msg': '[CQ:poke,qq={}]'.format(qq)})
                    elif rev['raw_message'].split(' ')[1] == '星座运势':

                        try:
                            constellation = rev['raw_message'].split(' ')[2]
                            text = horoscope(constellation)
                            send_msg({'msg_type': 'group', 'number': group, 'msg': text})
                        except:
                            send_msg({'msg_type': 'group', 'number': group, 'msg': '请在星座前面加上空格。'})
                    else:
                        message = rev['raw_message'].split(' ')[1]
                        url = 'http://api.qingyunke.com/api.php?key=free&appid=0&msg=' + message
                        s = quote(url, safe=string.printable)
                        try:
                            with urllib.request.urlopen(s) as response:
                                html = response.read()
                                # 将获取到的响应内容进行解码，并将json字符串内容转换为python字典格式
                                # 通过下标取到机器人回复的内容
                                qq = rev['sender']['user_id']
                                # print(eval(html.decode("utf-8"))["content"])
                                if 'face' in eval(html.decode("utf-8"))["content"]:

                                    send_msg({'msg_type': 'group', 'number': group,
                                              'msg': '[CQ:face,id=32]'})
                                else:
                                    send_msg({'msg_type': 'group', 'number': group,
                                          'msg': eval(html.decode("utf-8"))["content"].replace('{br}', '\n')})
                                # print(eval(html.decode("utf-8"))["content"])
                        except:

                            send_msg({'msg_type': 'group', 'number': group, 'msg': '重新连接中。。。'})
                except:
                    continue
        else:
            continue
    elif rev["post_type"] == "notice":
        try:
            if rev['sub_type'] == 'poke' and rev['target_id'] == qq_robot and rev['group_id']!=None:
                group = rev['group_id']
                send_msg({'msg_type': 'group', 'number': group, 'msg': '戳我干嘛！'})
        except:
            continue
    else:
        continue