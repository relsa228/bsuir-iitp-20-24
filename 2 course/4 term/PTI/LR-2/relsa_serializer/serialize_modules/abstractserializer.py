from abc import abstractmethod


class AbstractSerializer:
    @abstractmethod
    def dump(self, target_item, file_path: str, globals_from_main: dict) -> None:
        pass

    @abstractmethod
    def dumps(self, target_item, globals_from_main: dict) -> str:
        pass

    @abstractmethod
    def load(self, file_path: str, globals_from_main) -> all:
        pass

    @abstractmethod
    def loads(self, target_str, globals_from_main) -> all:
        pass
