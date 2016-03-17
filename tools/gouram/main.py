from tools.gouram.gouram import Gouram
import sys

if __name__ == "__main__":
    g = Gouram()
    print(g.expand(sys.argv[1]))
