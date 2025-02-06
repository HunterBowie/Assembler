from .timer import RealTimer
from .util import read_file
from .assembler import Assembler, CONFIG, write_output
from os import path
        
def main():
    timer = RealTimer()
    timer.start()
    data = read_file(CONFIG["input-file-path"], split="\n")
    assembler = Assembler()
    data = assembler.assemble(data)
    used_memory = assembler.get_remaining_memory()
    write_output(data)
    timer.stop()
    print(f"""\n
    -- Assembled Program --\n
time: {timer.get()} seconds
memory: {used_memory}/{CONFIG['memory-size']} bytes used
output: -> {CONFIG['output']} <-\n""")


main()