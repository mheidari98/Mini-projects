from Crypto.Cipher import PKCS1_OAEP, AES
from Crypto.PublicKey import RSA
from cryptography.fernet import Fernet   # pip3 install cryptography
import os, struct, hashlib

def decrypt_file(key, in_filename, out_filename=None, chunksize=24*1024):
    if not out_filename:
        out_filename = os.path.splitext(in_filename)[0]

    with open(in_filename, 'rb') as infile:
        origsize = struct.unpack('<Q', infile.read(struct.calcsize('Q')))[0]
        iv = infile.read(16)
        decryptor = AES.new(key, AES.MODE_CBC, iv)

        with open(out_filename, 'wb') as outfile:
            while True:
                chunk = infile.read(chunksize)
                if len(chunk) == 0:
                    break
                outfile.write(decryptor.decrypt(chunk))

            outfile.truncate(origsize)

def SimpleDecrypt(filename, key):
    f = Fernet(key)
    
    with open(filename, "rb") as file:
        encrypted_data = file.read()

    decrypted_data = f.decrypt(encrypted_data)

    with open(filename, "wb") as file:
        file.write(decrypted_data)


def main():
    with open("key.key", "rb") as key_file:
        RsaKey = RSA.importKey(open('private.pem').read())
        cipher = PKCS1_OAEP.new(RsaKey)    
        key = cipher.decrypt( key_file.read() )

    password = hashlib.sha256(key).digest()

    for dirpath, dirnames, filenames in os.walk('files'):
        for name in filenames :
            FilePath = os.path.join(dirpath, name)
            # SimpleDecrypt(FilePath, password)
            decrypt_file(password, FilePath)
            os.remove(FilePath)

if __name__ == "__main__":
    main()