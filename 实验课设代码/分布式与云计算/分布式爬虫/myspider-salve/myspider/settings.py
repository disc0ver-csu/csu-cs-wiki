'''
@Description: 
@Author: 妄想
@Date: 2020-06-23 13:27:00
@LastEditTime: 2020-06-23 15:21:39
@LastEditors: 妄想
'''
# -*- coding: utf-8 -*-

# Scrapy settings for myspider project
#
# For simplicity, this file contains only settings considered important or
# commonly used. You can find more settings consulting the documentation:
#
#     https://docs.scrapy.org/en/latest/topics/settings.html
#     https://docs.scrapy.org/en/latest/topics/downloader-middleware.html
#     https://docs.scrapy.org/en/latest/topics/spider-middleware.html

BOT_NAME = 'myspider'

SPIDER_MODULES = ['myspider.spiders']
NEWSPIDER_MODULE = 'myspider.spiders'


# Crawl responsibly by identifying yourself (and your website) on the user-agent
#USER_AGENT = 'myspider (+http://www.yourdomain.com)'

# Obey robots.txt rules
ROBOTSTXT_OBEY = True

# Configure maximum concurrent requests performed by Scrapy (default: 16)
#CONCURRENT_REQUESTS = 32

# Configure a delay for requests for the same website (default: 0)
# See https://docs.scrapy.org/en/latest/topics/settings.html#download-delay
# See also autothrottle settings and docs
#DOWNLOAD_DELAY = 3
# The download delay setting will honor only one of:
#CONCURRENT_REQUESTS_PER_DOMAIN = 16
#CONCURRENT_REQUESTS_PER_IP = 16

# Disable cookies (enabled by default)
COOKIES_ENABLED = False

# redis
# # 调度器，在 redis 里分配请求
# SCHEDULER = "scrapy_redis.scheduler.Scheduler"
# # 去重
# DUPEFILTER_CLASS = "scrapy_redis.dupefilter.RFPDupeFilter"
# # 在 redis 中保持 scrapy-redis 用到的各个队列，从而允许暂停和暂停后恢复，即不清理 redis queue
# SCHEDULER_PERSIST = True
# # ITEM_PIPELINES={
# #     'scrapy_redis.pipelines.RedisPipeline': 400,
# # }
# SCHEDULER_QUEUE_CLASS = 'scrapy_redis.queue.SpiderPriorityQueue'
# REDIS_HOST = '120.26.177.209'
# REDIS_PORT = '6379'
# REDIS_ENCODING = 'utf-8'
# REDIS_PARAMS = {'password': '123456'}