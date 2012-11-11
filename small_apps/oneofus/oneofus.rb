
class OneOfUs(object)
    def __init__(self, x, y, board):
        self.X = x
        self.Y = y
        self.board = board
        self.path = ""
        self.x = 0
        self.y = 0

    def find_path(self):
        pass
    end

    def full_filled(self):
        pass
    end

    def move(self):
        pass
    end

if __name__ == "__main__":
    oou = OneOfUs(3, 3, "CbBbCbAaCbCaCbAbCb")
    oou.find_path()
    print oou.path

