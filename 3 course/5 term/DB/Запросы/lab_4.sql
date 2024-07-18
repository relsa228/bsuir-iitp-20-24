1. Пул запросов для сложной выборки из базы данных:
Выбрать названия всех произведений определенного автора (по ФИО)
SELECT works.name FROM works WHERE id in ( 
	SELECT authorship.work FROM authorship WHERE authorship.author = (
		SELECT authors.id FROM authors WHERE authors.name = 'Казимир' AND authors.surname = 'Кац' AND authors.patronymic = 'Авраамович'));

Выбрать названия заказчиков для которых печатал партии центр по определенному адресу
SELECT customers.name FROM customers WHERE id in (
	SELECT orders.customer FROM orders WHERE id in (
		SELECT batches.order From batches WHERE batches.print_center in (
			SELECT print_centers.id FROM print_centers WHERE print_centers.adress = '93 The Glory way, Novigrad')))

-------------------------------------------------------------------------------------------------------
2. Пул SQL запросов для получения представлений в БД:
Адреса печатных центров и менеджеры, которые за них ответсвенны
SELECT print_centers.address, "name", "surname" FROM managers
	JOIN print_centers ON print_centers.manager = managers.id

Получить все партии, принадлежащие заказчику
SELECT customers.name, batches.id
	FROM customers RIGHT JOIN batches 
		ON batches."order" IN (SELECT id FROM orders WHERE customer = customers.id);

---------------------------------------------------------------------------------------------------
3. Пул запросов для получения сгруппированных данных:
Сумма, заплаченная каждым из заказчиков (с выводом имен заказчиков через фк)
SELECT orders.customer, 
	(SELECT customers.name FROM customers WHERE id = orders.customer) AS "name", 
		SUM(cost) AS Profit 
			FROM "orders" GROUP BY orders.customer

Сумма, заплаченная каждым из заказчиков (> 500000)
SELECT orders.customer, 
	(SELECT customers.name FROM customers WHERE id = orders.customer) AS "name", 
		SUM(cost) AS Profit 
			FROM "orders" GROUP BY orders.customer
				HAVING SUM(cost) > 500000

Объединение ФИО менеджеров и авторов
SELECT "name", surname, patronymic 
	FROM authors
		UNION SELECT "name", surname, patronymic 
			FROM managers;

------------------------------------------------------------------------------------------------------
4. Пул SQL запросов для сложных операций с данными:
Авторы, имеющие хотя бы одно произведение конкретного жанра
SELECT "surname", "name", "patronymic" FROM "authors" WHERE EXISTS 
	(SELECT "id" FROM works WHERE EXISTS 
		(SELECT genre FROM genre_affiliation WHERE "work" in 
			(SELECT "work" FROM authorship WHERE authorship.author = "authors".id) 
				AND genre = 2));

Добавление менеджера в авторы
INSERT INTO authors (id, surname, "name", "patronymic")
	SELECT "id", "surname", "name", "patronymic" FROM managers
		WHERE "surname" = 'Шварцман' AND "name" = 'Ефим' AND "patronymic" = 'Адамович'; 

Все авторы, которые не являются менеджерами
SELECT * FROM authors EXCEPT SELECT * FROM authors WHERE id IN (SELECT id FROM managers)

Все аторы, которые являются менеджерами
SELECT * FROM authors INTERSECT SELECT * FROM authors WHERE id IN (SELECT id FROM managers)

название жанр 