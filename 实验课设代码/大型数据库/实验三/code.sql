-- 创建表记录各操作时间
drop table t_record_time_J305;
create table t_record_time_J305(
	operate varchar(128),
	times varchar(32));

-- 创建过程
create or replace procedure p_record_time_J305(input varchar)
as
temp varchar(32);
begin
	select to_char(systimestamp, 'yyyy-mm-dd hh24:mi:ss.ff') into temp from dual;
	insert into t_record_time_J305(operate) values(input);
	update t_record_time_J305 set times=temp where operate=input;
end;
/

exec p_record_time_J305('创建过程')
col operate format a40;
col times format a32;
select * from t_record_time_J305;

-- 创建姓名表
drop table tname;
create table tname(name varchar(32));

-- 插入姓名 约5w条
exec p_record_time_J305('开始导入原始姓名')
@C:\Users\ITryagain\Desktop\大型数据库\实验\实验三\name.txt
commit;
exec p_record_time_J305('导入原始姓名结束')

set pagesize 10000

-- 制造足够多的姓名
-- 为名字的每个字创建视图
-- 128 * 1700 * 56
drop view v_name1_J305;
drop view v_name2_J305;
drop view v_name3_J305;
drop view v_name12_J305;
drop view v_name123_J305;
create view v_name1_J305 as select * from (select distinct substr(name,1,1) na1 from tname order by dbms_random.value);
create view v_name2_J305 as select * from (select distinct substr(name,2,1) na2 from tname order by dbms_random.value) where rownum<=1700;
create view v_name3_J305 as select * from (select distinct substr(name,3,1) na3 from tname order by dbms_random.value) where rownum<=56;
create view v_name12_J305 as select concat(na1,na2) na12 from v_name1_J305,v_name2_J305;
create view v_name123_J305 as select concat(na12,na3) na123 from v_name12_J305,v_name3_J305;


-- 创建t_stu_name_J305学生姓名表
drop table t_stu_name_J305;
create table t_stu_name_J305(sname varchar(16));
-- 为姓名表t_stu_name_J305插入12403200条学生姓名
insert into t_stu_name_J305(sname) select na12 from v_name12_J305;
insert into t_stu_name_J305(sname) select na123 from v_name123_J305;
exec p_record_time_J305('完成为姓名表生成12403200条记录')
select count(*) from t_stu_name_J305;

-- 学号 性别 电话 邮箱 生日

-- 生成规范学号表
--  ABCD16EFGH:每次生成两位，分四批生成，可以在1分钟左右生成
--建立过程中要使用的表
drop table t_student_sno_gh_J305;
drop table t_student_sno_ef_J305;
drop table t_student_sno_cd_J305;
drop table t_student_sno_ab_J305;
create table t_student_sno_gh_J305(sno number(10));
create table t_student_sno_ef_J305(sno number(10));
create table t_student_sno_cd_J305(sno number(10));
create table t_student_sno_ab_J305(sno varchar(10));

--建立过程：
declare
i int;
begin
	for i in 1..32 loop -- 班内序号
		insert into t_student_sno_gh_J305 values(i);
	end loop;
	for i in 1..50 loop -- 班级序号
		insert into t_student_sno_ef_J305 select 160000+i*100+t_student_sno_gh_J305.sno from t_student_sno_gh_J305;
		commit;
	end loop;
	for i in 1..90 loop -- 专业序号
		insert into t_student_sno_cd_J305 select i*1000000+t_student_sno_ef_J305.sno from t_student_sno_ef_J305;
		commit;
	end loop;
	for i in 1..80 loop -- 学院序号
		insert into t_student_sno_ab_J305 select substr(10000000000+i*100000000+t_student_sno_cd_J305.sno,2,10) from t_student_sno_cd_J305;
		commit;
	end loop;
end;
/

exec p_record_time_J305('完成11520000条学号ID生成')

--   批量处理sex, tel, email, birthday等数据
--   产生随机性别：男、女占比为99%到99.5%
--   在性别表t_sex_j432中，143人，男女分别71人，一人性别为其它。随机查询一条记录时，可使男、女占比为99.3%
--   函数f_getSex_j432返回值为随机性别
create or replace function f_getSex_J305 return varchar
is
f_numb number;
f_sex varchar(8);
begin
	select trunc(dbms_random.value(1,143)) into f_numb from dual;
	if f_numb<=71 then
		f_sex:= '男';
	elsif f_numb<=142 then
		f_sex:= '女';
	else
		f_sex:= '其他';
	end if;
return f_sex;
end;
/
show error

-- 邮箱随机生成
drop table t_email_J305;
create table t_email_J305(email varchar(32));
insert into t_email_J305 values('126');
insert into t_email_J305 values('gmail');
insert into t_email_J305 values('163');
insert into t_email_J305 values('qq');
insert into t_email_J305 values('formial');
insert into t_email_J305 values('sina');
insert into t_email_J305 values('139');
insert into t_email_J305 values('sohu');
insert into t_email_J305 values('csu.edu');

create or replace function f_getEmail_J305 return varchar
is
Email varchar(32);
em_name varchar(16);
en_own varchar(16);
begin
	select substr(cast(dbms_random.value as varchar(32)),3,11) into em_name from dual;
	select email into en_own from (select email from t_email_J305 order by dbms_random.value) where rownum=1;
	if en_own='csu.edu' then
		Email:=em_name||'@'||en_own||'.cn';
	else
		Email:=em_name||'@'||en_own||'.com';
	end if;
return Email;
end;
/

-- 电话随机生成
drop table t_tel_J305;
create table t_tel_J305(tel varchar(4));
insert into t_tel_J305 values('132');
insert into t_tel_J305 values('135');
insert into t_tel_J305 values('136');
insert into t_tel_J305 values('138');
insert into t_tel_J305 values('139');
insert into t_tel_J305 values('150');
insert into t_tel_J305 values('151');
insert into t_tel_J305 values('153');
insert into t_tel_J305 values('156');
insert into t_tel_J305 values('158');
insert into t_tel_J305 values('186');
insert into t_tel_J305 values('188');

create or replace function f_getTel_J305 return varchar
is
Tel varchar(12);
tel_head varchar(4);
tel_tail varchar(8);
begin
	select substr(cast(dbms_random.value as varchar(32)),3,8) into tel_tail from dual;
	select tel into tel_head from (select tel from t_tel_J305 order by dbms_random.value) where rownum=1;
	Tel:=tel_head||tel_tail;
return Tel;
end;
/

-- 生日随机生成 [19940101, 19970731]
create or replace function f_getBirthday_J305 return date
is
birthday date;
max_dis number(8);
min_dis number(8);
begin
	max_dis:=ceil(sysdate-to_date('19940102','yyyy-mm-dd'));
	min_dis:=ceil(sysdate-to_date('19970731','yyyy-mm-dd'));
	select trunc(sysdate - dbms_random.value(min_dis,max_dis),'dd') into birthday from dual;
	--select to_date(trunc(dbms_random.value(2449354,2451186)),'J') into birthday from dual;
return birthday;
end;
/
exec p_record_time_J305('性别、手机号、邮箱、出生日期等随机函数生成完毕')

-- 建立基本信息模板表
drop table t_sequence_id;
create table t_sequence_id(
	id number(16),
	sex varchar(32),
	tel varchar(32),
	email varchar(32),
	birthday date
);

drop table t_stud_other_information_J305;
create table t_stud_other_information_J305(
	id number(16),
	sex varchar(32),
	tel varchar(32),
	email varchar(32),
	birthday date
);


begin
delete from t_sequence_id;
for i in 0..9999 loop
	insert into t_sequence_id(id, sex, tel, email,birthday) values(i,f_getSex_J305,f_getTel_J305,f_getEmail_J305,f_getBirthday_J305);
end loop;
end;
/

exec p_record_time_J305('生成12000000条其他信息生成')
begin
delete from t_stud_other_information_J305;
for i in 0..1199 loop
--begin
--delete from t_sequence_id;
--for i in 0..9999 loop
--	insert into t_sequence_id(id, sex, tel, email,birthday) values(i,f_getSex_J305,f_getTel_J305,f_getEmail_J305,f_getBirthday_J305);
--end loop;
--end;
	insert into t_stud_other_information_J305(id,sex,tel,email,birthday) select i * 10000 + t_sequence_id.id as MSISDN,t_sequence_id.sex,t_sequence_id.tel,t_sequence_id.email,t_sequence_id.birthday from t_sequence_id;
commit;
end loop;
end;
/
select count(*) from t_stud_other_information_J305;
exec p_record_time_J305('完成生成12000000条其他信息生成')

exec p_record_time_J305('学生信息表有主键，生成11520000条记录，开始时间')
drop table t_stud_J305;
create table t_stud_J305(
	sno varchar(10),
	sname varchar(32),
	sex varchar(32),
	tel varchar(32),
	email varchar(32),
	birthday date
);
-- 通过表格自带序号连接
insert into t_stud_J305(sno, sname, sex, tel, email, birthday) 
select X.sno,A.sname, B.sex, B.tel, B.email, B.birthday 
from 
(select rownum rownum_X,sno from t_student_sno_ab_J305) X, 
(select rownum rownum_A,sname from t_stu_name_J305) A, 
(select rownum rownum_B,sex,tel,email,birthday from t_stud_other_information_J305) B 
where rownum_A = rownum_B and rownum_A = rownum_X;
exec p_record_time_J305('学生信息表有主键，生成11520000条记录，完成时间')

--为学生表添加其它约束
alter table t_stud_J305 add constraint ck_stud_sex check(sex in('男','女','其它','其他'));
alter table t_stud_J305 add constraint ck_stud_email check(email like '%@%.%');
alter table t_stud_J305 add constraint ck_stud_birthday check(birthday>=to_date('19940101','yyyymmdd') and birthday<=to_date('19970731','yyyymmdd'));

exec p_record_time_J305('没有姓名索引，查询姓氏开始')
select count(*) from t_stud_J305 where sname like '王%';
exec p_record_time_J305('没有姓名索引，查询姓氏结束')

exec p_record_time_J305('没有姓名索引，查询姓名开始')
select * from t_stud_J305 where sname='王莺';
exec p_record_time_J305('没有姓名索引，查询姓名结束')

exec p_record_time_J305('没有姓名索引，统计某一姓名第二个字相同人数开始')
select count(*) from t_stud_J305 where sname like '_莺%';
exec p_record_time_J305('没有姓名索引，统计某一姓名第二个字相同人数结束')


drop index i_stu_sname_J305;
exec p_record_time_J305('开始创建姓名索引')
create index i_stu_sname_J305 on t_stud_J305(sname);
exec p_record_time_J305('完成创建姓名索引')

exec p_record_time_J305('有姓名索引，查询姓氏开始')
select count(*) from t_stud_J305 where sname like '王%';
exec p_record_time_J305('有姓名索引，查询姓氏结束')

exec p_record_time_J305('有姓名索引，查询姓名开始')
select * from t_stud_J305 where sname='王莺';
exec p_record_time_J305('有姓名索引，查询姓名结束')

exec p_record_time_J305('有姓名索引，统计某一姓名第二个字相同人数开始')
select count(*) from t_stud_J305 where sname like '_莺%';
exec p_record_time_J305('有姓名索引，统计某一姓名第二个字相同人数结束')

exec p_record_time_J305('没有分区，按学号首位ID统计人数的开始时间')
select count(*) from t_student_J305 where sno like '5%';
exec p_record_time_J305('没有分区，按学号首位ID统计人数的结束时间') 

exec p_record_time_J305('没有分区，按专业统计人数的开始时间')
select count(*) from t_student_j432 where sno like '______01%';
exec p_record_time_J305('没有分区，按专业统计人数的结束时间')

-- 重建学生表，分区
drop table t_stud_J305;
create table t_stud_J305(
	sno varchar(10),
	sname varchar(32),
	sex varchar(32),
	tel varchar(32),
	email varchar(32),
	birthday date)
	partition by range(sno)(
	partition part_0 values less than ('1000160000'),
	partition part_1 values less than ('2000160000'),
	partition part_2 values less than ('3000160000'),
	partition part_3 values less than ('4000160000'),
	partition part_4 values less than ('5000160000'),
	partition part_5 values less than ('6000160000'),
	partition part_6 values less than ('7000160000'),
	partition part_7 values less than ('8000160000'),
	partition part_8 values less than ('9000160000'),
	partition part_9 values less than (maxvalue)
);
-- 通过表格自带序号连接
insert into t_stud_J305(sno, sname, sex, tel, email, birthday) 
select X.sno,A.sname, B.sex, B.tel, B.email, B.birthday 
from 
(select rownum rownum_X,sno from t_student_sno_ab_J305) X, 
(select rownum rownum_A,sname from t_stu_name_J305) A, 
(select rownum rownum_B,sex,tel,email,birthday from t_stud_other_information_J305) B 
where rownum_A = rownum_B and rownum_A = rownum_X;
exec p_record_time_J305('学生信息表有主键，生成11520000条记录，完成时间')

--为学生表添加其它约束
alter table t_stud_J305 add constraint ck_stud_sex check(sex in('男','女','其它','其他'));
alter table t_stud_J305 add constraint ck_stud_email check(email like '%@%.%');
alter table t_stud_J305 add constraint ck_stud_birthday check(birthday>=to_date('19940101','yyyymmdd') and birthday<=to_date('19970731','yyyymmdd'));

exec p_record_time_J305('有分区，按学号首位ID统计人数的开始时间')
select count(*) from t_student_J305 where sno like '5%';
exec p_record_time_J305('有分区，按学号首位ID统计人数的结束时间') 

exec p_record_time_J305('有分区，按专业统计人数的开始时间')
select count(*) from t_student_j432 where sno like '______01%';
exec p_record_time_J305('有分区，按专业统计人数的结束时间')

set linesize 300;
set pagesize 1000;
col things format a64;
col times format a32;
select * from t_record_time_J305 order by times;




--BEGIN  
--  FOR i IN 1 .. 10 LOOP  
--   exec dbms_output.put_line(ceil(sysdate-to_date('19940101','yyyy-mm-dd')));  
--   exec dbms_output.put_line(to_date(to_char(sysdate,'yyyyMMdd'),'yyyy-mm-dd')-9447); 
--  END LOOP;  
--END;  

--select ceil((to_date('2019-05-02 00:00:00', 'yyyy-mm-dd hh24-mi-ss') - to_date('2019-04-30 23:59:59', 'yyyy-mm-dd hh24-mi-ss'))) from dual;


--select sysdate - dbms_random.value(min_dis,max_dis) from dual;
