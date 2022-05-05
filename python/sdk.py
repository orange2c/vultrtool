import requests
import json

class SDK_V2:
    """基本的api读取函数"""
    text = ''
    API_KEY = ''
    
    money = '' #余额

    class account:
        name = '' #用户名
        email = ''

    def transfer(self, path, data='' ):
        """用于发送api及读取数据"""
        url = 'https://api.vultr.com/v2/' + path
        headers ={
        "Authorization": "Bearer "+self.API_KEY
        }
        return requests.get(url,  headers=headers, data=data, timeout=2).text

    def __init__(self, API_KEY ) -> None:
        self.API_KEY = API_KEY
        account =  json.loads(self.transfer("account"))["account"]
        self.account.name = account["name"]
        self.account.email = account["email"]

import main