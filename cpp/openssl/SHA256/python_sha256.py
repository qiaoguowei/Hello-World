#!/usr/bin/python3

import hmac
import hashlib

def _m_sha256():
    secret_key = "my_key"
    sha256_token = "hello world"
    hmac_sha256_hash = hmac.new(secret_key.encode('utf-8'), sha256_token.encode('utf-8'), hashlib.sha256).hexdigest()

    print(hmac_sha256_hash)

_m_sha256()
