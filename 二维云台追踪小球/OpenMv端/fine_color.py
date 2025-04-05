import sensor, image, time
import display
from pyb import UART

uart = UART(3, 115200, timeout_char=1000)                         # 使用给定波特率初始化
uart.init(115200, bits=8, parity=None, stop=1, timeout_char=1000) # 使用给定参数初始化

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA2) #128*160
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
#clock = time.clock()
lcd = display.SPIDisplay()
red=[31, 45, 43, 68, 25, 54]  #红线阈值

def find_blobposition(img):
    max_size=0
    for blob in img.find_blobs([red],area_threshold=500):
        if blob[2]*blob[3]>max_size:    #只找最大的色块
            max_size=blob[2]*blob[3]
            img.draw_rectangle(blob.rect()) #将识别到的小球框出来
            img.draw_cross(blob.cx(),blob.cy())
            Sending(blob.cx(),blob.cy())    #找到小球再发数据
            print(blob.cx(),blob.cy())

def Sending(cx,cy):     #将数据包传给stm32(其实发送单个数据不需要用数据包，多此一举仅作为练习)
    data=bytearray([0xa3,0xb3,cx,cy,0xc3]) #帧头 + 帧头 +循迹结果+ 帧尾
    uart.write(data)

def Auto_SetThr():
    global red

    for i in range(200):
        img = sensor.snapshot()
        img.draw_rectangle((54,80,10,10), color=(255,0,0))  #圈出搜寻区域
        lcd.write(img)
        Statistics = img.get_statistics(roi=(75,55,10,10))  #得到搜寻区域内的图像统计信息
        red = [Statistics.l_min(),Statistics.l_max(), #从统计信息中得到色块阈值
                     Statistics.a_min(),Statistics.a_max(),
                     Statistics.b_min(),Statistics.b_max()]


#Auto_SetThr() #先自动定义阈值

while(True):
    img = sensor.snapshot()
    find_blobposition(img)
    lcd.write(img)


