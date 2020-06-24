'''
@Description: 
@Author: 妄想
@Date: 2020-06-23 13:27:00
@LastEditTime: 2020-06-24 19:12:20
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

#抓取网站的最大允许的抓取深度值
DEPTH_LIMIT=0

# Obey robots.txt rules
ROBOTSTXT_OBEY = True

# Configure maximum concurrent requests performed by Scrapy (default: 16)
#CONCURRENT_REQUESTS = 32

# Configure a delay for requests for the same website (default: 0)
# See https://docs.scrapy.org/en/latest/topics/settings.html#download-delay
# See also autothrottle settings and docs
DOWNLOAD_DELAY = 3
DOWNLOADER_MIDDLEWARES = {
    'scrapy.contrib.downloadermiddleware.httpproxy.HttpProxyMiddleware': 110,
    "myspider.Proxy_Middleware.ProxyMiddleware":100,
    'scrapy.downloadermiddlewares.robotstxt.RobotsTxtMiddleware': 100,
    'scrapy.downloadermiddlewares.defaultheaders.DefaultHeadersMiddleware': 550,
    'scrapy.downloadermiddlewares.ajaxcrawl.AjaxCrawlMiddleware': 560,
    'scrapy.downloadermiddlewares.httpcompression.HttpCompressionMiddleware': 590,
    'scrapy.downloadermiddlewares.chunked.ChunkedTransferMiddleware': 830,
    'scrapy.downloadermiddlewares.stats.DownloaderStats': 850,
    'myspider.timeout_middleware.Timeout_Middleware':610,
    'scrapy.downloadermiddlewares.httpauth.HttpAuthMiddleware': None,
    'scrapy.downloadermiddlewares.useragent.UserAgentMiddleware': 300,
    'scrapy.downloadermiddlewares.retry.RetryMiddleware': None,
    'scrapy.downloadermiddlewares.redirect.MetaRefreshMiddleware': None,
    'scrapy.downloadermiddlewares.redirect.RedirectMiddleware': 400,
    'scrapy.downloadermiddlewares.cookies.CookiesMiddleware': None,
    'scrapy.downloadermiddlewares.httpcache.HttpCacheMiddleware': None,
    'myspider.useragent_dowmload_middleware.py.RotateUserAgentMiddleware':400,
    'myspider.redirect_middleware.Redirect_Middleware':500,

}

# Disable cookies (enabled by default)
COOKIES_ENABLED = False


# 使用scrapy-redis组件，分布式运行多个爬虫
SCHEDULER = "scrapy_redis.scheduler.Scheduler"
DUPEFILTER_CLASS = "scrapy_redis.dupefilter.RFPDupeFilter"
SCHEDULER_PERSIST = True
SCHEDULER_QUEUE_CLASS = 'scrapy_redis.queue.SpiderPriorityQueue'
REDIS_URL = None
REDIS_HOST = '127.0.0.1'
REDIS_PORT = '6379'