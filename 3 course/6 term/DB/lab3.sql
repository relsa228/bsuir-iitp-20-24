------------------------------------------------------------------------------
--Тестовые таблицы
create table LAB3_DEV."groups"
(
    "id" number primary key,
    "name"  varchar2(30) not null,
    c_val number not null
);

create table LAB3_PROD."groups"
(
    "id" number primary key,
    "name"  varchar2(30) not null,
    c_val number not null
);

create table LAB3_DEV."students"
(
    "id" number primary key,
    "name"  varchar2(30) not null,
    group_id number not null
);

DROP TABLE LAB3_DEV."products";
CREATE TABLE LAB3_DEV."products" ( 
    constraint dd_pk PRIMARY KEY (product_id)
    product_id numeric(10) not null,
    supplier_id numeric(10) not null,
    CONSTRAINT fk_supplier
    FOREIGN KEY (supplier_id)
    REFERENCES  LAB3_DEV."supplier"(supplier_id)
);

DROP TABLE LAB3_DEV."supplier";
CREATE TABLE LAB3_DEV."supplier"
( 
    product_id numeric(10) not null,
    supplier_id numeric(10) not null,
  supplier_name varchar2(50) not null,
  contact_name varchar2(50),
  CONSTRAINT supplier_pk PRIMARY KEY (supplier_id)
  CONSTRAINT fk_dd FOREIGN KEY (product_id)
    REFERENCES  LAB3_DEV."supplier"(product_id)
);


------------------------------------------------------------------------------
--0. Создание юзеров для лабы
ALTER SESSION SET "_oracle_script"=TRUE;
DROP USER LAB3_DEV CASCADE;

ALTER SESSION SET "_oracle_script"=TRUE;
DROP USER LAB3_PROD CASCADE;

ALTER SESSION SET "_oracle_script"=TRUE;
CREATE USER LAB3_DEV;
ALTER USER LAB3_DEV QUOTA UNLIMITED ON USERS;

ALTER SESSION SET "_oracle_script"=TRUE;
CREATE USER LAB3_PROD;
ALTER USER LAB3_PROD QUOTA UNLIMITED ON USERS;

GRANT CONNECT, RESOURCE TO LAB3_DEV;
GRANT CONNECT, RESOURCE TO LAB3_PROD;

------------------------------------------------------------------------------
--1. Сравнение таблиц

create or replace procedure COMPARE_SCHEMES(dev_schema in varchar2, prod_schema in varchar2) as
    ref_table varchar2(225);
    ref_constrain varchar2(225);

    tab_count NUMBER;
    clmn_count NUMBER;
    dist_tab_count NUMBER;
    ref_table_count NUMBER;

    input_flag BOOLEAN := TRUE;
    loop_flag BOOLEAN := FALSE;

    funct_count NUMBER;
    f1_arg_count NUMBER;
    f2_arg_count NUMBER;
    arg_count NUMBER;

    ddl_out varchar2(225);
    funct_ending varchar2(225);
BEGIN
--Модуль обхода dev таблиц и поиска отличий
    for tab in (select * from ALL_TABLES WHERE OWNER=dev_schema) loop
        SELECT COUNT(*) INTO tab_count FROM ALL_TABLES WHERE OWNER=prod_schema AND TABLE_NAME=tab.TABLE_NAME;
        IF tab_count=1 THEN
            for clmn in (SELECT * FROM ALL_TAB_COLUMNS WHERE table_name=tab.TABLE_NAME AND OWNER=dev_schema) loop 
                SELECT COUNT(*) INTO clmn_count FROM ALL_TAB_COLUMNS WHERE  OWNER=prod_schema AND 
                                                                            COLUMN_NAME=clmn.COLUMN_NAME AND
                                                                            DATA_TYPE=clmn.DATA_TYPE AND 
                                                                            DATA_LENGTH=clmn.DATA_LENGTH;
                IF clmn_count=0 THEN
                    INSERT INTO DIST_TABLES VALUES (tab.TABLE_NAME);
                END IF;
                EXIT WHEN clmn_count=0;
            END LOOP;
        ELSE
            INSERT INTO DIST_TABLES VALUES (tab.TABLE_NAME);
        END IF;
    END LOOP;

--Модуль проверки форен кея
    SELECT COUNT(*) INTO dist_tab_count FROM DIST_TABLES;
    WHILE dist_tab_count <> 0 LOOP
        for tab in (SELECT * FROM DIST_TABLES) LOOP
            for f_key in (select src_cc.table_name as src_table from all_constraints c inner join all_cons_columns dest_cc on
                            c.r_constraint_name=dest_cc.constraint_name and c.r_owner=dest_cc.owner inner join all_cons_columns src_cc on
                                c.constraint_name=src_cc.constraint_name and c.owner=src_cc.owner where c.constraint_type='R'
                                    and dest_cc.owner=dev_schema AND dest_cc.table_name=tab."t_name") loop
                
                SELECT COUNT(*) into ref_table_count FROM OUT_TABLES WHERE "t_name"=f_key.SRC_TABLE;
                
                for lp in (select dest_cc.table_name as dest_table from all_constraints c inner join all_cons_columns dest_cc on
                            c.r_constraint_name=dest_cc.constraint_name and c.r_owner=dest_cc.owner inner join all_cons_columns src_cc on
                                c.constraint_name=src_cc.constraint_name and c.owner=src_cc.owner where c.constraint_type='R'
                                    and dest_cc.owner=dev_schema AND src_cc.table_name=tab."t_name") loop
                    
                    if lp.dest_table=f_key.SRC_TABLE then
                        ddl_out := 'Looping ref ' || f_key.SRC_TABLE || ' ' || tab."t_name";
                        dbms_output.put_line(ddl_out);
                        loop_flag := TRUE;
                    end if;
                end loop;

                IF ref_table_count=0 AND not loop_flag then
                    input_flag:=FALSE;
                END IF;
            end loop;

            IF input_flag THEN
                DELETE FROM DIST_TABLES WHERE "t_name"=tab."t_name";
                INSERT INTO OUT_TABLES VALUES (tab."t_name");
            END IF;
            input_flag:=TRUE;
            loop_flag := FALSE;
            SELECT COUNT(*) INTO dist_tab_count FROM DIST_TABLES;
        END LOOP;
    END LOOP;

    dbms_output.put_line('--------TABLES--------');
    for tab in (SELECT * FROM OUT_TABLES) LOOP
        dbms_output.put_line(tab."t_name"); 
        ddl_out := 'CREATE TABLE ' || prod_schema || '.' || '"' || tab."t_name" || '"' || ' (';
        dbms_output.put_line(ddl_out);
        for colmn in (SELECT * FROM ALL_TAB_COLUMNS WHERE table_name=tab."t_name" AND OWNER=dev_schema) loop
            ddl_out := '"' || colmn.COLUMN_NAME || '" ' || colmn.DATA_TYPE || '(' || colmn.DATA_LENGTH || ')';
            if colmn.DATA_DEFAULT is not NULL THEN
                ddl_out := ddl_out || ' default ' || colmn.DATA_DEFAULT;
            end if; 
            if colmn.NULLABLE='N' THEN
                ddl_out := ddl_out || ' not null ';
            end if;
            dbms_output.put_line(ddl_out);
        end loop; 
        for cnstrnt in (SELECT * FROM ALL_CONSTRAINTS WHERE OWNER=dev_schema AND table_name=tab."t_name" AND CONSTRAINT_TYPE='P' AND GENERATED='USER NAME') loop
            for c_name in (SELECT cols.column_name FROM all_constraints cons, all_cons_columns cols WHERE cols.table_name = tab."t_name" AND cons.constraint_type = 'P'
                            AND cons.constraint_name = cols.constraint_name AND cons.owner = cols.owner ORDER BY cols.table_name, cols.position) LOOP
                ddl_out := 'CONSTRAINT ' || cnstrnt.CONSTRAINT_NAME || ' PRIMARY KEY (' || c_name.COLUMN_NAME || ')';
            end loop;
            dbms_output.put_line(ddl_out);
        end loop;
        for cnstrnt in (select src_cc.owner as src_owner, src_cc.table_name as src_table, src_cc.column_name as src_column,
                            dest_cc.owner as dest_owner, dest_cc.table_name as dest_table, dest_cc.column_name as dest_column, c.constraint_name
                                from all_constraints c inner join all_cons_columns dest_cc on c.r_constraint_name = dest_cc.constraint_name
                                    and c.r_owner = dest_cc.owner inner join all_cons_columns src_cc on c.constraint_name = src_cc.constraint_name
                                        and c.owner = src_cc.owner where c.constraint_type = 'R' and dest_cc.owner = dev_schema
                                            and dest_cc.table_name = tab."t_name") loop
            for ref_name in (SELECT * FROM all_cons_columns a JOIN all_constraints c ON a.owner = c.owner AND a.constraint_name = c.constraint_name
                                JOIN all_constraints c_pk ON c.r_owner = c_pk.owner AND c.r_constraint_name = c_pk.constraint_name
                                    WHERE c.constraint_type = 'R' AND a.table_name = tab."t_name") loop
            ddl_out := 'CONSTRAINT ' || ref_name.CONSTRAINT_NAME || ' FOREIGN KEY (' || ref_name.COLUMN_NAME || ') REFERENCES  ' || dev_schema || '."' || ref_name.table_name || '"' || '(' || ref_name.COLUMN_NAME || ');';
            end loop;
            dbms_output.put_line(ddl_out);
        end loop;
        dbms_output.put_line(')');
    END LOOP;

--Модуль проверки функций (выводит)
    dbms_output.put_line('----FUNCTIONS----');
    for funct in (select * from all_objects WHERE object_type='FUNCTION' AND owner=dev_schema) loop
        select COUNT(*) into funct_count from all_objects where owner=prod_schema and object_type='FUNCTION' and object_name=funct.object_name;
        if funct_count=0 THEN
            dbms_output.put_line(funct.object_name);
            ddl_out := 'CREATE OR REPLACE FUNCTION ' || prod_schema || '.' || funct.object_name || ' (';
            dbms_output.put_line(ddl_out);
            for proc_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=funct.object_name AND POSITION<>0 AND PACKAGE_NAME IS NULL) loop
                ddl_out := proc_out.DATA_TYPE || ' ' || proc_out.ARGUMENT_NAME;
                dbms_output.put_line(ddl_out);
            end loop;
            dbms_output.put_line(')');
            SELECT DATA_TYPE into funct_ending from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=funct.object_name AND POSITION=0;
            funct_ending := 'return ' || funct_ending;
            dbms_output.put_line(funct_ending);
        ELSE
            SELECT count(*) into f1_arg_count from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=funct.object_name;
            SELECT count(*) into f2_arg_count from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=funct.object_name;
            if f1_arg_count <> f2_arg_count then
                dbms_output.put_line(funct.object_name);
                ddl_out := 'CREATE OR REPLACE FUNCTION ' || prod_schema || '.' || funct.object_name || ' (';
                dbms_output.put_line(ddl_out);
                for proc_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=funct.object_name AND POSITION<>0 AND PACKAGE_NAME IS NULL) loop
                    ddl_out := proc_out.DATA_TYPE || ' ' || proc_out.ARGUMENT_NAME;
                    dbms_output.put_line(ddl_out);
                end loop;
                dbms_output.put_line(')');
                SELECT DATA_TYPE into funct_ending from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=funct.object_name AND POSITION=0;
                funct_ending := 'return ' || funct_ending;
                dbms_output.put_line(funct_ending);
            else
                for arg in (select * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=funct.object_name) loop
                    if arg.position=0 THEN
                        SELECT count(*) into arg_count from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=funct.object_name and DATA_TYPE=arg.DATA_TYPE and POSITION=0;
                        if arg_count=0 THEN
                            dbms_output.put_line(funct.object_name);
                            ddl_out := 'CREATE OR REPLACE FUNCTION ' || prod_schema || '.' || funct.object_name || ' (';
                            dbms_output.put_line(ddl_out);
                            for proc_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=funct.object_name AND POSITION<>0 AND PACKAGE_NAME IS NULL) loop
                                ddl_out := proc_out.DATA_TYPE || ' ' || proc_out.ARGUMENT_NAME;
                                dbms_output.put_line(ddl_out);
                            end loop;
                            dbms_output.put_line(')');
                            SELECT DATA_TYPE into funct_ending from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=funct.object_name AND POSITION=0;
                            funct_ending := 'return ' || funct_ending;
                            dbms_output.put_line(funct_ending);
                        end if;
                    else
                        SELECT count(*) into arg_count from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=funct.object_name and DATA_TYPE=arg.DATA_TYPE;
                        if arg_count=0 THEN
                            dbms_output.put_line(funct.object_name);
                            ddl_out := 'CREATE OR REPLACE FUNCTION ' || prod_schema || '.' || funct.object_name || ' (';
                            dbms_output.put_line(ddl_out);
                            for proc_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=funct.object_name AND POSITION<>0 AND PACKAGE_NAME IS NULL) loop
                                ddl_out := proc_out.DATA_TYPE || ' ' || proc_out.ARGUMENT_NAME;
                                dbms_output.put_line(ddl_out);
                            end loop;
                            dbms_output.put_line(')');
                            SELECT DATA_TYPE into funct_ending from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=funct.object_name AND POSITION=0;
                            funct_ending := 'return ' || funct_ending;
                            dbms_output.put_line(funct_ending);
                        end if;
                    end if;
                end loop;
            end if;
        end if;
    end loop;

--Модуль проверки процедур (выводит)
    dbms_output.put_line('----PROCEDURE----');
    for proc in (select * from all_objects WHERE object_type='PROCEDURE' AND owner=dev_schema) loop
        select COUNT(*) into funct_count from all_objects where owner=prod_schema and object_type='PROCEDURE' and object_name=proc.object_name;
        if funct_count=0 THEN
            dbms_output.put_line(proc.object_name);
            ddl_out := 'CREATE OR REPLACE PROCEDURE ' || prod_schema || '.' || proc.object_name || ' (';
            dbms_output.put_line(ddl_out);
            for proc_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc.object_name) loop
                ddl_out := proc_out.ARGUMENT_NAME || ' in ' || proc_out.DATA_TYPE;
                dbms_output.put_line(ddl_out);
            end loop;
            dbms_output.put_line(')');
        ELSE
            SELECT count(*) into f1_arg_count from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc.object_name;
            SELECT count(*) into f2_arg_count from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=proc.object_name;
            
            if f1_arg_count <> f2_arg_count then
                dbms_output.put_line(proc.object_name);
                ddl_out := 'CREATE OR REPLACE PROCEDURE ' || prod_schema || ' . ' || proc.object_name || ' (';
                dbms_output.put_line(ddl_out);
                for proc_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc.object_name) loop
                    ddl_out := proc_out.ARGUMENT_NAME || ' in ' || proc_out.DATA_TYPE;
                    dbms_output.put_line(ddl_out);
                end loop;
                dbms_output.put_line(')');
            else
                for arg in (select * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc.object_name) loop
                    SELECT count(*) into arg_count from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=proc.object_name and DATA_TYPE=arg.DATA_TYPE;
                    if arg_count=0 THEN
                        dbms_output.put_line(proc.object_name);
                        ddl_out := 'CREATE OR REPLACE PROCEDURE ' || prod_schema || '.' || proc.object_name || ' (';
                        dbms_output.put_line(ddl_out);
                        for proc_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc.object_name) loop
                            ddl_out := proc_out.ARGUMENT_NAME || ' in ' || proc_out.DATA_TYPE;
                            dbms_output.put_line(ddl_out);
                        end loop;
                        dbms_output.put_line(')');
                    end if;
                end loop;
            end if;
        end if;
    end loop;

--Модуль проверки пакетов (выводит)
    dbms_output.put_line('----Packages----');
    for pkg in (select * from all_objects WHERE object_type='PACKAGE' AND owner=dev_schema) loop
        select COUNT(*) into funct_count from all_objects where owner=prod_schema and object_type='PACKAGE' and object_name=pkg.OBJECT_NAME;
        if funct_count=0 THEN
            dbms_output.put_line(pkg.object_name);
            ddl_out := 'CREATE or replace PACKAGE ' || prod_schema || '.' || pkg.object_name || ' AS';
            dbms_output.put_line(ddl_out);
            for proc_out in (select * from all_procedures where owner=dev_schema and object_name=pkg.object_name AND PROCEDURE_NAME is not NULL) loop
                ddl_out := 'PROCEDURE ' || proc_out.PROCEDURE_NAME || '(';
                dbms_output.put_line(ddl_out);
                for arg_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc_out.PROCEDURE_NAME AND PACKAGE_NAME=pkg.object_name) loop
                    ddl_out := arg_out.ARGUMENT_NAME || ' in ' || arg_out.DATA_TYPE;
                    dbms_output.put_line(ddl_out);
                end loop;
                dbms_output.put_line(')');
            end loop;
            ddl_out := 'END ' || pkg.object_name || ';';
            dbms_output.put_line(ddl_out);
        ELSE
            SELECT count(*) into f1_arg_count from all_procedures where owner=dev_schema AND OBJECT_NAME=pkg.OBJECT_NAME;
            SELECT count(*) into f2_arg_count from all_procedures where owner=prod_schema AND OBJECT_NAME=pkg.OBJECT_NAME;
            
            if f1_arg_count <> f2_arg_count then
                dbms_output.put_line(pkg.object_name);
                ddl_out := 'CREATE or replace PACKAGE ' || prod_schema || '.' || pkg.object_name || ' AS';
                dbms_output.put_line(ddl_out);
                for proc_out in (select * from all_procedures where owner=dev_schema and object_name=pkg.object_name AND PROCEDURE_NAME is not NULL) loop
                    ddl_out := 'PROCEDURE ' || proc_out.PROCEDURE_NAME || '(';
                    dbms_output.put_line(ddl_out);
                    for arg_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc_out.object_name AND PACKAGE_NAME=pkg.object_name) loop
                        ddl_out := arg_out.ARGUMENT_NAME || ' in ' || arg_out.DATA_TYPE;
                        dbms_output.put_line(ddl_out);
                    end loop;
                    dbms_output.put_line(')');
                end loop;
                ddl_out := 'END ' || pkg.object_name || ';';
                dbms_output.put_line(ddl_out);
            else
                for proc_pkg in (select * from all_procedures where owner=dev_schema and object_name=pkg.object_name) loop
                    if proc_pkg.SUBPROGRAM_ID<>0 then
                        select COUNT(*) into funct_count from all_procedures where owner=prod_schema and object_name=pkg.object_name and PROCEDURE_NAME=proc_pkg.PROCEDURE_NAME;
                        if funct_count=0 THEN
                            dbms_output.put_line(pkg.object_name);
                            ddl_out := 'CREATE or replace PACKAGE ' || prod_schema || '.' || pkg.object_name || ' AS';
                            dbms_output.put_line(ddl_out);
                            for proc_out in (select * from all_procedures where owner=dev_schema and object_name=pkg.object_name AND PROCEDURE_NAME is not NULL) loop
                                ddl_out := 'PROCEDURE ' || proc_out.PROCEDURE_NAME || '(';
                                dbms_output.put_line(ddl_out);
                                for arg_out in (SELECT * from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc_out.object_name AND PACKAGE_NAME=pkg.object_name) loop
                                    ddl_out := arg_out.ARGUMENT_NAME || ' in ' || arg_out.DATA_TYPE;
                                    dbms_output.put_line(ddl_out);
                                end loop;
                                dbms_output.put_line(')');
                            end loop;
                            ddl_out := 'END ' || pkg.object_name || ';';
                            dbms_output.put_line(ddl_out);
                        end if;
                    end if;
                end loop;
            end if;
        end if;
    end loop;


    dbms_output.put_line('Superfluous objects:');
--Модуль поиска таблиц на удление
    for tab in (select * from ALL_TABLES WHERE OWNER=prod_schema) loop
        SELECT COUNT(*) INTO tab_count FROM ALL_TABLES WHERE OWNER=dev_schema AND TABLE_NAME=tab.TABLE_NAME;
        IF tab_count=1 THEN
            for clmn in (SELECT * FROM ALL_TAB_COLUMNS WHERE table_name=tab.TABLE_NAME AND OWNER=prod_schema) loop 
                SELECT COUNT(*) INTO clmn_count FROM ALL_TAB_COLUMNS WHERE  OWNER=dev_schema AND 
                                                                            COLUMN_NAME=clmn.COLUMN_NAME AND
                                                                            DATA_TYPE=clmn.DATA_TYPE AND 
                                                                            DATA_LENGTH=clmn.DATA_LENGTH;
                IF clmn_count=0 THEN
                    ddl_out := 'DROP TABLE ' || tab.TABLE_NAME;
                    dbms_output.put_line(ddl_out);
                END IF;
                EXIT WHEN clmn_count=0;
            END LOOP;
        ELSE
            ddl_out := 'DROP TABLE ' || tab.TABLE_NAME;
            dbms_output.put_line(ddl_out);
        END IF;
    END LOOP;

--Модуль поиска функций на удаление
    dbms_output.put_line('----FUNCTIONS----');
    for funct in (select * from all_objects WHERE object_type='FUNCTION' AND owner=prod_schema) loop
        select COUNT(*) into funct_count from all_objects where owner=dev_schema and object_type='FUNCTION' and object_name=funct.object_name;
        if funct_count=0 THEN
            ddl_out := 'DROP FUNCTION ' || funct.object_name;
            dbms_output.put_line(ddl_out);
        ELSE
            SELECT count(*) into f1_arg_count from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=funct.object_name;
            SELECT count(*) into f2_arg_count from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=funct.object_name;
            if f1_arg_count <> f2_arg_count then
                ddl_out := 'DROP FUNCTION ' || funct.object_name;
                dbms_output.put_line(ddl_out);
            else
                for arg in (select * from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=funct.object_name) loop
                    if arg.position=0 THEN
                        SELECT count(*) into arg_count from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=funct.object_name and DATA_TYPE=arg.DATA_TYPE and POSITION=0;
                        if arg_count=0 THEN
                            ddl_out := 'DROP FUNCTION ' || funct.object_name;
                            dbms_output.put_line(ddl_out);
                        end if;
                    else
                        SELECT count(*) into arg_count from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=funct.object_name and DATA_TYPE=arg.DATA_TYPE;
                        if arg_count=0 THEN
                            ddl_out := 'DROP FUNCTION ' || funct.object_name;
                            dbms_output.put_line(ddl_out);
                        end if;
                    end if;
                end loop;
            end if;
        end if;
    end loop;

--Модуль проверки процедур (выводит)
    dbms_output.put_line('----PROCEDURE----');
    for proc in (select * from all_objects WHERE object_type='PROCEDURE' AND owner=prod_schema) loop
        select COUNT(*) into funct_count from all_objects where owner=dev_schema and object_type='PROCEDURE' and object_name=proc.object_name;
        if funct_count=0 THEN
            ddl_out := 'DROP PROCEDURE ' || proc.object_name;
            dbms_output.put_line(ddl_out);
        ELSE
            SELECT count(*) into f1_arg_count from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=proc.object_name;
            SELECT count(*) into f2_arg_count from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc.object_name;
            
            if f1_arg_count <> f2_arg_count then
                ddl_out := 'DROP PROCEDURE ' || proc.object_name;
                dbms_output.put_line(ddl_out);
            else
                for arg in (select * from ALL_ARGUMENTS where owner=prod_schema AND OBJECT_NAME=proc.object_name) loop
                    SELECT count(*) into arg_count from ALL_ARGUMENTS where owner=dev_schema AND OBJECT_NAME=proc.object_name and DATA_TYPE=arg.DATA_TYPE;
                    if arg_count=0 THEN
                        ddl_out := 'DROP PROCEDURE ' || proc.object_name;
                        dbms_output.put_line(ddl_out);
                    end if;
                end loop;
            end if;
        end if;
    end loop;

--Модуль проверки пакетов (выводит)
    dbms_output.put_line('----Packages----');
    for pkg in (select * from all_objects WHERE object_type='PACKAGE' AND owner=prod_schema) loop
        select COUNT(*) into funct_count from all_objects where owner=dev_schema and object_type='PACKAGE' and object_name=pkg.OBJECT_NAME;
        if funct_count=0 THEN
            ddl_out := 'DROP PACKAGE ' || pkg.OBJECT_NAME;
            dbms_output.put_line(ddl_out);
        ELSE
            SELECT count(*) into f1_arg_count from all_procedures where owner=prod_schema AND OBJECT_NAME=pkg.OBJECT_NAME;
            SELECT count(*) into f2_arg_count from all_procedures where owner=dev_schema AND OBJECT_NAME=pkg.OBJECT_NAME;
            
            if f1_arg_count <> f2_arg_count then
                ddl_out := 'DROP PACKAGE ' || pkg.OBJECT_NAME;
                dbms_output.put_line(ddl_out);
            else
                for proc_pkg in (select * from all_procedures where owner=prod_schema and object_name=pkg.object_name) loop
                    if proc_pkg.SUBPROGRAM_ID<>0 then
                        select COUNT(*) into funct_count from all_procedures where owner=dev_schema and object_name=pkg.object_name and PROCEDURE_NAME=proc_pkg.PROCEDURE_NAME;
                        if funct_count=0 THEN
                            ddl_out := 'DROP PACKAGE ' || pkg.OBJECT_NAME;
                            dbms_output.put_line(ddl_out);
                        end if;
                    end if;
                end loop;
            end if;
        end if;
    end loop;
END COMPARE_SCHEMES;

DROP TABLE DIST_TABLES;
DROP TABLE OUT_TABLES;
create table DIST_TABLES ("t_name"  varchar2(128) not null);
create table OUT_TABLES ("t_name"  varchar2(128) not null);
call COMPARE_SCHEMES('LAB3_DEV', 'LAB3_PROD');





drop table LAB3_DEV."Room";
drop table  LAB3_DEV."RoomType" cascade;


CREATE TABLE LAB3_DEV."Room"(Room_ID int PRIMARY KEY, Price INT, Reservation_ID int,Gust_ID int );
--CREATE TABLE LAB3_DEV."Gust" ( Gust_ID INT PRIMARY KEY, First_Name VARCHAR(50), Last_Name VARCHAR(50), Email VARCHAR(20), phone_number INT, Address VARCHAR(30) );
--CREATE TABLE LAB3_DEV."Reservation" ( Reservation_ID INT PRIMARY KEY, Start_Date Date, End_Date Date );
CREATE TABLE LAB3_DEV."RoomType" ( RoomType_ID INT NOT NULL PRIMARY KEY, Class VARCHAR(10), ExtraPrice INT);

ALTER TABLE LAB3_DEV."Room" ADD FOREIGN KEY (price) REFERENCES LAB3_DEV."RoomType"(RoomType_ID);
ALTER TABLE LAB3_DEV."RoomType" ADD FOREIGN KEY (ExtraPrice) REFERENCES LAB3_DEV."Room"(Room_ID);


CREATE TABLE LAB3_DEV."tab1"(id int PRIMARY KEY, val INT);
CREATE TABLE LAB3_DEV."tab2"(id int PRIMARY KEY, val INT);
CREATE TABLE LAB3_DEV."tab3"(id int PRIMARY KEY, val INT);

drop table LAB3_DEV."tab1";
drop table LAB3_DEV."tab2";
drop table LAB3_DEV."tab3";

ALTER TABLE LAB3_DEV."tab2" ADD FOREIGN KEY (val) REFERENCES LAB3_DEV."tab1"(id);
ALTER TABLE LAB3_DEV."tab1" ADD FOREIGN KEY (val) REFERENCES LAB3_DEV."tab3"(id);

2->1
1->3

















--НЕ ПРОЦЕДУРА
call funct('LAB3_DEV', 'LAB3_PROD');
SELECT "t_name" FROM DIST_TABLES
SELECT * FROM ALL_TAB_COLUMNS WHERE OWNER='LAB3_DEV';
SELECT * FROM ALL_TAB_COLUMNS WHERE table_name='ALL_CONSTRAINTS';

select *
from   all_objects
where  owner = 'LAB3_DEV'
and    object_type = 'PROCEDURE';

select * from ALL_ARGUMENTS where owner='LAB3_DEV' and OBJECT_NAME='HELLO_SECOND';

create or replace function LAB3_dev.hello
return number

is
    parity_counter number;
    odd_counter number;
begin
    dbms_output.put_line('Hello'); 
    return 1;
end;

create or replace function LAB3_PROD.hello_second(salary in number, percent in VARCHAR2)
return BOOLEAN
is
    parity_counter number;
    odd_counter number;
begin
    dbms_output.put_line('Hello'); 
    return true;
end;

create or replace function LAB3_DEV.hello_second(salary in number, percent in VARCHAR2)
return number
is
    parity_counter number;
    odd_counter number;
begin
    dbms_output.put_line('Hello'); 
    return 1;
end;

CREATE OR REPLACE PROCEDURE LAB3_prod.hello_proc(start_time IN VARCHAR2, end_time IN number)
IS
   cnumber number;
BEGIN
    dbms_output.put_line('Hello'); 
END hello_proc;

drop procedure LAB3_prod.hello_proc;
drop procedure LAB3_dev.hello_proc;

drop function LAB3_dev.hello_second;
drop function LAB3_dev.hello;

drop function LAB3_prod.hello_second;
drop function LAB3_prod.hello;

CREATE or replace PACKAGE LAB3_PROD.TESTPKG AS 
   PROCEDURE hello_second(salary in number, percent in VARCHAR2);
END TESTPKG;


drop PACKAGE LAB3_PROD.TESTPKG;

select * from all_objects WHERE object_name='HELLO_SECOND' AND owner='LAB3_DEV';
select * from all_procedures where owner='LAB3_DEV' and object_name='TESTPKG';
SELECT * FROM ALL_TAB_COLUMNS WHERE table_name='supplier' AND OWNER='LAB3_DEV';

select table_name, constraint_name, status, owner
from all_constraints
where r_owner = 'supplier'
and constraint_type = 'R'
and r_constraint_name in
 (
   select constraint_name from all_constraints
   where constraint_type in ('P', 'U')
   and table_name = 'products'
   and owner = 'LAB3_DEV'
 )
order by table_name, constraint_name

SELECT *
  FROM all_cons_columns a
  JOIN all_constraints c ON a.owner = c.owner
                        AND a.constraint_name = c.constraint_name
  JOIN all_constraints c_pk ON c.r_owner = c_pk.owner
                           AND c.r_constraint_name = c_pk.constraint_name
 WHERE c.constraint_type = 'R'
   AND a.table_name = 'products'
--НЕ ПРОЦЕДУРА

select
  src_cc.owner as src_owner,
  src_cc.table_name as src_table,
  src_cc.column_name as src_column,
  dest_cc.owner as dest_owner,
  dest_cc.table_name as dest_table,
  dest_cc.column_name as dest_column,
  c.constraint_name
from
  all_constraints c
inner join all_cons_columns dest_cc on
  c.r_constraint_name = dest_cc.constraint_name
  and c.r_owner = dest_cc.owner
inner join all_cons_columns src_cc on
  c.constraint_name = src_cc.constraint_name
  and c.owner = src_cc.owner
where
  c.constraint_type = 'R'
  and dest_cc.owner = 'LAB3_DEV'
  and dest_cc.table_name = 'tab3'
  --and dest_cc.column_name = 'MY_OPTIONNAL_TARGET_COLUMN'
;