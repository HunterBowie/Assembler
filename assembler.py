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

class ASMSyntaxError(Exception):
    pass

class ASMMemoryError(Exception):
    pass

class ASMNameError(Exception):
    pass

class ASMImportError(Exception):
    pass


class RealTimer:
    def __init__(self):
        self.start_time = -1
        self.stop_time = -1
    
    def start(self):
        self.reset()
    
    def get(self):
        if self.start_time == -1:
            return 0
        if self.stop_time == -1:
            return time.monotonic()-self.start_time

        return self.stop_time-self.start_time
    
    def reset(self):
        self.start_time = time.monotonic()
        self.stop_time = -1

    def stop(self):
        self.stop_time = time.monotonic()
    
    def passed(self, seconds):
        return self.get() >= seconds
    
    def __repr__(self):
        return f"time: {self.get()}"
        


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
    MEM_SIZE = 256
    STACK_LEN = 8
    def __init__(self):
        self.output = [0 for i in range(self.MEM_SIZE)]
        self.raw_data = [] # ["#import 'another file'", "section.data"]
        self.data = {"header": [], "section.data": [], "section.code": []}
        self.defines = {} # {"name": value}
        self.variables = {} # {"name": addr}
        self.labels = {} # {"name": addr}
        self.data_mem_addr = self.MEM_SIZE - self.STACK_LEN - 1
        self.code_mem_addr = 0
    
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
        self.data = {"header": [], "section.data": [], "section.code": []}
        position = "header"
        for line in self.raw_data:
            if "section.data" == line:
                position = "section.data"
                continue
            if "section.code" == line:
                position = "section.code"
                continue
            self.data[position].append(line)
            
    def _proccess_header(self):
        data = self.data["header"]
        for line in data:
            if "#define" in line:
                parts = line.split(" ")
                if not is_literal_value(parts[2]):
                    print(f"[WARNING] #define {parts[1]} has non-literal value {parts[2]}")
                self.defines[parts[1]] = parts[2]
            
            elif "#import" in line:
                parts = line.split(" ")
                print("importing placeholder")
            
            else:
                raise ASMSyntaxError(f"header declaration {line} is not valid")
        data.clear()
    
    def _new_instruction(self, memonic, operand):
        self.output[self.code_mem_addr] = INSTRUCTIONS.index(memonic.lower())
        self.code_mem_addr += 1
        if is_literal_value(operand):
            operand = make_int(operand)
        else:
            if operand in self.variables.keys():
                operand = self.variables[operand]
            elif operand in self.labels.keys():
                operand = self.labels[operand]
            elif operand in self.defines.keys():
                operand = self.defines[operand]
                
                try:
                    operand = make_int(operand)
                except ValueError:
                    raise ASMSyntaxError(f"defined value {operand} is not a literal")
            else:
                raise ASMNameError(f"\"{operand}\" is not recoginzed as var, label, or def")
        self.output[self.code_mem_addr] = operand
        self.code_mem_addr += 1
        


    def _new_variable(self, name, value):
        self.variables[name] = self.data_mem_addr
        if value != "null":
            self._new_instruction("ldi", value)
            self._new_instruction("sta", str(self.data_mem_addr))
        self.data_mem_addr -= 1

    
    def _proccess_data_section(self):
        data = self.data["section.data"]
        for line in data:
            for d_name,d_value in self.defines.items():
                if d_name in line:
                    line = line.replace(d_name, d_value)
            parts = line.split(" ")
            if len(parts) != 2:
                raise ASMSyntaxError(f"wrong number of arguments for variable definition {line}")
            self._new_variable(parts[0], parts[1])
        data.clear()

    
    def _proccess_code_section(self):
        data = self.data["section.code"]
    
    def assemble(self, raw_data):
        self.raw_data = raw_data
        self._clean_raw()
        self._load_data_from_raw()
        self._proccess_header()
        self._proccess_data_section()
        print(self.data)
        print(self.defines, self.variables, self.labels)
        # self._proccess_code_section()
        return self.output


def format_output(output, format):
    string_output = ""
    for addr,data in enumerate(output):
        output_line = format.replace(ADDR_SPOT, str(addr))
        output_line = output_line.replace(DATA_SPOT, str(data))
        string_output = string_output + output_line + "\n"
    return string_output
        
def main():
    timer = RealTimer()
    timer.start()
    data = read_file("input")
    data = Assembler().assemble(data)
    data = format_output(data, read_file("format", split=False))
    write_file("output", data)
    timer.stop()
    print(f"\nAssembled Program in {timer.get()} seconds")


main()