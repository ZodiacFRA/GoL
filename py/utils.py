class Position(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        if isinstance(other, Position):
            return Position(self.x + other.x, self.y + other.y)
        return Position(self.x + other, self.y + other)

    def __sub__(self, other):
        if isinstance(other, Position):
            return Position(self.y - other.y, self.x - other.x)
        return Position(self.x + other, self.y + other)

    def __floordiv__(self, factor):
        return Position(self.x // factor, self.y // factor)

    def __truediv__(self, factor):
        return Position(self.x / factor, self.y / factor)

    def __str__(self):
        return f"(y={self.y}, x={self.x})"
        # return f"({self.y}, {self.x})"

    def __repr__(self):
        return f"Position(y={self.y}, x={self.x})"

    def __eq__(self, other):
        if isinstance(other, Position):
            return self.y == other.y and self.x == other.x
        return (self.x, self.y) == other

## Normal comparison operators (>, <) are used to check if AT LEAST one value is (>, <)
# to the other instance
    def __gt__(self, other):
        return self.y > other.y or self.x > other.x

    def __ge__(self, other):
        return self.y >= other.y or self.x >= other.x

    def __lt__(self, other):
        return self.y < other.y or self.x < other.x

    def __le__(self, other):
        return self.y <= other.y or self.x <= other.x

## BITWISE operators (>>, <<) are used to check if ALL values are (>=, <=)
# to the other instance
    def __rshift__(self, other):
        return self.y >= other.y and self.x >= other.x

    def __lshift__(self, other):
        return self.y <= other.y and self.x <= other.x

    def __mul__(self, other):
        if isinstance(other, Position):
            return Position(self.x * other.x, self.y * other.y)
        return Position(self.x * other, self.y * other)

    def __mod__(self, other):
        if isinstance(other, Position):
            return Position(self.x % other.x, self.y % other.y)
        return Position(self.x % other, self.y % other)

    def get_xy(self):
        return self.x, self.y
