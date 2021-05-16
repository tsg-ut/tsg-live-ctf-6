import base64
import os
import pathlib
import sys

MAX_SIZE = 2000000

def create_dir(path):
    pathlib.Path(path).mkdir(parents=True, exist_ok=True)

def get_until_null(data):
    idx = data.find(b'\x00')
    if idx < 0:
        print('the given file is broken')
        sys.exit(1)
    return data[:idx].decode('utf-8'), data[idx + 1:]

def unarchive(text):
    data = base64.b64decode(text)

    directory, data = get_until_null(data)
    create_dir(directory)
    while len(data) > 0:
        p, data = get_until_null(data)
        size_s, data = get_until_null(data)
        contents = data[:int(size_s)]
        data = data[int(size_s):]

        create_dir(os.path.dirname(p))
        with open(p, 'wb') as f:
            f.write(contents)
    return directory

def archive_aux(cur):
    l = os.listdir(cur)
    ret = b''
    for x in l:
        p = os.path.join(cur, x)
        if os.path.isdir(p):
            ret += archive_aux(p)
        elif os.path.isfile(p):
            with open(p, 'rb') as f:
                data = f.read()
            ret += p.encode('utf-8') + b'\x00'
            ret += str(len(data)).encode('utf-8') + b'\x00'
            ret += data
    return ret

def archive(directory):
    ret = directory.encode('utf-8') + b'\x00'
    ret += archive_aux(directory)
    return base64.b64encode(ret).decode('utf-8')

def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("--enc", default=None)
    args = parser.parse_args()
    if args.enc is not None:
        print(archive(args.enc))
    else:
        text = input()
        if len(text) > MAX_SIZE:
            print('too long')
            return
        print(unarchive(text))

if __name__ == '__main__':
    main()
