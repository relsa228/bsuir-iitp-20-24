class ClassForTest:
    def __init__(self, string: str, num: int):
        self.string = string
        self.num = num

    def funct1(self):
        return self.string

    def funct2(self):
        return self.num


def take_globals():
    return globals()
