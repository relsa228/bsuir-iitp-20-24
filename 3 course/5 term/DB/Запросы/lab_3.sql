--------------------------------------------------------------------------------------------------------
Таблицы
ON UPDATE NO ACTION - ключ не должен меняться, поэтому неважно, что тут будет
ON DELETE NO ACTION - значение нельзя удалять (я так решил), поэтому no action

CREATE TABLE "authors" (
	"id" UUID NOT NULL,
	"name" TEXT NOT NULL,
	"surname" TEXT NOT NULL,
	"patronymic" TEXT NULL DEFAULT NULL,
	"work_count" INTEGER NOT NULL DEFAULT '0',
	PRIMARY KEY ("id")
)

CREATE TABLE "genres" (
	"id" SERIAL,
	"genre" TEXT NOT NULL,
	PRIMARY KEY ("id")
)

CREATE TABLE "order_states" (
	"id" SERIAL,
	"order_state" TEXT NOT NULL,
	PRIMARY KEY ("id")
)

CREATE TABLE "positions" (
	"id" SERIAL,
	"position" TEXT NOT NULL,
	PRIMARY KEY ("id")
)

CREATE TABLE "print_states" (
	"id" SERIAL,
	"print_state" TEXT NOT NULL,
	PRIMARY KEY ("id")
)

CREATE TABLE "work_types" (
	"id" SERIAL,
	"work_type" TEXT NOT NULL,
	PRIMARY KEY ("id")
)

CREATE TABLE "managers" (
	"id" UUID NOT NULL,
	"name" TEXT NOT NULL,
	"surname" TEXT NOT NULL,
	"patronymic" TEXT NULL DEFAULT NULL,
	"username" TEXT NOT NULL,
	"position" INTEGER NULL DEFAULT NULL,
	"password" TEXT NULL DEFAULT NULL,
	"last_auth_time" TIMESTAMP NULL DEFAULT NULL,
	PRIMARY KEY ("id"),
	FOREIGN KEY ("position") REFERENCES "positions" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION
)

CREATE TABLE "customers" (
	"id" UUID NOT NULL,
	"name" TEXT NOT NULL,
	"spec" TEXT NOT NULL,
	"order_count" INTEGER NOT NULL,
	"manager" UUID NOT NULL,
	PRIMARY KEY ("id"),
	FOREIGN KEY ("manager") REFERENCES "managers" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION
)

CREATE TABLE "orders" (
	"id" UUID NOT NULL,
	"customer" UUID NOT NULL,
	"cost" BIGINT NOT NULL,
	"open_date" DATE NOT NULL,
	"deadline" DATE NOT NULL,
	"close_date" DATE NULL DEFAULT NULL,
	"order_state" INTEGER NOT NULL,
	"manager" UUID NOT NULL,
	PRIMARY KEY ("id"),
	FOREIGN KEY ("customer") REFERENCES "customers" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION,
	FOREIGN KEY ("manager") REFERENCES "managers" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION,
	FOREIGN KEY ("order_state") REFERENCES "order_states" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION
)

CREATE TABLE "works" (
	"id" UUID NOT NULL,
	"name" TEXT NOT NULL,
	"edition_number" INTEGER NOT NULL,
	"genre" INTEGER NOT NULL,
	"type" INTEGER NOT NULL,
	PRIMARY KEY ("id"),
	FOREIGN KEY ("genre") REFERENCES "genres" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION,
	FOREIGN KEY ("type") REFERENCES "work_type" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION
)

CREATE TABLE "authorship" (
	"author" UUID NOT NULL,
	"work" UUID NOT NULL,
	FOREIGN KEY ("author") REFERENCES "authors" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION,
	FOREIGN KEY ("work") REFERENCES "works" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION
)

CREATE TABLE "print_centers" (
	"id" UUID NOT NULL,
	"address" TEXT NULL DEFAULT NULL,
	"manager" UUID NULL DEFAULT NULL,
	"batch_in_progress" INTEGER NULL DEFAULT NULL,
	"publication_batch" INTEGER NULL DEFAULT NULL,
	PRIMARY KEY ("id"),
	FOREIGN KEY ("manager") REFERENCES "managers" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION
)

CREATE TABLE "batches" (
	"id" UUID NOT NULL,
	"order" UUID NULL DEFAULT NULL,
	"work" UUID NULL DEFAULT NULL,
	"print_center" UUID NULL DEFAULT NULL,
	"print_state" INTEGER NULL DEFAULT NULL,
	PRIMARY KEY ("id"),
	FOREIGN KEY ("order") REFERENCES "orders" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION,
	FOREIGN KEY ("print_center") REFERENCES "print_center" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION,
	FOREIGN KEY ("print_state") REFERENCES "print_states" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION,
	FOREIGN KEY ("work") REFERENCES "works" ("id") ON UPDATE NO ACTION ON DELETE NO ACTION
)

--------------------------------------------------------------------------------------------------------
Операции CRUD:
---
gen_random_uuid() - генератор uuid 
crypt('password', gen_salt('bf', 8)) - шифровка паролей

INSERT INTO "tab_name" VALUES (val1, val2, val3 ... valN)
INSERT INTO "tab_name" (col1, col2, col3) VALUES (val1, val2, val3)

Менеджеры (запомни пароли)
INSERT INTO "managers" VALUES (gen_random_uuid(), 'Исмаил', 'Голдштейн', 'Яковлевич', 'goldstein', 1, crypt('qwerty123', gen_salt('bf', 8)), '2021-10-12 11:42:39');
INSERT INTO "managers" VALUES (gen_random_uuid(), 'Авраам', 'Вайгельман', 'Даянович', 'vaigelman', 2, crypt('qwe123rty', gen_salt('bf', 8)), '2022-09-05 13:40:31');
INSERT INTO "managers" VALUES (gen_random_uuid(), 'Леви', 'Ойтенберг', 'Аланович', 'oitenberg', 2, crypt('123qwerty', gen_salt('bf', 8)), '2021-07-14 23:22:40');
INSERT INTO "managers" VALUES (gen_random_uuid(), 'Джозеф', 'Керштейн', 'Давидович', 'kerstein', 2, crypt('qwe12345rty', gen_salt('bf', 8)), '2022-09-06 13:40:31');
INSERT INTO "managers" VALUES (gen_random_uuid(), 'Ефим', 'Шварцман', 'Адамович', 'schwartzman', 2, crypt('qwe123456rty', gen_salt('bf', 8)), '2022-10-07 15:12:00');
---
(не забывать про AND OR NOT IS)
SELECT param1, param2 FROM table_name WHERE param = 'param_val';
---
UPDATE table_name SET param = 'new_val' WHERE param = 'param_val';
ALTER TABLE table_name ADD new_col_name CHARACTER TEXT NULL  DEFAULT 'def';
ALTER TABLE table_name ALTER COLUMN col_name TYPE TEXT;
ALTER TABLE table_name RENAME COLUMN col_name TO new_col_name;
---
(не забывать про AND OR NOT IS)
DROP TABLE table_name CASCADE (применяй ко всем, лишним не будет); 
DELETE FROM table_name WHERE param='param_val';
ALTER TABLE table_name DROP COLUMN col_name;

--------------------------------------------------------------------------------------------------------
Запросы (  <> -- не равно
			= -- равно)

SELECT DISTINCT col_name FROM table_name; -- выборка уникальных значений
SELECT * FROM table_name ORDER BY col_name; -- выборка с сортировкой по значению (ASC/DESC - по возрастанию, по убыванию)
SELECT col_1, col_2, col_3 FROM table_name ORDER BY col_1 ASC, col_2 DESC;
SELECT col_1, num_2 * num_3 AS total_num FROM table_name ORDER BY total_num; -- можно еще так через псевдонимы 
SELECT * FROM Products ORDER BY ProductName LIMIT 4 OFFSET 2; -- ограничение на вывод (LIMIT - сколько, OFFSET - начиная откуда)
---
SELECT * FROM table_name WHERE col_name IN (val1, val2, val3); -- проверка на вхождение в сет
SELECT * FROM table_name WHERE col_name BETWEEN something AND something; -- проверка на границы 
SELECT * FROM table_name WHERE col_name LIKE шаблон; -- проверка строк по шаблону	'%' - любая подстрока ('aboba%' == 'aboba bobs boba')
																				--	'_' - символ ('aboba_' == 'abobas') 

SELECT * FROM table1, table2 WHERE table2.fk_table1 = table1.fk_table2; -- выборка через форенкеи
SELECT tab1.col1, tab1.col2, tab2.col3 FROM tab1 JOIN tab2 ON tab2.Id = tab1.fk; -- или так

--------------------------------------------------------------------------------------------------------

Выбрать названия всех произведений определенного автора (по ФИО)
SELECT works.name FROM works WHERE id in ( 
	SELECT authorship.work FROM authorship WHERE authorship.author = (
		SELECT authors.id FROM authors WHERE authors.name = 'Казимир' AND authors.surname = 'Кац' AND authors.patronymic = 'Авраамович'));

Выбрать названия заказчиков для которых печатал партии центр по определенному адресу
SELECT customers.name FROM customers WHERE id in (
	SELECT orders.customer FROM orders WHERE id in (
		SELECT batches.order From batches WHERE batches.print_center in (
			SELECT print_centers.id FROM print_centers WHERE print_centers.adress = '93 The Glory way, Novigrad')))
