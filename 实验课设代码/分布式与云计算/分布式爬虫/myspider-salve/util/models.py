'''
@Description: 
@Author: 妄想
@Date: 2020-06-25 14:25:49
@LastEditTime: 2020-06-25 16:21:48
@LastEditors: 妄想
'''
from sqlalchemy import Column, String, Integer, ForeignKey, Boolean, Text, DateTime
from sqlalchemy.ext.declarative import declarative_base
import datetime

Base = declarative_base()

class MySpider(Base):
    __tablename__ = 'myspider'
    ID = Column(Integer, primary_key=True)
    url = Column(String(200), nullable=False)
    size = Column(String(32), nullable=False)
    time = Column(DateTime, default=datetime.datetime.now)