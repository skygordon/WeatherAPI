
import requests
import datetime
import json

def request_handler(request):
    r = requests.get("http://api.openweathermap.org/data/2.5/weather?q=Cambridge,us&APPID=80a2eb48c973e19d7e75afe6113a3e74")
    response = json.loads(r.text)
    
    if len(request['values'])!= 0:
        num = int(request['values']['numcount'])
    
    else:
        num = int(request['form']['numcount'])
    
    temp = "The temperature is " + str(((float(response["main"]["temp"])-273)*(9/5)+32))
    time = "The time is " + str((datetime.datetime.fromtimestamp(response["dt"]).strftime('%Y-%m-%d%H:%M:%S'))[10:])
    date =  "The date is " + str((datetime.datetime.fromtimestamp(response["dt"]).strftime('%Y-%m-%d%H:%M:%S'))[0:10])
    vis = "The visibility is " + str((response["weather"][0]["main"]))
    if num == 1:
        return temp
    if num == 2:
        return time
    if num == 3:
        return date
    if num == 4:
        return vis
    else:
        "Nonvalid numcount"


"""
Created on Sun Mar  3 22:02:49 2019
@author: skylargordon
"""

