class key:
    def __init__(self, p, q):
        self.N = p * q
        self.phi = (p - 1) * (q - 1)
        self.e = 65537
        self.d = pow(self.e, -1, self.phi)

    def gen_private_key(self):
        return (self.N, self.d)

    def gen_public_key(self):
        return (self.N, self.e)

def encrypt(msg, public):
    N, e = public
    return pow(msg, e, N)

def decrypt(c, private):
    N, d = private
    return pow(c, d, N)


from private_key import p, q
from FLAG import FLAG


msg = int.from_bytes(FLAG, byteorder='big')
keys = key(p, q)
encrypted = encrypt(msg, keys.gen_public_key())

assert(msg < p * q)

print(f'N, e = {keys.gen_public_key()}')
print(f'c = {encrypted}')

if pow(msg, keys.phi, keys.N) != 1:
    raise Exception('Oops! RSA is broken!')