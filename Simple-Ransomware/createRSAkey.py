from Crypto.PublicKey import RSA
from Crypto import Random

random_generator = Random.new().read
keyPair = RSA.generate(4096, random_generator) #generate pub and priv key

pubKey = keyPair.publickey()
print(f"Public key:  (n={hex(pubKey.n)}, e={hex(pubKey.e)})")
pubKeyPEM = pubKey.exportKey()
print(pubKeyPEM.decode('ascii'))

print(f"Private key: (n={hex(pubKey.n)}, d={hex(keyPair.d)})")
privKeyPEM = keyPair.exportKey()
print(privKeyPEM.decode('ascii'))

with open ("private.pem", "wb") as prv_file:
    prv_file.write(keyPair.exportKey('PEM'))

with open ("public.pem", "wb") as pub_file:
    pub_file.write(pubKey.exportKey('PEM'))
