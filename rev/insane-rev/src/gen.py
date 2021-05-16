def calc_fact(x):
    pair = None
    mn = 256
    for i in range(16):
        for j in range(i, 16):
            p = i * j
            s = abs(x - p)
            if i + j + s < mn:
                pair = (i, j)
                mn =  i + j + s
    return (pair[0], pair[1], x - pair[0] * pair[1])

def gen_str(x):
    (i, j, diff) = calc_fact(x)
    if diff < 0:
        c = '-'
    else:
        c = '+'

    x = '+' * i
    y = '+' * j
    z = c * abs(diff)
    return '>{}[<{}>-]<{}'.format(x, y, z)

sub = '[<->-]'

def gen_cmp(c):
    payload = ''
    payload += '>,>'
    payload += gen_str(ord(c))
    payload += sub
    payload += '<'
    payload += '[<+>[-]]<'
    return payload

def print_yes_no():
    payload = ''
    payload += '>+<[>->'
    payload += gen_str(ord('N'))
    payload += '.>'
    payload += gen_str(ord('G'))
    payload += '.>'
    payload += gen_str(ord('\n'))
    payload += '.<<<<[-]]'

    payload += '>[-'
    payload += gen_str(ord('O'))
    payload += '.>'
    payload += gen_str(ord('K'))
    payload += '.>'
    payload += gen_str(ord('\n'))
    payload += '.>]'
    return payload


flag = 'TSGLIVE{>+++++++[<++++++++++++>-]<+}'
#flag = 'T'

payload = ''.join([gen_cmp(c) for c in flag])
payload += print_yes_no()
print(payload)



