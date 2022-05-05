import json
from sdk import SDK_V2

# OPENAPI = {}
# with open('swagger.json','r',encoding='utf8')as fp:
#     OPENAPI = json.load(fp)
# print(OPENAPI["info"]["title"])


API_KEY = " "
vultr = SDK_V2(API_KEY)
print(vultr.account.name)
print(vultr.account.email)

