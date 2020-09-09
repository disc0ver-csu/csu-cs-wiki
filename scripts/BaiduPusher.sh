###
 # @Description: 
 # @Author: 妄想
 # @Date: 2020-06-17 14:17:14
 # @LastEditTime: 2020-06-17 14:18:10
 # @LastEditors: 妄想
### 
#!/usr/bin/env bash
source /etc/profile
ORG=CSU
REPO=csu-cs-wiki
# Baidu Pusher 

# Sitemap Parser
pip install bs4
python scripts/Sitemap_Parser.py

cd site
#Use Curl
head='http://data.zz.baidu.com/urls?site='
tokenhead='&token='
URL=$head$site$tokenhead$BaiduToken
curl -H 'Content-Type:text/plain' --data-binary @sitemap.txt "$URL"

