from enum import Enum

class State(Enum):
    OK = 0
    MAIN_MISSING = 1
    MIXED_EXTENSIONS = 2
    MULTIPLE_MAINS = 3
    COMPILATION_ERRORS = 4