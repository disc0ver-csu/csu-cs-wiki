--1．创建一个PROFILE文件pTester，设置锁定用户的登录失败次数为3次，会话的总计连接时间60分钟，口令可用天数30天
create profile c##pTester limit FAILED_LOGIN_ATTEMPTS 3 connect_time 60 password_life_time 30;

select profile,resource_name,limit from dba_profiles where profile = 'C##PTESTER';

--2．创建一个新用户Tester，密码为Tester123，缺省表空间是tabspace_????。在tabspace_????表空间中可以使用50M空间，指定环境资源文件为pTester。
create tablespace test_tabspace_J305
datafile 'D:/sql/test_tabspace_J305.dbf'
size 1g
autoextend on
next 10m;

--3．将角色RESOURCE指派给用户Tester。
create user c##Tester
identified by Tester123
default tablespace test_tabspace_J305
quota 50M
on test_tabspace_J305
profile c##pTester;

grant resource, create session, dba to c##Tester;


--4．用EXP和IMP工具将之前创建的major_????表导入到Tester用户下。
exp c##_J305/c##_J305@ORCL file=D:/sql/major_J305.dmp tables=major_J305
imp c##Tester/Tester123@ORCL file=D:/sql/major_J305.dmp tables=major_J305








set serveroutput on

create or replace procedure exp_table
as
cursor test is select * from major_J305;
begin
for test_record in test
loop
dbms_output.put_line(test_record);
end loop;
END;
/



create or replace procedure test1(t_name varchar2) 
as
cursor cur_col is select column_name,data_type,data_length 
                  from  user_tab_columns  
                  where Table_Name = t_name; 

v_file UTL_FILE.file_type;

v_col_name varchar2(50);
v_col_type varchar2(20);
v_col_long varchar2(50);
v_vaule varchar2(50);
v_rownum int;
str_make varchar2(500) :='create table '||t_name||'(';
str_code varchar2(500);
str_col varchar2(500):='';
str_value varchar2(500) :='';
Begin
    select num_rows into v_rownum from dba_tables where table_name=t_name and owner='C##TESTER';
    v_file := UTL_FILE.FOPEN('MY_DIR', 'test.txt', 'W');
     open cur_col; 
     loop 
            fetch cur_col into v_col_name,v_col_type,v_col_long;
            exit when cur_col %NOTFOUND;
            str_make := str_make||v_col_name||' '||v_col_type||'('||v_col_long||'),' ;
            str_col := str_col||v_col_name||',';
     end loop;
     close cur_col;
     UTL_FILE.put_line(v_file, str_make||');');
    for i in 1..v_rownum loop
        open cur_col; 
        loop 
            fetch cur_col into v_col_name,v_col_type,v_col_long;
            exit when cur_col %NOTFOUND;
            str_code:= 'select '||v_col_name||' from (select rownum r, '||t_name||'.* from '||t_name||') e where e.r='||i;
            EXECUTE IMMEDIATE str_code into v_vaule ;
            str_value:=str_value||v_vaule||',';
        end loop;
        close cur_col;
        UTL_FILE.put_line(v_file, 'insert into table '||t_name||'('||str_col||') values ('||str_value||');');
        str_value:='';
    end loop;
    UTL_FILE.FCLOSE(v_file);
End;
/
