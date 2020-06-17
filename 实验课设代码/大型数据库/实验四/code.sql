create tablespace tablespace_J305 datafile 'D:\sql\tablespace_J305.dbf'size 3G autoextend on next 100M extent management local;

alter user c##_J305 default tablespace tablespace_J305;
select username,default_tablespace from user_users;

select name from v$database;

-- cmd
exp c##_J305/c##_J305@ORCL file=D:\sql\base.dmp full=y
--导出用户c##_J305的表
exp c##_J305/c##_J305@ORCL file=D:\sql\UserTables.dmp owner=c##_J305
--导出指定表：t_student_J305
exp c##_J305/c##_J305@ORCL file=D:\sql\Tables.dmp tables=major_J305 --stud_J305

--导入数据库
imp c##_J305/c##_J305@ORCL file=D:\sql\base.dmp full=y ignore=y
--导入数据库中的表
imp c##_J305/c##_J305@ORCL file=D:\sql\UserTables.dmp tables=major_J305 --stud_J305
--直接导入文件表（也需要添加tables限定）
imp system/123456@ORCL file=D:\sql\Tables.dmp tables=major_J305 --stud_J305

--导出系统表空间users
exp system/123456@ORCL file=D:/sql/tableSpaceUsers.dmp tablespaces=users
--导出自定义表空间tablespace_J305
exp system/123456@ORCL file=D:/sql/tableSpaceOwn.dmp tablespaces=tablespace_J305

--恢复系统表空间users
imp system/123456@ORCL file=D:/sql/tableSpaceUsers.dmp tablespaces=users full=y
--恢复自定义表空间tablespace_J305
imp system/123456@ORCL file=D:/sql/tableSpaceOwn.dmp tablespaces=tablespace_J305 full=y


--登录DBA用户system，通过cat字典入口，找到以DBA_开头的相关数据字典，并且每个对象显示5条记录（SQL生成SQL）
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
conn system/123456 as sysdba
spool D:/sql/dba.txt;
select 'select * from '||tname||' where rownum<=5;' from publicsyn where tname like 'DBA%';
spool off;
@D:/sql/dba.txt

--查找自己用户下的触发器字典，生成代码将所有触发器的状态改为disable并执行。再生成代码，将状态为disable的触发器的状态改为enable，并执行。
--查找所有的触发器
select trigger_name from user_triggers;
spool D:/sql/disableTri.txt
select 'alter trigger '||trigger_name||' disable;' from user_triggers;
spool off;
@D:/sql/disableTri.txt
spool D:/sql/enableTri.txt
select 'alter trigger '||trigger_name||' enable;' from user_triggers;
spool off;
@D:/sql/enableTri.txt
