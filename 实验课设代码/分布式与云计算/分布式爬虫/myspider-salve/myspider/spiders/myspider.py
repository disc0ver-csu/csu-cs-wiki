'''
@Description: 
@Author: 妄想
@Date: 2020-06-23 13:34:08
@LastEditTime: 2020-06-23 19:37:39
@LastEditors: 妄想
'''

import scrapy
from scrapy_redis.spiders import RedisSpider
from scrapy.spiders import Spider
from scrapy.selector import Selector
from myspider.items import MyspiderItem
import re

class MySpider(Spider):
    name = 'myspidersalve'
    # redis_key = 'start_urls'
    # allowed_domains = ['cnblogs.com']
    start_urls = [
        "https://www.cnblogs.com/csu-lmw/"
    ]
    seen_set = set([])

    def parse(self, response):
        
        myspiderItem = MyspiderItem
        selector = Selector(response)

        yield {     
            'url': response.url,
            'size': self.format_bytes(int(len(response.body))),
        }
        
        # for cnblogs
        sel = selector.xpath('//*[@id="mainContent"]/div/div/div/a/@href').extract()
        for url in sel:
            if url.endswith('.html'):
                yield response.follow(url, callback=self.parse) 

        for url in selector.xpath('//*[@id="cnblogs_post_body"]/p/a/@href').extract():
            
            yield response.follow(url, callback=self.parse)

        next_url = response.xpath(u'//*[@id="nav_next_page"]/a/@href').extract_first()
        if next_url != None:
            yield scrapy.Request(next_url,callback=self.parse)
        
        next_url = response.xpath(u'//*[@id="homepage_bottom_pager"]/div/a/@href').extract()
        for url in next_url:
            if url.endswith("1") == False:
                yield scrapy.Request(url,callback=self.parse)
        
        # for most web page
        urls = response.css('a::attr(href)').re(r'^/.+?/$') 
        for url in urls:
            yield response.follow(url, callback=self.parse) 
            
    def format_bytes(self, size):
        # 2**10 = 1024
        power = 2**10
        n = 0
        power_labels = {0 : ' b', 1: ' KB', 2: ' MB', 3: ' GB', 4: ' TB'}
        while size > power:
            size /= power
            n += 1
        return str(size) + power_labels[n]
