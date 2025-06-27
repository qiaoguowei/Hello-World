import base64

encoded_str = "RmlyZXdhbGwxIQ=="

decoded_bytes = base64.b64decode(encoded_str)

print(decoded_bytes)
