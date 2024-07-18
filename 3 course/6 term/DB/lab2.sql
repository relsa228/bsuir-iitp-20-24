------------------------------------------------------------------------------
--0. Создание юзера для лабы
alter session set "_oracle_script"=TRUE;
create user LAB2;
ALTER USER LAB2 quota unlimited on USERS;

------------------------------------------------------------------------------
--1. Создание таблиц
create table LAB2."students"
(
    "id" number primary key,
    "name"  varchar2(30) not null,
    group_id number not null
);

create sequence LAB2.lab2_student
start with 1
increment by 1;

create table LAB2."groups"
(
    "id" number primary key,
    "name"  varchar2(30) not null,
    c_val number not null
);

create sequence LAB2.lab2_group
start with 1
increment by 1;

------------------------------------------------------------------------------
--2. Проверка целостности
CREATE OR REPLACE TRIGGER lab2.chk_unique_id_student        --wrk
    BEFORE INSERT OR UPDATE OF "name" ON lab2."students"
        FOR EACH ROW     
            FOLLOWS lab2.generate_uniq_student_id
DECLARE
    rowc NUMBER;
    e_not_unique_ident EXCEPTION;
    PRAGMA AUTONOMOUS_TRANSACTION;
    PRAGMA exception_init(e_not_unique_ident, -01422);
BEGIN 
    SELECT COUNT(*) INTO rowc FROM lab2."students" WHERE "id" = :new."id";
    IF rowc <> 0  THEN
        RAISE e_not_unique_ident;
    END IF;
END;

CREATE OR REPLACE TRIGGER lab2.chk_unique_groupname       --wrk
    BEFORE INSERT OR UPDATE OF "name" ON lab2."groups"
        FOR EACH ROW
DECLARE
    rowc NUMBER;
    e_not_unique_ident EXCEPTION;
    PRAGMA AUTONOMOUS_TRANSACTION;
    PRAGMA exception_init(e_not_unique_ident, -01422);
BEGIN 
    SELECT COUNT(*) INTO rowc FROM lab2."groups" WHERE "name" = :new."name";
    IF rowc <> 0  THEN
        RAISE e_not_unique_ident;
    END IF;
END;

CREATE OR REPLACE TRIGGER lab2.chk_unique_id_group              --wrk
    BEFORE INSERT OR UPDATE OF "name" ON lab2."groups"
        FOR EACH ROW
            FOLLOWS lab2.generate_uniq_group_id
DECLARE
    rowc NUMBER;
    e_not_unique_ident EXCEPTION;
    PRAGMA AUTONOMOUS_TRANSACTION;
    PRAGMA exception_init(e_not_unique_ident, -01422);
BEGIN 
    SELECT COUNT(*) INTO rowc FROM lab2."groups" WHERE "id" = :new."id";
    IF rowc <> 0  THEN
        RAISE e_not_unique_ident;
    END IF;
END;

CREATE OR REPLACE TRIGGER lab2.generate_uniq_group_id   --wrk
    BEFORE INSERT ON lab2."groups"
        FOR EACH ROW
            FOLLOWS lab2.chk_unique_groupname
BEGIN 
    SELECT lab2.lab2_group.nextval INTO :new."id" FROM dual;
END;

CREATE OR REPLACE TRIGGER lab2.generate_uniq_student_id     --wrk
    BEFORE INSERT ON lab2."students"
        FOR EACH ROW
BEGIN 
    SELECT lab2.lab2_student.nextval INTO :new."id" FROM dual;
END;

------------------------------------------------------------------------------
--3. Foreign Key
CREATE OR REPLACE TRIGGER lab2.cascade_del      --wrk
    BEFORE DELETE ON lab2."groups"
        FOR EACH ROW
DECLARE
    PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
    DELETE FROM lab2."students" WHERE GROUP_ID = :old."id";
    COMMIT;
END;

------------------------------------------------------------------------------
--4. Журналирование
CREATE TABLE lab2."logs"
(
    time_mark TIMESTAMP NOT NULL, 
    statemant VARCHAR2(100) NOT NULL,
    new_id NUMBER,
    old_id NUMBER,
    "name" VARCHAR2(100),
    "group" NUMBER
);

CREATE OR REPLACE TRIGGER log_trig                      --wrk
    AFTER INSERT OR DELETE OR UPDATE ON lab2."students"
        FOR EACH ROW
BEGIN
    IF INSERTING THEN
        INSERT INTO lab2."logs" VALUES(TO_TIMESTAMP(TO_CHAR(SYSDATE,'yyyy-mm-dd hh:mi:ss'), 'yyyy-mm-dd hh:mi:ss'), 'INSERT',:new."id",null,:new."name",:new.group_id);
    ELSIF UPDATING THEN
        INSERT INTO lab2."logs" VALUES(TO_TIMESTAMP(TO_CHAR(SYSDATE,'yyyy-mm-dd hh:mi:ss'), 'yyyy-mm-dd hh:mi:ss'),'UPDATE',:new."id",:old."id",:old."name",:old.group_id);
    ELSIF DELETING THEN
        INSERT INTO lab2."logs" VALUES(TO_TIMESTAMP(TO_CHAR(SYSDATE,'yyyy-mm-dd hh:mi:ss'), 'yyyy-mm-dd hh:mi:ss'),'DELETE',null,:old."id",:old."name",:old.group_id);
    END IF;
END;

------------------------------------------------------------------------------
--5. Восстановления информации
CREATE OR REPLACE PROCEDURE restore_data(start_time IN CHAR) -- на момент
IS 
    CURSOR get_logs IS 
        SELECT * FROM lab2."logs" WHERE time_mark>=TO_TIMESTAMP(start_time, 'yyyy-mm-dd hh:mi:ss') ORDER BY time_mark DESC;
BEGIN
    FOR getting_log IN get_logs LOOP
        IF getting_log.statemant='INSERT' THEN
            DELETE FROM lab2."students" WHERE "id"=getting_log.new_id;
        ELSIF getting_log.statemant='UPDATE' THEN
            UPDATE lab2."students" SET "id"=getting_log.old_id, "name"=getting_log."name", group_id=getting_log."group" WHERE "id"=getting_log.new_id;
        ELSIF getting_log.statemant='DELETE' THEN
            INSERT INTO lab2."students" VALUES(getting_log.old_id, getting_log."name", getting_log."group");
        END IF;
        DELETE FROM lab2."logs" WHERE time_mark=getting_log.time_mark;
    END LOOP;
    commit;
END restore_data;

CREATE OR REPLACE PROCEDURE restore_data_by_interval(start_time IN CHAR, end_time IN CHAR)  -- на интервал
IS 
    CURSOR get_logs IS 
        SELECT * FROM lab2."logs" WHERE time_mark>=TO_TIMESTAMP(start_time, 'yyyy-mm-dd hh:mi:ss') AND time_mark<=TO_TIMESTAMP(end_time, 'yyyy-mm-dd hh:mi:ss') ORDER BY time_mark DESC;
BEGIN
    FOR getting_log IN get_logs LOOP
        IF getting_log.statemant='INSERT' THEN
            DELETE FROM lab2."students" WHERE "id"=getting_log.new_id;
        ELSIF getting_log.statemant='UPDATE' THEN
            UPDATE lab2."students" SET "id"=getting_log.old_id, "name"=getting_log."name", group_id=getting_log."group" WHERE "id"=getting_log.new_id;
        ELSIF getting_log.statemant='DELETE' THEN
            INSERT INTO lab2."students" VALUES(getting_log.old_id, getting_log."name", getting_log."group");
        END IF;
        DELETE FROM lab2."logs" WHERE time_mark=getting_log.time_mark;
    END LOOP;
    commit;
END restore_data_by_interval;

------------------------------------------------------------------------------
--6. Триггер на синхронизацию
CREATE OR REPLACE TRIGGER LAB2.sync 
    AFTER INSERT OR DELETE OR UPDATE ON LAB2."students"
        FOR EACH ROW
BEGIN
    IF inserting THEN
        UPDATE LAB2."groups" SET c_val=c_val+1 WHERE "id" = :NEW.group_id;
    ELSIF updating THEN
        UPDATE LAB2."groups" SET c_val=c_val+1 WHERE "id" = :NEW.group_id;
        UPDATE LAB2."groups" SET c_val=c_val-1 WHERE "id" = :OLD.group_id;
    ELSIF deleting THEN
        UPDATE LAB2."groups" SET c_val=c_val-1 WHERE "id" = :OLD.group_id;
    END IF;
END;