------------------------------------------------------------------------------
--0. Создание юзеров для лабы
ALTER SESSION SET "_oracle_script"=TRUE;
CREATE USER LAB4;
ALTER USER LAB4 QUOTA UNLIMITED ON USERS;

GRANT CONNECT, RESOURCE TO LAB4;


------------------------------------------------------------------------------
--1. Функция для выборки
CREATE OR REPLACE Function LAB4.XMLSelect
   (xml_expression IN varchar2)
   RETURN VARCHAR2
IS
    l_cursor_id INTEGER;
    out_select VARCHAR2(7000);
BEGIN
    out_select := 'SELECT';
    for out_column in (select extractValue(value(t),'column') column_name
                            from table(XMLSequence(XMLType(xml_expression).extract('SELECT/columns/column'))) t) LOOP
        out_select := out_select || ' ' || out_column."COLUMN_NAME" || ','; 
    end loop;

    out_select := SUBSTR(out_select, 1, LENGTH(out_select) - 1);

    for src_tab in (select extractValue(value(t),'tab') src_tab
                        from table(XMLSequence(XMLType(xml_expression).extract('SELECT/from/tab'))) t) LOOP
        out_select := out_select || ' FROM ' || src_tab."SRC_TAB"; 
    end loop;

    for join_unit in (select extractValue(value(t),'join/type') join_type, 
                        extractValue(value(t),'join/tab') join_tab,
                            extractValue(value(t),'join/condition') join_condition
                                    from (table(XMLSequence(XMLType(xml_expression).extract('SELECT/joins/join'))) t)) loop
        out_select := out_select || CHR(10) || CHR(9) || join_unit."JOIN_TYPE" || ' ' || join_unit."JOIN_TAB" || ' on ' || join_unit."JOIN_CONDITION";
    end loop;

    out_select := out_select || CHR(10) || CHR(9) || CHR(9) || ' WHERE ';
    for out_condition in (select extractValue(value(t),'condition') CONDITION
                            from table(XMLSequence(XMLType(xml_expression).extract('SELECT/where/condition'))) t) LOOP
        out_select := out_select || out_condition."CONDITION" || ' ' ;
    end loop;

    for out_condition in (select extractValue(value(t),'nesting/column') S_COLUMN,
                            extractValue(value(t),'nesting/nesting_type') N_TYPE,
                                extract(value(t),'nesting/SELECT') select_seq
                                from table(XMLSequence(XMLType(xml_expression).extract('SELECT/where/nesting'))) t) LOOP
        out_select := out_select || CHR(10) || CHR(9) || CHR(9) || out_condition.S_COLUMN || ' ' || out_condition.N_TYPE || ' (' ||  LAB4.XMLSelect(out_condition."SELECT_SEQ".getClobVal()) || ')';
    end loop;
    RETURN out_select;
END;

CREATE OR REPLACE Function LAB4.XMLSelectInit
   (xml_expression IN varchar2)
   RETURN sys_refcursor
IS
    cur  sys_refcursor;
    out_select varchar(7000);
BEGIN
    out_select := LAB4.XMLSELECT(xml_expression);
    OPEN cur;
    dbms_output.put_line(out_select || CHR(10));
    return cur;
end;

------------------------------------------------------------------------------
--2.1 Функция для создания таблицы - wrk
CREATE OR REPLACE Function LAB4.XMLCreate
   (xml_expression IN varchar2)
   RETURN VARCHAR2
IS
    out_create VARCHAR2(7000);
    seq_create VARCHAR2(7000);
    trigger_create VARCHAR2(7000);

    table_name VARCHAR2(7000);
    primary_name VARCHAR2(7000);
    username VARCHAR2(7000);
BEGIN
    out_create := 'CREATE TABLE ';
    select extractValue(value(t),'name') column_name into table_name
        from table(XMLSequence(XMLType(xml_expression).extract('create/name'))) t;
    select extractValue(value(t),'user') column_name into username
        from table(XMLSequence(XMLType(xml_expression).extract('create/user'))) t;
    
    if username IS NULL OR username = ''  THEN
        out_create := out_create || table_name || ' (' || CHR(10);
    else
        out_create := out_create || username || '."' || table_name || '"' || ' (' || CHR(10);
    end if;
    for column_unit in (select extractValue(value(t),'column/column_name') column_name, 
                            extractValue(value(t),'column/datatype') datatype,
                                extractValue(value(t),'column/not_null') not_null,
                                    extractValue(value(t),'column/default') default_val
                                        from (table(XMLSequence(XMLType(xml_expression).extract('create/columns/column'))) t)) loop
        out_create := out_create || column_unit."COLUMN_NAME" || ' ' || column_unit."DATATYPE" || ' ';
        if column_unit."DEFAULT_VAL" IS NOT NULL OR column_unit."DEFAULT_VAL" <> '' THEN
            out_create := out_create || 'DEFAULT ' || column_unit."DEFAULT_VAL";
        end if;
        if column_unit."NOT_NULL" = 'true' THEN
            out_create := out_create || ' NOT NULL,' || CHR(10);
        else
            out_create := out_create || ',' || CHR(10);
        end if;
    end loop;
    for primary_unit in (select extractValue(value(t),'primary_key/column_name') column_name, 
                            extractValue(value(t),'primary_key/constraint_name') constraint_name
                                from (table(XMLSequence(XMLType(xml_expression).extract('create/constraints/primary_key'))) t)) loop
        out_create := out_create || ' CONSTRAINT ' || primary_unit."CONSTRAINT_NAME" || ' PRIMARY KEY (' || primary_unit."COLUMN_NAME" || ')' || CHR(10);
    end loop;
    for foreing_unit in (select extractValue(value(t),'foreing_key/column_name') column_name, 
                            extractValue(value(t),'foreing_key/constraint_name') constraint_name,
                                extractValue(value(t),'foreing_key/reference_table') reference_table,
                                    extractValue(value(t),'foreing_key/reference_column') reference_column
                                        from (table(XMLSequence(XMLType(xml_expression).extract('create/constraints/foreing_key'))) t)) loop
        out_create := out_create || ' CONSTRAINT ' || foreing_unit."CONSTRAINT_NAME" || ' FOREIGN KEY (' || foreing_unit."COLUMN_NAME" || ') REFERENCES ' || foreing_unit."REFERENCE_TABLE" || '(' || foreing_unit."REFERENCE_COLUMN" || ')' || CHR(10);
    end loop;
    out_create := out_create || ');';

    select extractValue(value(t),'primary_key/column_name') column_name into primary_name
         from (table(XMLSequence(XMLType(xml_expression).extract('create/constraints/primary_key'))) t);
    if primary_name IS NULL OR primary_name = ''  THEN
        out_create := out_create || CHR(10) || CHR(10) || 'Primary key is not defined';
    else
        if username IS NOT NULL OR username <> ''  THEN
            seq_create := 'create sequence ' || username || '.' || table_name || '_id_seq' || CHR(10) ||
                'start with 1' || CHR(10) || 'increment by 1;' || CHR(10) || CHR(10);
            trigger_create := 'CREATE OR REPLACE TRIGGER ' || username || '.' || table_name || '_id_trigger' || CHR(10) 
                || 'BEFORE INSERT ON ' || username || '."' || table_name || '"' || CHR(10) || 'FOR EACH ROW' || CHR(10) ||
                'BEGIN' || CHR(10) || 'select ' || username || '.' || table_name || '_id_seq.nextval INTO :new."' || UPPER(primary_name) || 
                '" FROM dual;' || CHR(10) || 'END;';
        else
            seq_create := 'create sequence ' || table_name || '_id_seq' || CHR(10) ||
                'start with 1' || CHR(10) || 'increment by 1;' || CHR(10) || CHR(10);
            trigger_create := 'CREATE OR REPLACE TRIGGER ' || table_name || '_id_trigger' || CHR(10) 
                || 'BEFORE INSERT ON ' || table_name || CHR(10) || 'FOR EACH ROW' || CHR(10) ||
                'BEGIN' || CHR(10) || 'select ' || table_name || '_id_seq.nextval INTO :new."' || UPPER(primary_name) || 
                '" FROM dual;' || CHR(10) || 'END;';
        end if;
    end if;
    RETURN out_create || CHR(10) || CHR(10) || seq_create || CHR(10) || CHR(10) || trigger_create;
END;
------------------------------------------------------------------------------
--2.2 Функция для удаления таблиц - wrk
CREATE OR REPLACE Function LAB4.XMLDrop
   (xml_expression IN varchar2)
   RETURN VARCHAR2
IS
    out_drop VARCHAR2(7000);
    table_name VARCHAR2(7000);
BEGIN
    out_drop := '';
    for drop_unit in (select extractValue(value(t),'table_name') t_name
                                from (table(XMLSequence(XMLType(xml_expression).extract('drop/table_name'))) t)) loop
        out_drop := out_drop || CHR(10) || 'DROP TABLE ' || drop_unit."T_NAME" || ';';
    end loop;
    RETURN out_drop;
END;

------------------------------------------------------------------------------
--3. Функция для изменения таблицы - wrk
CREATE OR REPLACE Function LAB4.XMLModify
   (xml_expression IN varchar2)
   RETURN VARCHAR2
IS
    modify_type VARCHAR2(20);
    table_name VARCHAR2(7000);

    i_counter NUMBER := 0;
    j_counter NUMBER := 0;

    modify_out VARCHAR2(7000);
BEGIN
    select extractValue(value(t),'affect_table') column_name into table_name
            from table(XMLSequence(XMLType(xml_expression).extract('dml/affect_table'))) t;
    select extractValue(value(t),'dml_type') column_name into modify_type
            from table(XMLSequence(XMLType(xml_expression).extract('dml/dml_type'))) t;    

    case modify_type
        when 'INSERT' then
            modify_out := 'INSERT INTO ' || table_name || ' (';
            for insert_column in (select extractValue(value(t),'column') column_name
                                    from (table(XMLSequence(XMLType(xml_expression).extract('dml/affect_columns/column'))) t)) loop
                modify_out := modify_out || insert_column."COLUMN_NAME" || ', ';
            end loop;
            modify_out := SUBSTR(modify_out, 1, LENGTH(modify_out) - 1) || ') VALUES (';
            for insert_value in (select extractValue(value(t),'value') value_name
                                    from (table(XMLSequence(XMLType(xml_expression).extract('dml/new_values/value'))) t)) loop
                modify_out := modify_out || insert_value."VALUE_NAME" || ', ';
            end loop;
            modify_out := SUBSTR(modify_out, 1, LENGTH(modify_out) - 1) ||');';
        when 'UPDATE' then
            modify_out := 'UPDATE ' || table_name || ' SET ';
            for update_unit in (select extractValue(value(t),'column') affect_column
                                    from (table(XMLSequence(XMLType(xml_expression).extract('dml/affect_columns/column'))) t)) loop
                for update_val in (select extractValue(value(t),'value') n_value
                                        from (table(XMLSequence(XMLType(xml_expression).extract('dml/new_values/value'))) t)) loop
                    if i_counter = j_counter then
                        modify_out := modify_out || update_unit."AFFECT_COLUMN" || ' = ' || update_val."N_VALUE" || ', ';
                        j_counter := 0;
                        exit;
                    end if;
                    j_counter := j_counter + 1;
                end loop;
                i_counter := i_counter + 1;
            end loop;
            modify_out := SUBSTR(modify_out, 1, LENGTH(modify_out) - 2) || ' WHERE ';
            for upd_condition in (select extractValue(value(t),'condition') CONDITION
                            from table(XMLSequence(XMLType(xml_expression).extract('dml/where/condition'))) t) LOOP
                modify_out := modify_out || upd_condition."CONDITION" || ' ';
            end loop;
            for out_condition in (select extractValue(value(t),'nesting/column') S_COLUMN,
                            extractValue(value(t),'nesting/nesting_type') N_TYPE,
                                extract(value(t),'nesting/SELECT') select_seq
                                from table(XMLSequence(XMLType(xml_expression).extract('dml/where/nesting'))) t) LOOP
                modify_out := modify_out || CHR(10) || CHR(9) || CHR(9) || out_condition.S_COLUMN || ' ' || out_condition.N_TYPE || ' (' ||  LAB4.XMLSelect(out_condition."SELECT_SEQ".getClobVal()) || ')';
            end loop;
            modify_out := modify_out || ';';
        when 'DELETE' then
            modify_out := 'DELETE FROM ' || table_name || ' WHERE ';
            for del_condition in (select extractValue(value(t),'condition') CONDITION
                            from table(XMLSequence(XMLType(xml_expression).extract('dml/where/condition'))) t) LOOP
                modify_out := modify_out || del_condition."CONDITION" || ' ';
            end loop;
            for out_condition in (select extractValue(value(t),'nesting/column') S_COLUMN,
                            extractValue(value(t),'nesting/nesting_type') N_TYPE,
                                extract(value(t),'nesting/SELECT') select_seq
                                from table(XMLSequence(XMLType(xml_expression).extract('dml/where/nesting'))) t) LOOP
                modify_out := modify_out || CHR(10) || CHR(9) || CHR(9) || out_condition.S_COLUMN || ' ' || out_condition.N_TYPE || ' (' ||  LAB4.XMLSelect(out_condition."SELECT_SEQ".getClobVal()) || ')';
            end loop;
            modify_out := modify_out || ';';
        else dbms_output.put_line('Type error');
    end case;
    RETURN modify_out;
END;

------------------------------------------------------------------------------
--Тесты
BEGIN
    dbms_output.put_line(LAB4.XMLCREATE('<create>
    <user>LAB4</user>
    <name>t1</name>
    <columns>
        <column>
            <column_name>id</column_name>
            <datatype>NUMBER</datatype>
            <not_null>false</not_null>
            <default></default>
        </column>
        <column>
            <column_name>num</column_name>
            <datatype>NUMBER</datatype>
            <not_null>false</not_null>
            <default></default>
        </column>
        <column>
            <column_name>val</column_name>
            <datatype>VARCHAR(10)</datatype>
            <not_null>false</not_null>
            <default></default>
        </column>
    </columns>
    <constraints>
        <primary_key>
            <column_name>id</column_name>
            <constraint_name>pk_t1</constraint_name>
        </primary_key>
    </constraints>
</create>'));
end;

BEGIN
    dbms_output.put_line(LAB4.XMLModify('<dml>
    <dml_type>UPDATE</dml_type>
    <affect_table>LAB4."tab_name"</affect_table>
    <affect_columns>
        <column>col1</column>
    </affect_columns>
    <new_values>
        <value>''1''</value>
    </new_values>
    <where>
        <nesting>
            <nesting_type>IN</nesting_type>
            <column>id</column>
            <SELECT>
                <columns>
                    <column>id</column>
                </columns>
                <from>
                    <tab>LAB4."tab_name"</tab>
                </from>
                <where>
                    <condition>"tab_name".id = 1</condition>
                </where>
            </SELECT>
        </nesting>
    </where>
</dml>'));
end;

BEGIN
    dbms_output.put_line(LAB4.XMLDrop('<drop>
    <table_name>t1</table_name>
    <table_name>t2</table_name>
    <table_name>t3</table_name>
    <table_name>t4</table_name>
</drop>'));
end;


select   from dual;

BEGIN
    dbms_output.put_line(LAB4.XMLSelect('<SELECT>
    <columns>
        <column>id</column>
        <column>num</column>
        <column>val</column>
    </columns>
    <from>
        <tab>LAB4."t1"</tab>
    </from>
    <where>
        <nesting>
            <nesting_type>IN</nesting_type>
            <column>t1.id</column>
            <SELECT>
                <columns>
                    <column>id</column>
                </columns>
                <from>
                    <tab>LAB4."t2"</tab>
                </from>
                <where>
                    <condition>"t2".num between 2 and 4</condition>
                    <condition>and val like ''%a%''</condition>
                </where>
            </SELECT>
        </nesting>
    </where>
</SELECT>'));
END;


CREATE TABLE LAB4."t1" (
id NUMBER ,
num NUMBER ,
val VARCHAR(10) ,
 CONSTRAINT
pk_t1 PRIMARY KEY (id)
);

create sequence LAB4.t1_id_seq
start with 1
increment
by 1;



CREATE OR REPLACE TRIGGER LAB4.t1_id_trigger
BEFORE INSERT ON
LAB4."t1"
FOR EACH ROW
BEGIN
select LAB4.t1_id_seq.nextval INTO :new."ID" FROM
dual;
END;