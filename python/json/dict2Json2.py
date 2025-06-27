#!/usr/bin/python3
import json

my_dict = {'responseCode':200,'message':'success','data':[]}
print(json.dumps(my_dict,indent=4))
