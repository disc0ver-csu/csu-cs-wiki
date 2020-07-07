create tablespace tablespace_j610 datafile 'D:/Codes/SQL/tablespace_j610.dbf'size 3G autoextend on next 100M extent management local;

  --4.使用EXP导出数据与IMP导入数据（在cmd窗口下直接输入命令）

  --先查询网络服务端口：select name from v$database;

  --查询结果为：ORAL

   

  --将数据库完全导出到D盘（时间较长）

  exp U_J610/J610@BIGDATA file=D:/Codes/SQL/base.dmp full=y

  --导出用户U_J610的表

  exp U_J610/J610@BIGDATA file=D:/Codes/SQL/UserTables.dmp owner=U_J610

  --导出指定表：stud_j610

  exp U_J610/J610@BIGDATA file=D:/Codes/SQL/Tables.dmp tables=stud_j610
/
   

  --导入数据库

  imp U_J610/J610@BIGDATA file=D:/Codes/SQL/base.dmp full=y ignore=y

  --导入数据库中的表

  imp U_J610/J610@BIGDATA file=D:/Codes/SQL/UserTables.dmp tables=stud_j610

  --直接导入文件表（也需要添加tables限定）

  imp system/p610@BIGDATA file=D:/Codes/SQL/Tables.dmp tables=stud_j610

   

  --5备份系统表空间以及自定义表空间

  --导出系统表空间users

  exp system/p610@BIGDATA file=D:/Codes/SQL/tableSpaceUsers.dmp tablespaces=users

  --导出自定义表空间tablespace_j610

  exp system/p610@BIGDATA file=D:/Codes/SQL/tableSpaceOwn.dmp tablespaces=tablespace_j610

   

  --恢复系统表空间users

  imp system/p610@BIGDATA file=D:/Codes/SQL/tableSpaceUsers.dmp tablespaces=users

  --恢复自定义表空间tablespace_j610

  imp system/p610@BIGDATA file=D:/Codes/SQL/tableSpaceOwn.dmp tablespaces=tablespace_j610

   

  --6登录DBA用户system，通过cat字典入口，找到以DBA_开头的相关数据字典，并且每个对象显示5条记录（SQL生成SQL）

  --登录dba

  set linesize 1000

  set pagesize 100

  col SESSION_ID format 999999;

  col LOCK_TYPE format a32;

  col MODE_HELD format a32;

  col MODE_REQUESTED format a32;

  col LOCK_ID1 format a32;

  col LOCK_ID2 format a32;

  col LAST_CONVERT format 9999;

  col BLOCKING_OTHERS format a32;

  col CON_ID format 9999;

  conn system/p610 as sysdba

  spool D:/Codes/SQL/dba.txt;

  select 'select * from '||tname||' where rownum<=5;' from publicsyn where tname like 'DBA%';

  spool off;

  @D:/Codes/SQL/dba.txt

   

  --7.查找自己用户下的触发器字典，生成代码将所有触发器的状态改为disable并执行。再生成代码，将状态为disable的触发器的状态改为enable，并执行。

  --查找所有的触发器

  select trigger_name from user_triggers;

   

  spool D:/Codes/SQL/disableTri.txt

  select 'alter trigger '||trigger_name||' disable;' from user_triggers;

  spool off;

  @D:/Codes/SQL/disableTri.txt

   

  spool D:/Codes/SQL/enableTri.txt

  select 'alter trigger '||trigger_name||' enable;' from user_triggers;

  spool off;

  @D:/Codes/SQL/enableTri.txt
