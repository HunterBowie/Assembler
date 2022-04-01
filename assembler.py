import time
INSTRUCTIONS = [
    "nop",
    "lda",
    "ldi",
    "sta",
    "add",
    "sub",
    "inc",
    "dec",
    "jmp",
    "jc",
    "jn",
    "jz",
    "inw",
    "inx",
    "outy",
    "outz",
    "call",
    "ret",
    "push",
    "pull",
    "pop",
    "null",
    "null",
    "null",
    "null",
    "null",
    "null",
    "null",
    "null",
    "null",
    "null",
    "hlt"
]

HEX_CHARS = [
    "0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"
]

BIN_CHARS = [
    "0","1"
]

ADDR_SPOT = "@ADDRESS"
DATA_SPOT = "@DATA"
INFO_SPOT = "@INFO"

class ASMSyntaxError(Exception):
    pass

class ASMMemoryError(Exception):
    pass

class ASMNameError(Exception):
    pass

class ASMImportError(Exception):
    pass

def read_file(path, split=True):
    with open(path+".txt", "r") as f:
        data = f.read()
        if split:
            data = data.split("\n")
        return data

def write_file(path, data):
    with open(path+".txt", "w") as f:
        f.write(data)

def make_int(value):
    if value[:2] == "0b":
        value = value[2:]
        value = value[::-1]
        digit = 1
        num = 0
        for i in range(len(value)):
            num += BIN_CHARS.index(value[i]) * digit
            digit = digit * 2
        return num
    elif value[:2] == "0x":
        value = value[2:]
        value = value[::-1]
        digit = 1
        num = 0
        for i in range(len(value)):
            num += HEX_CHARS.index(value[i]) * digit
            digit = digit * 16
        return num
    else:
        return int(value)

def is_literal_value(value):
    try:
        int(value)
    except ValueError:
        pass
    else:
        return True
    if value[:2] == "0b":
        return True
    if value[:2] == "0x":
        return True
    return False


class Assembler:
    MEM_SIZE = 255
    def __init__(self):
        self.output = []
        self.raw_data = [] # ["#import 'another file'", "section.data"]
        self.data = {"header": [], "section.data": [], "section.code": []}
        self.defines = [] # {"name": value}
        self.labels = [] # {"name": addr}
        self.variables = [] # {"name": addr}
    
    def _clean_raw(self):
        self.raw_data = [line.strip() for line in self.raw_data]
        self.raw_data = [line for line in self.raw_data if line != ""]
        new_raw_data = []
        for line in self.raw_data:
            if ";" in line:
                parts = line.split(";")
                new_raw_data.append(parts[0].strip())
                continue
            new_raw_data.append(line)
        self.raw_data = new_raw_data
    
    def _load_data_from_raw(self):
        for line in self.raw_data:
            pass
    
    def _proccess_header(self):
        data = self.data["header"]
    
    def _proccess_data_section(self):
        data = self.data["section.data"]
    
    def _proccess_code_section(self):
        data = self.data["section.code"]
    
    def assemble(self, raw_data):
        self.raw_data = raw_data
        self._clean_raw()
        self._load_data_from_raw()
        self._proccess_header()
        self._proccess_data_section()
        self._proccess_code_section()
        return self.data


def format_output(output, format):
    new_output = []
    for addr_data in output:
        addr, data = addr_data
        output_line = format.replace(ADDR_SPOT, str(addr))
        output_line = output_line.replace(DATA_SPOT, str(data))
        new_output.append(output_line)
    return new_output
        
def main():
    data = read_file("input")
    data = Assembler().assemble(data)
    data = format_output(data, read_file("format", split=False))
    write_file("output", data)

main()
