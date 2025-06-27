chcp 65001
@echo off

:2
choice /t 3 /d y /n >null

del C:\Users\kingdom\Documents\nqhq.dbf
echo [32m删除完成[0m
copy D:\nqhq.dbf C:\Users\kingdom\Documents\ >null
echo 复制完成
if "%time%" GTR "18:59:00" (exit)
goto 2
