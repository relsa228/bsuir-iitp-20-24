-----------------------------------------------Триггеры----------------------------------------------------
1. Инкримент колличества изданных книг у авторов, причастных к написанию (так как author и work в сумме дают PK для many-to-many 
	таблицы проверять записи на уникальность нет смысла)
CREATE OR REPLACE FUNCTION inc_book_count() 
RETURNS TRIGGER
LANGUAGE plpgsql
AS '
  BEGIN 
  
    UPDATE authors
    SET work_count = work_count + 1
    WHERE authors.id = NEW.author;
  
  RETURN NEW;
  END;';

CREATE OR REPLACE TRIGGER inc_book_count AFTER UPDATE OR INSERT ON authorship
  FOR EACH ROW EXECUTE PROCEDURE inc_book_count();

2. Отправка партий после того, как будет напечатана последняя из них
CREATE OR REPLACE FUNCTION send_order() 
RETURNS TRIGGER
LANGUAGE plpgsql
AS '
  BEGIN 
    IF NEW.print_state = 4 then
      UPDATE print_centers SET publication_batch = publication_batch + 1 WHERE id = NEW.print_center;
      IF (SELECT COUNT(*) from batches WHERE "order" = NEW."order") = (SELECT COUNT(*) from batches WHERE "order" = NEW."order" AND print_state = 4) then
        UPDATE orders Set order_state = 4 WHERE id = NEW."order";
        UPDATE batches SET print_state = 5 WHERE "order" = NEW."order";
      end if;
    end if;
    IF NEW.print_state = 3 then
      UPDATE print_centers SET publication_batch = publication_batch - 1 WHERE id = NEW.print_center;
    end if;
  RETURN NEW;
  END;
  ';
  
CREATE OR REPLACE TRIGGER send_order AFTER UPDATE OR INSERT ON batches
  FOR EACH ROW EXECUTE PROCEDURE send_order()

3. Инкремент каунтера заказов
CREATE OR REPLACE FUNCTION inc_order_count() 
RETURNS TRIGGER
LANGUAGE plpgsql
AS '
  BEGIN 
  
    UPDATE customers
    SET order_count = order_count + 1
    WHERE customers.id = NEW.customer;
  
  RETURN NEW;
  END;';

CREATE OR REPLACE TRIGGER inc_order_count AFTER INSERT ON orders
  FOR EACH ROW EXECUTE PROCEDURE inc_order_count();
  --------------------------------------------Процедуры:---------------------------------------------------
1. Отправить со склада все партии определенного заказа
CREATE PROCEDURE given_away_order("order_id" TEXT)
LANGUAGE SQL
AS $$
UPDATE batches SET print_state = 5 WHERE "order" = "order_id"::uuid
$$;

2. Сменить должность менеджера, все предыдущие назначения убираются
CREATE PROCEDURE change_position(manager_id TEXT, new_position INT)
LANGUAGE plpgsql
AS '
Begin
IF (SELECT position From managers WHERE "id" = manager_id::uuid) = 1 AND new_position != 1 then
UPDATE customers Set manager = NULL WHERE manager = manager_id::uuid;
end if;
IF (SELECT position From managers WHERE "id" = manager_id::uuid) = 2 AND new_position != 2 then
UPDATE print_centers Set manager = NULL WHERE manager = manager_id::uuid;
end if;
IF (SELECT position From managers WHERE "id" = manager_id::uuid) = 3 AND new_position != 3 then
UPDATE orders Set manager = NULL WHERE manager = manager_id::uuid;
end if;

UPDATE managers SET position = new_position WHERE "id" = manager_id::uuid;
end;
';


-----------------------------------Функции:---------------------------------------------------------------
1. Функция для получения названий заказчиков для которых печатал партии центр по определенному адресу
CREATE FUNCTION get_customers_printcenter(addr TEXT)
RETURNS TABLE(customers.name)
LANGUAGE SQL
AS $$
SELECT customers.name FROM customers WHERE id in (
	SELECT orders.customer FROM orders WHERE id in (
		SELECT batches.order From batches WHERE batches.print_center in (
			SELECT print_centers.id FROM print_centers WHERE print_centers.address = addr)))
$$;
-----
SELECT get_customers_printcenter('93 The Glory way, Novigrad')

2. Авторы, имеющие хотя бы одно произведение конкретного жанра
CREATE FUNCTION genre_author_info(genre_num INT)
RETURNS TABLE("Name" TEXT, "Patronymic" TEXT, "Surname" TEXT)
LANGUAGE SQL
AS $$
SELECT "name", "patronymic", "surname" FROM "authors" WHERE EXISTS 
	(SELECT "id" FROM works WHERE EXISTS 
		(SELECT genre FROM genre_affiliation WHERE "work" in 
			(SELECT "work" FROM authorship WHERE authorship.author = "authors".id) 
				AND genre = genre_num))
$$;