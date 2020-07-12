'''
@Description: 
@Author: 妄想
@Date: 2020-06-25 13:00:50
@LastEditTime: 2020-06-25 16:01:15
@LastEditors: 妄想
'''
from util.config import Config
from util.models import MySpider
from sqlalchemy.orm import sessionmaker
from sqlalchemy import create_engine

class MysqlPipeline(object):
    
    def __init__(self):
        engine = create_engine(Config.SQLALCHEMY_DATABASE_URI)
        DBSession = sessionmaker(bind=engine)
        self.session = DBSession()
    
    def process_item(self, item, spider):
        model = MySpider(
            url=item['url'],
            size=item['size']
        )
        self.session.add(model)
        self.session.commit()
        print('New item {} added to DB.'.format(item['url']))
        return item
    
    def close_spider(self, spider):
        try:
            self.session.commit()
        except:
            self.session.rollback()
            raise
        finally:
            self.session.close()
