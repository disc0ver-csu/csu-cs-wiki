'''
@Description: 
@Author: 妄想
@Date: 2020-06-23 13:27:00
@LastEditTime: 2020-06-25 14:42:17
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
DOWNLOAD_DELAY = 3
DOWNLOADER_MIDDLEWARES = {
    'scrapy.downloadermiddlewares.httpproxy.HttpProxyMiddleware': 110,
    # "myspider.Proxy_Middleware.ProxyMiddleware":100,
    'scrapy.downloadermiddlewares.robotstxt.RobotsTxtMiddleware': 100,
    'scrapy.downloadermiddlewares.defaultheaders.DefaultHeadersMiddleware': 550,
    'scrapy.downloadermiddlewares.ajaxcrawl.AjaxCrawlMiddleware': 560,
    'scrapy.downloadermiddlewares.httpcompression.HttpCompressionMiddleware': 590,
    # 'scrapy.downloadermiddlewares.chunked.ChunkedTransferMiddleware': 830,
    'scrapy.downloadermiddlewares.stats.DownloaderStats': 850,
    'myspider.timeout_middleware.Timeout_Middleware':610,
    'scrapy.downloadermiddlewares.httpauth.HttpAuthMiddleware': None,
    'scrapy.downloadermiddlewares.useragent.UserAgentMiddleware': 300,
    'scrapy.downloadermiddlewares.retry.RetryMiddleware': None,
    'scrapy.downloadermiddlewares.redirect.MetaRefreshMiddleware': None,
    'scrapy.downloadermiddlewares.redirect.RedirectMiddleware': 400,
    'scrapy.downloadermiddlewares.cookies.CookiesMiddleware': None,
    'scrapy.downloadermiddlewares.httpcache.HttpCacheMiddleware': None,
    'myspider.useragent_dowmload_middleware.RotateUserAgentMiddleware':400,
    # 'myspider.redirect_middleware.Redirect_Middleware':500,

}

#设置数据入库pipline
ITEM_PIPELINES = {
    'myspider.mysql_pipeline.MysqlPipeline': 10,
}

# Disable cookies (enabled by default)
COOKIES_ENABLED = False

# redis
# 调度器，在 redis 里分配请求
SCHEDULER = "scrapy_redis.scheduler.Scheduler"
# 去重
DUPEFILTER_CLASS = "scrapy_redis.dupefilter.RFPDupeFilter"
# 在 redis 中保持 scrapy-redis 用到的各个队列，从而允许暂停和暂停后恢复，即不清理 redis queue
SCHEDULER_PERSIST = True
# ITEM_PIPELINES={
#     'scrapy_redis.pipelines.RedisPipeline': 400,
# }
SCHEDULER_QUEUE_CLASS = 'scrapy_redis.queue.SpiderPriorityQueue'
REDIS_HOST = '120.26.177.209'
REDIS_PORT = '6379'
REDIS_ENCODING = 'utf-8'
REDIS_PARAMS = {'password': '123456'}