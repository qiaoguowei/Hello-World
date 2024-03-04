#!/usr/bin/python3
import json

#if type(dict_value) == list and dict_value[0] == null:
#    print(dict_value)
retValue = {'responseCode':200,'message':'success','data':[None]}
#if len(retValue['data']) == 1:
if type(retValue['data']) == list and len(retValue['data']) > 0 and retValue['data'][0] == None:
    retValue['data'] = []
    print('i am coming')

print(json.dumps(retValue,indent=4))
