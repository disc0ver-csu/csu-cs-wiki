'''
@Description: 
@Author: 妄想
@Date: 2020-06-23 13:34:08
@LastEditTime: 2020-06-24 19:49:44
@LastEditors: 妄想
'''

from scrapy_redis.spiders import RedisSpider
from scrapy.selector import Selector
from util.redisUtil import RedisUtil

class MySpider(RedisSpider):
    name = 'myspider'
    redis_key = 'start_urls'
    # allowed_domains = ['cnblogs.com']
    # start_urls = [
    #     "https://www.cnblogs.com/csu-lmw/"
    # ]
    redis_util = RedisUtil("127.0.0.1", 6379)

    def parse(self, response):
        selector = Selector(response)

        # yield {     
        #     'url': response.url,
        #     'size': self.format_bytes(int(len(response.body))),
        # }
        
        # for cnblogs
        sel = selector.xpath('//*[@id="mainContent"]/div/div/div/a/@href').extract()
        for url in sel:
            if url.endswith('.html'):
                self.redis_util.insert(url, 1)
                self.redis_util.insert(url, 2)
                # yield response.follow(url, callback=self.parse) 

        for url in selector.xpath('//*[@id="cnblogs_post_body"]/p/a/@href').extract():
            self.redis_util.insert(url, 1)
            self.redis_util.insert(url, 2)
            # yield response.follow(url, callback=self.parse)

        next_url = response.xpath(u'//*[@id="nav_next_page"]/a/@href').extract_first()
        if next_url != None:
            self.redis_util.insert(next_url, 1)
            self.redis_util.insert(next_url, 2)
            # yield scrapy.Request(next_url,callback=self.parse)
        
        next_url = response.xpath(u'//*[@id="homepage_bottom_pager"]/div/a/@href').extract()
        for url in next_url:
            if url.endswith("1") == False:
                self.redis_util.insert(url, 1)
                self.redis_util.insert(url, 2)
                # yield scrapy.Request(url,callback=self.parse)
        
        # for most web page
        urls = response.css('a::attr(href)').re(r'^/.+?/$') 
        for url in urls:
            self.redis_util.insert(url, 1)
            self.redis_util.insert(url, 2)
            # yield response.follow(url, callback=self.parse) 