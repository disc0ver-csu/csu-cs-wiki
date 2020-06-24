'''
@Description: 
@Author: 妄想
@Date: 2020-06-23 13:34:08
@LastEditTime: 2020-06-23 14:04:56
@LastEditors: 妄想
'''

from scrapy_redis.spiders import RedisSpider
from scrapy.selector import Selector

class MySpider(RedisSpider):
    name = 'myspider'
    redis_key = 'start_urls'
    # allowed_domains = ['cnblogs.com']
    # start_urls = [
    #     "https://www.cnblogs.com/csu-lmw/"
    # ]

    def parse(self, response):
        pass