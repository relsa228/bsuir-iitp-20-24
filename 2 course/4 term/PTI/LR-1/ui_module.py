import os

from text_module import WorkWithText


class UserInterface:
    """Класс пользовательского интерфейса"""

    def __init__(self) -> None:
        """
            Конструктор класса.

            Создает:
                text_in_proc - для работы с текстом.
                :type text_in_proc: WorkWithText

                original_text - для сохранения оригинального пользовательского ввода
                :type original_text: str
        """
        self.text_in_proc = WorkWithText()
        self.original_text = ""

    def start_word_count(self):
        """
           Вызов метода word_count из класса WorkWithText в интерфейсе.
        """
        print(self.text_in_proc.word_count())

    def start_average_words(self):
        """
            Вызов метода average_words из класса WorkWithText в интерфейсе.
        """
        print(self.text_in_proc.average_words())

    def start_top_engrams(self):
        """
            Вызов метода top_engrams из класса WorkWithText в интерфейсе.
        """
        print("Желаете самостоятельно ввести значения N и K? (Y/AnyKey)")
        if input("Ваш ответ: ") == "Y":
            n = int(input("Введите N: "))
            k = int(input("Введите K: "))
            print(self.text_in_proc.top_engrams(k, n))
        else:
            print("Запускаем функцию со стандартными параметрами: K = 10, N = 4")
            print(self.text_in_proc.top_engrams(10, 4))

    def start_interface(self):
        """
            Запуск интерфейса.
        """
        self.original_text = input("Введите текст: ")
        while True:
            if self.original_text != "":
                break
            else:
                os.system('cls||clear')
                self.original_text = input("Ошибка. Повторите ввод: ")
        self.text_in_proc.text = self.original_text
        while True:
            os.system('cls||clear')
            print("Выберите действие:\n1. Статистика по словам\n2. Среднее и медианное количество слов в предложении"
                  "\n3. Топ n-грам\n4. Получить рабочую строку\n5. Выйти")
            choose = input("Ваш выбор: ")
            match choose:
                case "1":
                    os.system('cls||clear')
                    self.start_word_count()
                    input()
                case "2":
                    os.system('cls||clear')
                    self.start_average_words()
                    input()
                case "3":
                    os.system('cls||clear')
                    self.start_top_engrams()
                    input()
                case "4":
                    os.system('cls||clear')
                    print(f"Ваша строка: {self.original_text}")
                    input()
                case "5":
                    break
                case _:
                    os.system('cls||clear')
                    print("Неверный ввод.")
                    input()
