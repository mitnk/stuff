import re
import time
import urllib2

name='mitnk'
password='python'

def get_level_string():
    url = "http://www.hacker.org/runaway/index.php?" + 'name=' + name + '&password=' + password
    try:
        page = urllib2.urlopen(url, timeout=10)
    except urllib2.URLError, e:
        print str(e)

    content = page.read()
    result = re.search(r'<PARAM NAME=FlashVars VALUE="([^"]+)">', content)
    if not result:
        print 'not found'
    s = result.group(1)
    f = open('config.txt', 'w')
    f.write(s + "\n")
    f.close()
    return s


def parse_string():
    f = open('config.txt', 'r')
    p = "FVterrainString=([^&]+)&FVinsMax=(\d+)&FVinsMin=(\d+)&FVboardX=(\d+)&FVboardY=(\d+)&FVlevel=(\d+)"
    result = re.search(p, f.read())
    f.close()
    return (
        result.group(1),
        int(result.group(2)),
        int(result.group(3)),
        int(result.group(4)),
        int(result.group(5)),
        int(result.group(6)),
    )


def get_all_step(n):
    if n == 1:
        return ['R', 'D']
    return ["".join([x, y]) for x in get_all_step(n - 1) for y in get_all_step(1)]

def is_valid(step, board, FVboardX, FVboardY):
    length = len(step)
    i = 0
    x = y = 0
    while (1):
        c = step[i % length]
        if c == 'R':
            x += 1
        else:
            y += 1
        if x >= FVboardX or y >= FVboardY:
            return True
        elif board[x][y] == 1:
            return False
        i += 1
    return False


def runaway(board, FVinsMin, FVinsMax, FVboardX, FVboardY):
    for count in range(FVinsMin, FVinsMax + 1):
        for step in get_all_step(count):
            if is_valid(step, board, FVboardX, FVboardY):
                return step
    return None

def main():
    get_level_string()
    FVterrainString, FVinsMax, FVinsMin, FVboardX, FVboardY, FVlevel = parse_string()
    print "===This is Level %d===\n" % FVlevel

    board = []
    for y in range(FVboardX):
        column = []
        for x in range(FVboardY):
            if FVterrainString[x * FVboardY + y] == 'X':
                column.append(1)
            else:
                column.append(0)
        board.append(column)

    path = runaway(board, FVinsMin, FVinsMax, FVboardX, FVboardY)
    if not path:
        print "Path not found!"
        return None
    url = "http://www.hacker.org/runaway/index.php?path=" + path + '&name=' + name + '&password=' + password
    urllib2.urlopen(url)
    return True

if __name__ == "__main__":
    for i in range(30):
        t = time.time()
        main()
        print "Used time %d seconds" % (time.time() - t)
