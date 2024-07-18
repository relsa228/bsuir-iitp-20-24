--Создание таблицы
create table "MY_TABLE"
(
    "id" number primary key,
    val  number not null
)

--Создание автоинкремента
create sequence lab1_sec
start with 1
increment by 1;

--Заполнение значениями
declare
    random_num Number;
begin
    DBMS_OUTPUT.PUT_LINE(random_num);

    FOR i IN 15 ..10000 LOOP
        select round(DBMS_RANDOM.value(low => 1, high => 1000)) into random_num from dual;
        insert into MY_TABLE ("id", VAL) VALUES (lab1_sec.nextval, random_num);
    END LOOP;
end;

------------------------------------------------------------------------------
--Функция подсчета
create or replace function get_parity
return boolean
is
    parity_counter number;
    odd_counter number;
begin
    select COUNT(VAL) into parity_counter from MY_TABLE WHERE MOD(VAL, 2) = 0;
    select COUNT(VAL) into odd_counter from MY_TABLE WHERE MOD(VAL, 2) = 1;
    if parity_counter > odd_counter then
        return true;
    else
        return false;
    end if;
end

--Вызов функции
DECLARE
   res boolean;
BEGIN
   res := get_parity();
   if res then
        dbms_output.put_line('True');
    else
       dbms_output.put_line('False');
   end if;
END;

------------------------------------------------------------------------------
--Функция создания запроса
create or replace function get_insert (inpt_value in varchar2)
return varchar2
is
    result_str varchar2(100);
begin
    result_str := 'insert into MY_TABLE ("id", VAL) VALUES (lab1_sec.nextval, ' || inpt_value || ');';
    dbms_output.put_line(result_str);
    return result_str;
end;

--Вызов функции (с проверкой вывода)
DECLARE
   res varchar2(100);
BEGIN
   res := get_insert(123);
   dbms_output.put_line(res);
END;

--Процедуры
CREATE OR REPLACE PROCEDURE my_table_insert(new_value number)
AS
BEGIN
   insert into MY_TABLE ("id", VAL) VALUES (lab1_sec.nextval, new_value);
   commit;
END;

CREATE OR REPLACE PROCEDURE my_table_delete(del_id number)
AS
BEGIN
   delete from MY_TABLE where "id"=del_id;
    commit;
END;

CREATE OR REPLACE PROCEDURE my_table_update(updt_id number, new_value number)
AS
BEGIN
   update MY_TABLE set VAL=new_value where "id"=updt_id;
    commit;
END;

--------------------------------------------------------------------------------------
--Функция для зарплаты
create or replace function year_salary (salary in number, percent in number)
return number
is
    normal_percent number;
    result_salary number;
begin
    if salary <= 0 or percent < 0 then
        dbms_output.put_line('Incorrect input.');
        return -1;
    end if;
    normal_percent := percent / 100;
    result_salary := (1 + normal_percent) * 12 * salary;
    return result_salary;
exception
    WHEN OTHERS THEN
        dbms_output.put_line('Internal error.');
        return -1;
end;

--------------------------------------------------------------------------------------
--Специальное задание
create or replace function get_insert_2 (inpt_value in number)
return varchar2
is
    result_str varchar2(100);
    get_var number;
begin
    select VAL into get_var from MY_TABLE where "id" = inpt_value;
    result_str := 'insert into MY_TABLE ("id", VAL) VALUES ( '|| inpt_value ||', ' || get_var || ');';
    dbms_output.put_line(result_str);
    return result_str;

exception WHEN NO_DATA_FOUND THEN
       dbms_output.put_line('Error');
       return 'Error';
end;