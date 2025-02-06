from os import pardir, path

CURRENT_DIR = path.dirname(__file__)
PROJECT_DIR = path.abspath(path.join(CURRENT_DIR, pardir, pardir))

CONFIG_PATH = path.join(PROJECT_DIR, "config.json")


def read_file(file_path, split=None):
    with open(path.join(PROJECT_DIR, file_path), "r") as f:
        data = f.read()
        if split is not None:
            data = data.split(split)
        return data


def write_file(file_path, data):
    with open(path.join(PROJECT_DIR, file_path), "w") as f:
        f.write(data)
