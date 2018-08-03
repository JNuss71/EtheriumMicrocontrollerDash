import serial
import subprocess
import time


def get_gpu_temp(cmd=["nvidia-smi"], fname='nvidia-out.txt'):
    templine = ""
    file = open(fname, 'w')
    subprocess.call(cmd, stdout=file, shell=True)
    file.close()
    rfile = open(fname, 'r')
    for i in range(9):
        templine = rfile.readline()
    temp = templine[8:11].rstrip('C')
    file.close()
    #print(temp)
    return temp;


def mine_process(ser):
    p = subprocess.Popen(["ethminer", "-G", "--cl-local-work", "256"], stderr=subprocess.PIPE, universal_newlines=True)
    last_speed_out=""
    for stdout_line in iter(p.stderr.readline, ""):
        if int(get_gpu_temp()) > 80:
            p.kill()
            return
        if stdout_line[24:29]=='Speed':
            last_speed_out = "S" + stdout_line[32:41].rstrip(' Mh/s')
        serialcomm=("BT" + get_gpu_temp() + last_speed_out + "E ")
        ser.write(serialcomm.encode())
        if ser.in_waiting>0:
            if ser.read(3) == str.encode('TOP'):
                p.kill()
                return
        print(serialcomm)
        # print(ser.read(20))
        # print(stdout_line)
    p.kill()
    return


def temp_process(ser):
    while True:
        serialcomm="BT" + get_gpu_temp() + "E "
        ser.write(serialcomm.encode())
        print(serialcomm)
        time.sleep(.4)
        if ser.in_waiting > 0:
            if ser.read(3) == str.encode('ART'):
                return


serglobal=serial.Serial(port="COM3", xonxoff=True, timeout=.5)
while True:
    temp_process(serglobal)
    mine_process(serglobal)

