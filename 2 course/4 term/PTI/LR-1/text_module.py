import string
import re


class WorkWithText:
    """Класс для работы с текстом"""
    def __init__(self) -> None:
        """
            Конструктор класса.

            Создает:
                text - рабочая строка.
                :type text_in_proc: str
        """
        self.text = ""

    def word_count(self) -> str:
        """
            Метод подсчета повторений слов в тектсе.

            :rtype: str
            :return: Возвращает строку, в которой перечислены все используемые слова и количество их повторений.
        """
        self.text = self.text.lower()
        tuple_text = self.text.translate(self.text.maketrans('', '', string.punctuation)).split()
        dict_text = dict((word, tuple_text.count(word)) for word in set(tuple_text) if tuple_text.count(word) >= 1)
        result = "Список слов и их повторения в тексте:"
        for i in set(tuple_text):
            result = result + f"\n{i} -- {dict_text[i]}"
        return result

    def average_words(self) -> str:
        """
            Метод нахождения среднего и медианного количества слов в предложениях.

            :rtype: str
            :return: Возвращает строку со значениями среднего и медианного количества слов в предложениях и пояснения к этим
            значениям.
        """
        self.text = self.text.lower()
        tuple_text = re.split(r"[!?.]\s*", self.text)
        tuple_text = [value for value in tuple_text if value != ""]
        sent_count = []
        average = 0
        for sent in tuple_text:
            sent = sent.translate(self.text.maketrans('', '', string.punctuation)).split()
            sent_count.append(len(sent))
        for i in sent_count:
            average = average + i
        sent_count.sort()
        if len(sent_count) % 2 == 0:
            med_count = (sent_count[int((len(sent_count)) / 2)] + sent_count[int((len(sent_count)) / 2) - 1]) / 2
        else:
            med_count = sent_count[int((len(sent_count)) / 2)]
        return f"Среднее количество слов в предложениях: {average / len(sent_count)}\nМедианное количество слов в " \
               f"предложениях: {med_count}"

    def top_engrams(self, k: int, n: int) -> str:
        """
            Метод составления k-топа из n-грам.

            :param n: длина обрабатываемого n-грама
            :type n: int

            :param k: количество выводимых в топе значений
            :type k: int

            :rtype: str
            :return: Возвращает строку со значениями среднего и медианного количества слов в предложениях и пояснения к этим
            значениям.
        """
        self.text = self.text.lower()
        tuple_text = self.text.translate(self.text.maketrans('', '', string.punctuation)).replace(' ', '')
        if n >= len(tuple_text) or n <= 0:
            return "\nОшибка ввода. Неверное значение N."
        i = 0
        n_grams = []
        while n <= len(tuple_text):
            n_grams.append(tuple_text[i:n])
            n = n + 1
            i = i + 1
        n_grams = dict((word, n_grams.count(word)) for word in set(n_grams) if n_grams.count(word) >= 1)
        sorted_tuple = sorted(n_grams.items(), key=lambda x: x[1])
        if k >= len(sorted_tuple) or k <= 0:
            return "\nОшибка ввода. Неверное значение K."
        result = "Заданный k-топ n-грам:"
        for i in range(len(sorted_tuple) - 1, len(sorted_tuple) - k - 1, -1):
            result = result + f"\n{sorted_tuple[i]}"
        return result
