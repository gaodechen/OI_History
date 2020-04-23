@echo off
:loop
    rank.exe > problem.in
    std.exe < problem.in > std.out
    problem.exe < problem.in > problem.out
    fc problem.out std.out
if not errorlevel 1 goto loop
pause
goto loop
