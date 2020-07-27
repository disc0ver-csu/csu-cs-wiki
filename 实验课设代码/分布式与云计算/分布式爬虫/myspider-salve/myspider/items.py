'''
@Description: 
@Author: 妄想
@Date: 2020-06-23 13:27:00
@LastEditTime: 2020-06-24 19:35:52
@LastEditors: 妄想
'''
# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class MyspiderItem(scrapy.Item):
    """
        用于保存爬取到的数据
    """
    # title = scrapy.Field()
    size = scrapy.Field()
    url = scrapy.Field()
