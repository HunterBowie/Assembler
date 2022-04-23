import time, json
"""
output: text-serial, text-parallel, arduino-serial, arduino-parallel
parallel-style: c, json
"""

SERIAL_ADDR_REF = "@ADDRESS"
SERIAL_DATA_REF = "@DATA"
ARDUINO_INSERT_START_SPOT = "//@INSERT_START"
ARDUINO_INSERT_END_SPOT = "//@INSERT_END"

VAR_SEQUENCE_VALUE = "@VAR-VALUE"
VAR_SEQUENCE_ADDR = "@VAR-ADDR"


HEX_CHARS = [
    "0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"
]

BIN_CHARS = [
    "0","1"
]

class ASMSyntaxError(Exception):
    pass

class ASMMemoryError(Exception):
    pass

class ASMNameError(Exception):
    pass

class ASMImportError(Exception):
    pass

class ASMGeneralError(Exception):
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


def read_file(path, split=None):
    with open(path, "r") as f:
        data = f.read()
        if split is not None:
            data = data.split(split)
        return data

def write_file(path, data):
    with open(path, "w") as f:
        f.write(data)


CONFIG = json.load(open("config.json", "r"))


class Assembler:
    def __init__(self):
        self.output = [0 for i in range(CONFIG["memory-size"])]
        self.raw_data = [] # ["#import 'another file'", "section.data"]
        self.data = {"header": [], "section.data": [], "section.code": []}
        self.defines = {} # {"name": value}
        self.variables = {} # {"name": addr}
        self.labels = {} # {"name": addr}
        self.data_mem_addr = CONFIG["memory-size"] - CONFIG["stack-size"] - 1
        self.code_mem_addr = 0
    
    @staticmethod
    def _get_raw_int(value):
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

    @staticmethod
    def _is_literal_value(value):
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


    def _clean_raw(self):
        self.raw_data = [line.strip() for line in self.raw_data]
        
        self.raw_data = [line for line in self.raw_data if line != ""]
        new_raw_data = []
        
        for line in self.raw_data:
            if ";" in line:
                parts = line.split(";")
                if parts[0].strip() != "":
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
                parts = [part for part in parts if part.strip() != ""]
                if not self._is_literal_value(parts[2]):
                    print(f"[WARNING] #define {parts[1]} has non-literal value {parts[2]}")
                if parts[1] in self.defines:
                    print(f"[WARNING] #define {parts[1]} has collision {parts[2]}")
                self.defines[parts[1]] = parts[2]
            
            elif "#import" in line:
                parts = line.split(" ")
                assembler = Assembler()
                assembler.raw_data = read_file(parts[1], split="\n")
                assembler._clean_raw()
                assembler._load_data_from_raw()
                for line in assembler.data["header"]:
                    self.data["header"].append(line)
                for line in assembler.data["section.data"]:
                    self.data["section.data"].append(line)
                for line in assembler.data["section.code"]:
                    self.data["section.code"].append(line)
            
            else:

                raise ASMSyntaxError(f"header declaration {line} is not valid")
        data.clear()
    
    def _new_instruction(self, memonic: str, operand: str):
        self.output[self.code_mem_addr] = CONFIG["instructions"].index(memonic.lower())
        self.code_mem_addr += 1
        if self._is_literal_value(operand):
            operand = self._get_raw_int(operand)
        else:
            if operand in self.variables.keys():
                operand = self.variables[operand]
            elif operand in self.labels.keys():
                operand = self.labels[operand]
            elif operand in self.defines.keys():
                operand = self.defines[operand]
                
                try:
                    operand = self._get_raw_int(operand)
                except ValueError:
                    raise ASMSyntaxError(f"defined value {operand} is not a literal")
            else:
                raise ASMNameError(f"\"{operand}\" is not recoginzed as var, label, or def")
        self.output[self.code_mem_addr] = operand
        self.code_mem_addr += 1
        


    def _new_variable(self, name, value: str):
        self.variables[name] = self.data_mem_addr
        if value != "null":
            for memonic, operand in CONFIG["var-sequence"]:
                if operand == VAR_SEQUENCE_ADDR:
                    operand = str(self.data_mem_addr)
                elif operand == VAR_SEQUENCE_VALUE:
                    operand = value
                self._new_instruction(memonic, operand)
                
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
        ahead_addr = self.code_mem_addr
        label_lines = []
        for line in data:
            if ":" in line:
                parts = line.split(":")
                for i in range(len(parts)):
                    if parts[i] == "":
                        parts.remove("")
                label = parts[0]
                label_lines.append((line, label))
                self.labels[label] = ahead_addr
                if len(parts) == 1:
                    continue
            ahead_addr += 2
        for line,label in label_lines:
            new_line = line.replace(label, "")
            new_line = new_line.replace(":", "")
            new_line = new_line.strip()
            if new_line == "":
                data.remove(line)
            else:
                data[data.index(line)] = new_line
        
        for line in data:
            memonic = operand = "0"
            if " " not in line: # no operand
                memonic = line
            else:
                try:
                    memonic, operand = line.split(" ")
                except ValueError:
                    raise ASMSyntaxError(f"line in section.code is unreadable {line}")
            self._new_instruction(memonic, operand)
        
            
    def get_remaining_memory(self):
        starting_data_mem = CONFIG["memory-size"] - CONFIG["stack-size"] - 1
        amount = starting_data_mem - self.data_mem_addr
        amount += self.code_mem_addr
        return amount
    
    def assemble(self, raw_data):
        self.raw_data = raw_data
        self._clean_raw()
        self._load_data_from_raw()
        self._proccess_header()
        self._proccess_data_section()
        self._proccess_code_section()
        return self.output


def write_output(output):
    def get_serial():
        string_output = ""
        for addr,data in enumerate(output):
            output_line = CONFIG["serial-struct"].replace(SERIAL_ADDR_REF, str(addr))
            output_line = output_line.replace(SERIAL_DATA_REF, str(data))
            string_output = string_output + output_line + "\n"
        return string_output
    
    def get_parallel():
        dict_output = {}
        for index,value in enumerate(output):
            dict_output[index] = value
        return dict_output

    if CONFIG["output"] == "text-serial":
        string_output = get_serial()
        write_file(CONFIG["output-file-path"], string_output)
    elif CONFIG["output"] == "text-parallel":
        dict_output = get_parallel()
        json.dump(dict_output, open(CONFIG["output-file-path"], "w"), indent=CONFIG["text-parallel-spacing"])
    elif CONFIG["output"] == "arduino-serial":
        string_output = get_serial()
        string_data = read_file(CONFIG["arduino-file-path"])
        start_index, end_index = string_data.index(ARDUINO_INSERT_START_SPOT), string_data.index(ARDUINO_INSERT_END_SPOT) 
        string_data = string_data.replace(string_data[start_index+len(ARDUINO_INSERT_START_SPOT):end_index], "\n" + string_output)
        write_file(CONFIG["arduino-file-path"], string_data)
    elif CONFIG["output"] == "arduino-parallel":
        pass
    else:
        raise ASMGeneralError("CONFIG json file has unreadable style attribute")
    

    
        
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