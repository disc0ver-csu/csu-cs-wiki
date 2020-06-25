'''
@Description: 
@Author: 妄想
@Date: 2020-06-25 14:25:49
@LastEditTime: 2020-06-25 14:38:18
@LastEditors: 妄想
'''
from sqlalchemy import Column, String, Integer, ForeignKey, Boolean, Text
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()

class MySpider(Base):
    __tablename__ = 'myspider'
    ID = Column(Integer, primary_key=True)
    url = Column(String(200), nullable=False)
    size = Column(String(32), nullable=False)