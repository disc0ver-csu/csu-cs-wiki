'''
@Description: 
@Author: 妄想
@Date: 2020-06-24 19:09:58
@LastEditTime: 2020-06-24 19:10:29
@LastEditors: 妄想
'''
from scrapy.http import Request
from scrapy.downloadermiddlewares.downloadtimeout import DownloadTimeoutMiddleware

class Timeout_Middleware(DownloadTimeoutMiddleware):
    def process_exception(self,request, exception, spider):
        #print "####the downloader has exception!"
        print(exception)
        return request.replace(dont_filter=True)